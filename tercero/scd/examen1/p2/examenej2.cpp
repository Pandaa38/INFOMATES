

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <vector>
#include "scd.h"

using namespace std ;
using namespace scd ;

// numero de fumadores 
const int num_fumadores = 4;  // Ahora hay 4 fumadores

// Número de iteraciones del estanquero
const int num_items = 50;  // Más iteraciones para ver el efecto

// Mutex cout
mutex mtx_cout;


//-------------------------------------------------------------------------
/**
 * @brief Función que simula la acción de producir un ingrediente
 * 
 * @return int Número de ingrediente producido
 */
int producir_ingrediente(){
   // calcular milisegundos aleatorios de duración de la acción de producción
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   mtx_cout.lock();
      cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;
   mtx_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,2>() ;  // Solo ingredientes 0, 1, 2

   // informa de que ha terminado de producir
   mtx_cout.lock();
      cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;
   mtx_cout.unlock();

   return num_ingrediente ;
}


/**
 * @brief Función que simula la acción de fumar.
 * Tiene un retardo aleatorio de la hebra.
 * 
 * @param num_fumador Número del fumador
 */
void fumar( int num_fumador ){

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar
   mtx_cout.lock();
      cout << "Fumador " << num_fumador << "  :"
         << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;
   mtx_cout.unlock();

   // espera bloqueada un tiempo igual a 'duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar
   mtx_cout.lock();
      cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
   mtx_cout.unlock();
}



class Estanco : public HoareMonitor{
   private:
      static const int VACIO = -1;

      int mostrador;    // Indica el ingrediente que hay en el mostrador. -1=No hay ingrediente
      CondVar ingr_fumador[num_fumadores];  // Una cola para cada fumador específico
      CondVar mostrador_lleno;

      bool abierto;
      
      // Nuevas variables para el ejercicio
      bool cuenta;  // Variable para controlar la hebra contadora
      CondVar hebra_contadora_bloqueada;  // Cola para la hebra contadora
      int veces_fumado[num_fumadores];  // Contador de veces que ha fumado cada fumador
      int veces_ingrediente_0;  // Contador de veces que se ha producido el ingrediente 0

   public:
      Estanco();
      void ponerIngrediente(int i);
      bool obtenerIngrediente(int i);
      void esperarRecogidaIngrediente();
      void cierreEstanco();
      bool estaAbierto();
      void cuenta_cigarros();  // Nueva función para la hebra contadora
};

/**
 * @brief Constructor de la clase Estanco
 * 
 * Inicializa el mostrador a -1, ya que no hay ningún ingrediente en el mostrador
 */
Estanco::Estanco(){
   mostrador = VACIO;
   for (int i=0; i<num_fumadores; ++i)  // Una cola por cada fumador
      ingr_fumador[i] = newCondVar();
   mostrador_lleno = newCondVar();
   hebra_contadora_bloqueada = newCondVar();
   abierto = true;
   cuenta = false;
   veces_ingrediente_0 = 0;
   for (int i=0; i<num_fumadores; ++i)
      veces_fumado[i] = 0;
}

/**
 * @brief Función que pone un ingrediente en el mostrador
 * 
 * @param i Ingrediente a poner
 */
void Estanco::ponerIngrediente(int i){
   mostrador = i;
   
   // Si es el ingrediente 0, elegimos aleatoriamente entre fumador 0 y fumador 3
   if (i == 0){
      veces_ingrediente_0++;
      
      // Cada 15 veces que se genera el ingrediente 0, activamos la hebra contadora
      if (veces_ingrediente_0 % 15 == 0){
         cuenta = true;
         hebra_contadora_bloqueada.signal();
      }
      
      // Elegimos aleatoriamente entre fumador 0 y fumador 3
      int fumador_elegido = aleatorio<0,1>() == 0 ? 0 : 3;
      mtx_cout.lock();
         cout << "Estanquero : Ingrediente 0 disponible, se despierta al fumador " << fumador_elegido << endl;
      mtx_cout.unlock();
      
      // Despertamos solo al fumador elegido
      ingr_fumador[fumador_elegido].signal();
   }
   else if (i == 1){
      // El ingrediente 1 es para el fumador 1
      ingr_fumador[1].signal();
   }
   else if (i == 2){
      // El ingrediente 2 es para el fumador 2
      ingr_fumador[2].signal();
   }
}

/**
 * @brief Función que obtiene un ingrediente del mostrador
 * 
 * @param num_fumador Número del fumador
 * @return true Si el estanco está abierto, false si está cerrado
 */
bool Estanco::obtenerIngrediente(int num_fumador){

   // Determinamos qué ingrediente necesita el fumador
   int ingrediente_necesario;
   if (num_fumador == 0 || num_fumador == 3)
      ingrediente_necesario = 0;
   else if (num_fumador == 1)
      ingrediente_necesario = 1;
   else
      ingrediente_necesario = 2;

   // Si el estanco está abierto
   if (abierto){

      // Si el ingrediente no es el que está en el mostrador, esperamos en NUESTRA cola específica
      if (mostrador != ingrediente_necesario)
         ingr_fumador[num_fumador].wait();

      // Por si se ha cerrado mientras estábamos bloqueados
      if (abierto){
         // Lo cogemos, y avisamos al estanquero
         mostrador = VACIO;
         veces_fumado[num_fumador]++;  // Incrementamos el contador de este fumador
         mtx_cout.lock();
            cout << "Fumador " << num_fumador << "  : Ingrediente retirado." << endl << flush;
         mtx_cout.unlock();
         mostrador_lleno.signal();
      }
   }
   return abierto;
}

/**
 * @brief Función que espera a que se recoja un ingrediente
 */
void Estanco::esperarRecogidaIngrediente(){
   if (mostrador != VACIO)
      mostrador_lleno.wait();
}

/**
 * @brief Función que cierra el estanco
 */
void Estanco::cierreEstanco(){
   abierto = false;

   // Desbloqueamos a todos los fumadores que estén esperando
   for (int i=0; i<num_fumadores; ++i)
      ingr_fumador[i].signal();
   
   // Desbloqueamos la hebra contadora
   cuenta = true;
   hebra_contadora_bloqueada.signal();
}

/**
 * @brief Función que indica si el estanco está abierto
 * 
 * @return true Si el estanco está abierto
 * @return false Si el estanco está cerrado
 */
bool Estanco::estaAbierto(){
   return abierto;
}

/**
 * @brief Función que cuenta los cigarros fumados por los fumadores que comparten el ingrediente 0
 */
void Estanco::cuenta_cigarros(){
   // Si cuenta es false, bloqueamos la hebra
   if (!cuenta)
      hebra_contadora_bloqueada.wait();
   
   // Si el estanco está cerrado, salimos
   if (!abierto)
      return;
   
   // Mostramos el número total de veces que han fumado los fumadores 0 y 3
   int total = veces_fumado[0] + veces_fumado[3];
   mtx_cout.lock();
      cout << "========================================" << endl;
      cout << "CONTADOR: Total de cigarros fumados por fumadores 0 y 3: " << total << endl;
      cout << "  - Fumador 0: " << veces_fumado[0] << " cigarros" << endl;
      cout << "  - Fumador 3: " << veces_fumado[3] << " cigarros" << endl;
      cout << "========================================" << endl;
   mtx_cout.unlock();
   
   // Actualizamos cuenta a false
   cuenta = false;
}



//----------------------------------------------------------------------
/**
 * @brief Función que ejecuta la hebra del estanquero
 * 
 * @param monitor Monitor del estanco
 */
void funcion_hebra_estanquero(MRef<Estanco> monitor){
   int num_ingr_producido;

   for (int i=0; i<num_items; ++i){
      num_ingr_producido = producir_ingrediente();
      monitor->esperarRecogidaIngrediente();

      mtx_cout.lock();
         cout << i << " Estanquero : Ingrediente " << num_ingr_producido << " puesto." << endl << flush;
      mtx_cout.unlock();
      monitor->ponerIngrediente(num_ingr_producido);
   }
   monitor->esperarRecogidaIngrediente();

   mtx_cout.lock();
      cout << "Fin Estanquero : Cerramos." << endl << flush;
   mtx_cout.unlock();
   monitor->cierreEstanco();
}

/**
 * @brief Función que ejecuta la hebra de un fumador
 * 
 * @param num_fumador Número del fumador
 * @param monitor Monitor del estanco
 */
void  funcion_hebra_fumador( int num_fumador, MRef<Estanco> monitor ){
   
   /*
      ObtenerIngrediente es necesario que nos informe sobre si el estanco está abierto o cerrado
      Si esta funcion tan solo se encargase de esperar a que el ingrediente estuviese disponible,
         como tras obtener el último ingrediente se hace un signal y se libera al estanquero,
         este podría cerrar el estanco antes de que el fumador sepa que ese ingrediente es válido.
   */
   while (monitor->obtenerIngrediente(num_fumador))
      fumar(num_fumador);
}

/**
 * @brief Función que ejecuta la hebra contadora
 * 
 * @param monitor Monitor del estanco
 */
void funcion_hebra_contadora(MRef<Estanco> monitor){
   while (monitor->estaAbierto()){
      monitor->cuenta_cigarros();
   }
}

//----------------------------------------------------------------------
int main(){

   MRef<Estanco> monitor = Create<Estanco>();
   
   thread hebra_estanquero(funcion_hebra_estanquero, monitor);
   thread hebra_fumador[num_fumadores];
   thread hebra_contadora(funcion_hebra_contadora, monitor);

   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i]=thread(funcion_hebra_fumador, i, monitor);

   // Es necesario poner un join para que el main no termine antes que las hebras
   hebra_estanquero.join();
   for (int i=0; i<num_fumadores; ++i)
      hebra_fumador[i].join();
   hebra_contadora.join();

   return 0;
}
