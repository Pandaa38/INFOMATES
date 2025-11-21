

#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include <mutex>
#include "scd.h"

using namespace std;
using namespace scd;

constexpr int
   num_items = 6*4*5,   // número de items a producir/consumir
   num_productores = 6, // número de productores
   num_consumidores = 4; // número de consumidores

constexpr int
   num_items_prod = num_items / num_productores,
   num_items_cons = num_items / num_consumidores,
   total_multiplos = num_items/5;

int
   siguiente_dato = 0; // siguiente valor a devolver en 'producir_dato'
   
constexpr int               
   min_ms    = 5,     // tiempo minimo de espera en sleep_for
   max_ms    = 20 ;   // tiempo máximo de espera en sleep_for


mutex
   mtx_cout;                 // mutex de escritura en pantalla
unsigned
   cont_prod[num_items] = {0}, // contadores de verificación: producidos
   cont_cons[num_items] = {0}; // contadores de verificación: consumidos



/**
 * @brief Función que simula la producción de un dato.
 * 
 * @param id_productor Identificador del productor.
 * @param n Posición del dato que se ha de producir.
 * 
 * @return unsigned Dato producido.
 */
unsigned producir_dato(int id_productor, int n){
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = id_productor * num_items/num_productores + n ;
   cont_prod[dato_producido] ++ ;
   mtx_cout.lock();
      cout << "Productor " << id_productor << " produce: " << dato_producido << endl << flush ;
   mtx_cout.unlock();
   return dato_producido ;
}

/**
 * @brief Función que simula el consumo de un dato.
 * 
 * @param dato Dato a consumir.
 * @param id_consumidor Identificador del consumidor.
 */
void consumir_dato( int id_consumidor, unsigned dato ){
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx_cout.lock();
      cout << "\t\t\t\t\tConsumidor " << id_consumidor << " consume: " << dato << endl ;
   mtx_cout.unlock();
}

/**
 * @brief Función que comprueba los contadores de producción y consumo.
 */
void test_contadores(){
   bool ok = true ;
   cout << "comprobando contadores ...." << endl ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}


/**
 * @brief Clase para monitor buffer, semántica SC, múltiples productores/consumidores.
 * 
 * @note Implementación FIFO.
 */
class Buffer : public HoareMonitor
{
 private:
 static const int           // constantes ('static' ya que no dependen de la instancia)
   num_celdas_total = 30;   //   núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//   buffer de tamaño fijo, con los datos
   primera_libre,          //   indice de celda de la próxima inserción
   primera_ocupada,        //   indice de celda de la próxima extracción
   ocupadas;               //   Número de celdas ocupadas

 int num_mult=0, num_mult_parcial=0;
 int insertados=0, extraidos=0;

 CondVar                    // colas condicion:
   buffer_vacio,            //  cola donde espera el consumidor (n>0)
   buffer_lleno,            //  cola donde espera el productor  (n<num_celdas_total)
   impresora ;              //  cola donde espera la impresora

 public:                    // constructor y métodos públicos
   Buffer() ;             // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int n_prod, int valor ); // insertar un valor (sentencia E) (productor)

   bool metodo_impresora();
} ;

/**
 * @brief Constructor de la clase Buffer.
 */
Buffer::Buffer(){
   primera_libre   = 0;
   primera_ocupada = 0;
   ocupadas        = 0;
   num_mult=0, num_mult_parcial=0;

   buffer_lleno   = newCondVar();
   buffer_vacio   = newCondVar();
}

/**
 * @brief Función que extrae un valor del buffer.
 */
int Buffer::leer(){

   // Esperamos a que haya algún valor en el buffer
   // esperar bloqueado hasta que 0 < ocupadas
   if ( ocupadas == 0 ) buffer_vacio.wait();

   // hacer la operación de lectura, actualizando estado del monitor
   int valor = buffer[primera_ocupada] ;
   primera_ocupada++ ;
   primera_ocupada %= num_celdas_total ;
   ocupadas-- ;

   extraidos++;
      
   // señalar al productor que hay un hueco libre, por si está esperando
   buffer_lleno.signal();

   // devolver valor
   return valor ;
}


/**
 * @brief Función que escribe un valor en el buffer.
 * 
 * @param valor Valor a escribir.
 */
void Buffer::escribir( int n_prod, int valor ){

   // esperar bloqueado hasta que haya hueco para escribir un valor
   // esperar bloqueado hasta que primera_libre < num_celdas_total
   if ( ocupadas == num_celdas_total ) buffer_lleno.wait();

   assert(ocupadas < num_celdas_total);

   // hacer la operación de inserción, actualizando estado del monitor
   buffer[primera_libre] = valor ;
   primera_libre++ ;
   primera_libre %= num_celdas_total ;
   ocupadas++ ;

   insertados++;

   if (valor % 5 == 0) {
      num_mult++;
      num_mult_parcial++;
      impresora.signal();
   }

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   buffer_vacio.signal();
}


// -----------------------------------------------------------------------------
/**
 * @brief Función que simula la hebra productora.
 * @param id_hebra Identificador de la hebra.
 * @param monitor Monitor.
 */
void funcion_hebra_productora( int id_hebra, MRef<Buffer> monitor ){
   
   int items_por_productor = num_items/num_productores;
   for( unsigned i = 0 ; i < items_por_productor ; i++ ){
      int valor = producir_dato( id_hebra, i );
      monitor->escribir( valor );
   }
}

/**
 * @brief Función que simula la hebra consumidora.
 * @param id_hebra Identificador de la hebra.
 * @param monitor Monitor.
 */
void funcion_hebra_consumidora( int id_hebra, MRef<Buffer>  monitor ){
   int items_por_consumidor = num_items/num_consumidores;
   for( unsigned i = 0 ; i < items_por_consumidor ; i++ ){
      int valor = monitor->leer();
      consumir_dato( id_hebra, valor );
   }
}

bool Buffer::metodo_impresora(){
   if(num_mult == total_multiplos){ cout << "fin de la impresora" << endl; return false; }

   if(num_mult_parcial == 0){
      impresora.wait();
   }

   cout << "Impresora: múltiplo de 5 nº " << num_mult_parcial << " insertado." << endl;

   num_mult_parcial = 0;
   return true;
}

void funcion_hebra_impresora( int id_hebra, MRef<Buffer>  monitor ){
   while( monitor->metodo_impresora() ){

   }
}

int main()
{
   cout << "--------------------------------------------------------------------" << endl
        << "Problema del productor-consumidor únicos (Monitor SU)               " << endl
        << "--------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Buffer> monitor = Create<Buffer>() ;

   // crear y lanzar los productores y consumidores
   thread hebra_prod[num_productores], hebra_cons[num_consumidores];
   for( unsigned i = 0 ; i < num_productores ; i++ )
      hebra_prod[i] = thread( funcion_hebra_productora, i, monitor );
   for( unsigned i = 0 ; i < num_consumidores ; i++ )
      hebra_cons[i] = thread( funcion_hebra_consumidora, i, monitor );

   // esperar a que terminen las hebras
   for( unsigned i = 0 ; i < num_productores ; i++ )
      hebra_prod[i].join();
   for( unsigned i = 0 ; i < num_consumidores ; i++ )
      hebra_cons[i].join();

   test_contadores() ;
}
