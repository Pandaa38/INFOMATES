#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// g++ -std=c++11 -pthread -o [ejecutable] [fichero].cpp


// numero de fumadores 

const int num_fumadores = 3 ;

vector<Semaphore> ingr_disponible;
Semaphore mostrador_vacio(1);

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  )
{
   int ingrediente;

   for( int i = 0 ; i < 10 ; i++ )
   {
      ingrediente = producir_ingrediente( );
      mostrador_vacio.sem_wait( );
      cout << i << " Estanquero : Ingrediente " << ingrediente << " puesto." << endl << flush;
      ingr_disponible[ingrediente].sem_signal( );
   }



}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
      ingr_disponible[num_fumador].sem_wait( );
      cout << "Fumador " << num_fumador << "  : Ingrediente retirado." << endl << flush;
      mostrador_vacio.sem_signal();
      fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main()
{
   // Inicialización del vector de semáforos - cada uno con valor inicial 0
   for(int i = 0; i < num_fumadores; i++)
      ingr_disponible.push_back(Semaphore(0));

   thread hebra_estanquero(funcion_hebra_estanquero);
   thread hebra_fumador[num_fumadores];  // Usamos num_fumadores en lugar de NUM_FUMADORES

   for (int i = 0; i < num_fumadores; i++)  // Usamos num_fumadores aquí también
      hebra_fumador[i] = thread(funcion_hebra_fumador, i);
   
   hebra_estanquero.join();
   for (int i = 0; i < num_fumadores; i++)  // Y aquí
      hebra_fumador[i].join();

   return 0;
}
