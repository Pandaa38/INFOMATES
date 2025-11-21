#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales
const unsigned 
   num_items = 100 ,   // número de items
	tam_vec   = 10 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)




// Semáforos usados para controlar la sincronización
// - espera_consumidor: indica cuántos valores hay disponibles para consumir.
// - espera_productor: indica cuántos huecos hay disponibles para producir.
Semaphore espera_consumidor = 0;
Semaphore espera_productor = tam_vec;



// Mutex para que no se entrelacen los couts
mutex mtx_cout;


int vec[tam_vec];
int primera_libre = 0;
int primera_ocupada = 0;

//PARA IMPRESORA
int num_ocupadas = 0; 
mutex mtx_ocupadas;

// Semáforos para la sincronización con la impresora
Semaphore sem_prod_impr = 0; // Productor avisa a Impresora
Semaphore sem_impr_prod = 0; // Impresora avisa a Productor

Semaphore sem_buffer = 1; // Mutex para el buffer



/**
 * @brief Función que simula la producción de un dato.
 * 
 * @return unsigned Dato producido.
 */
unsigned producir_dato(){
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   mtx_cout.lock();
      cout << "Producido: " << dato_producido << endl << flush ;
   mtx_cout.unlock();
   return dato_producido ;
}

/**
 * @brief Función que simula el consumo de un dato.
 * 
 * @param dato Dato a consumir.
 */
void consumir_dato( unsigned dato ){
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx_cout.lock();
      cout << "\t\t\t\t\t\tConsumido: " << dato << endl ;
   mtx_cout.unlock();
}

/**
 * @brief Función que comprueba los contadores de producción y consumo.
 */
void test_contadores(){
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

/**
 * @brief Función que simula la hebra productora.
 */
void  funcion_hebra_productora(  ){
   for( unsigned i = 0 ; i < num_items ; i++ ){
      
      int dato = producir_dato();

      // Comprobamos que se puede producir
      sem_wait(espera_productor);

         sem_wait(sem_buffer);
         
         vec[primera_libre++] = dato;
         primera_libre %= tam_vec;
            
         // Actualizar variable de ocupación bajo exclusión mutua
         num_ocupadas++;
         
         // Sincronización con la impresora si es múltiplo de 5
         if (dato % 5 == 0) {
            sem_prod_impr.sem_signal(); // Desbloquear impresora
            sem_impr_prod.sem_wait();   // Esperar a que la impresora termine
         }
      
         sem_signal(sem_buffer);

      sem_signal(espera_consumidor);
   }
}

//----------------------------------------------------------------------

/**
 * @brief Función que simula la hebra consumidora.
 */
void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ ){
      int dato = 0;
      sem_wait(espera_consumidor);

         sem_wait(sem_buffer);

         dato = vec[primera_ocupada++];
         primera_ocupada %= tam_vec;

         num_ocupadas--;
         
         sem_signal(sem_buffer);
      sem_signal(espera_productor);

      consumir_dato( dato ) ;
    }
}
//----------------------------------------------------------------------

void funcion_hebra_impresora()
{
   // El número de iteraciones es N/5 (donde N=num_items)
   const int iteraciones = num_items / 5;

   for(int i = 0; i < iteraciones; i++) {

      sem_prod_impr.sem_wait();

      cout << "IMPRESORA: Celdas ocupadas en el buffer: " << num_ocupadas << endl;

      sem_impr_prod.sem_signal();
   }
   
   mtx_cout.lock();
   cout << "IMPRESORA: Terminada." << endl;
   mtx_cout.unlock();
}



int main()
{
   
   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora ),
          hebra_impresora  ( funcion_hebra_impresora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;
   hebra_impresora.join();

   test_contadores();
}
