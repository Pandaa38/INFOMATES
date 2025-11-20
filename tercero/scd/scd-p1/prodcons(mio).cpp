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
   num_items = 40 ,   // número de items
	tam_vec   = 10 ;   // tamaño del buffer
unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   siguiente_dato       = 0 ;  // siguiente dato a producir en 'producir_dato' (solo se usa ahí)

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato()
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   cout << "producido: " << dato_producido << endl << flush ;
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

// Variables globales para el buffer y sincronización
Semaphore puede_insertar(tam_vec); // Semáforo para espacios libres
Semaphore puede_extraer(0);        // Semáforo para items disponibles
mutex mtx;
Semaphore mutex_sem(1);

// Buffer circular compartido
int buffer[tam_vec];
int primera_libre = 0;
int primera_ocupada = 0; 



//----------------------------------------------------------------------


void test_contadores()
{
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

//----------------------------------------------------------------------

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;
      
      // Esperar a que haya un hueco libre
      sem_wait(puede_insertar);
      
      // Entrar a sección crítica
      //mtx.lock();
      sem_wait(mutex_sem);
      
      // Insertar el dato en el buffer
      buffer[primera_libre] = dato;
      primera_libre = (primera_libre + 1) % tam_vec;
      
      // Salir de sección crítica
      //mtx.unlock();
      sem_signal(mutex_sem);
      
      // Señalar que hay un dato más
      sem_signal(puede_extraer);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato=0;
      // Esperar a que haya un dato disponible
      sem_wait(puede_extraer);
      
      // Entrar a sección crítica
      mtx.lock();
      //sem_wait(mutex_sem);
      
      // Extraer el dato del buffer
      dato = buffer[primera_ocupada];
      primera_ocupada = (primera_ocupada + 1) % tam_vec;
      
      // Salir de sección crítica
      mtx.unlock();
      //sem_signal(mutex_sem);
      
      // Señalar que hay un hueco libre más
      sem_signal(puede_insertar);
      
      consumir_dato( dato ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO o FIFO ?)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}
