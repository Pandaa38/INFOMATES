
#include <iostream>
#include <ctime>    // Para función time()
#include <cstdlib>  // Para números aleatorios
#include <cstring>
#include "../include/ficha.h"
#include "../include/tablero.h"
#include "../include/jugador.h"
#include "../include/juego.h"
#include "../include/conexion.h"

using namespace std;

/* ***************************************** */

// Preguntamos por teclado los datos de un jugador y lo devolvemos
Jugador LeeJugador(const Ficha f, char mod, string direc )
{
  string nom;
  int n;
  if (mod=='L'){
      cout << "******* JUGADOR LOCAL *******" << endl;
      cout << "Dime el nombre del jugador "<< f <<" : ";
      cin >> nom;
      cout << "Dime de que nivel es (0=humano, 1=aleatorio)";
      cin >> n;
  }
  else{
      cout << "******* JUGADOR REMOTO *******" << endl;
      cout << "Dime la ip del ordenador donde esta el Jugador Remoto"<<endl;
      cin>>direc;
      n=0;
  }
  
  return Jugador(nom,f,n,mod,direc);
}

/* ***************************************** */

int main(int argc, char *argv[])
{
  char p;
  char modalidad;
  char papel='N';
  Jugador j1;
  Jugador j2;
  Conexion conexion;
  char msg[50];

  srand(time(0));  // Inicializamos el generador de números aleatorios

  do{
     cout << "Modalidad de Juego" << endl;
     cout << "  Juego (L)ocal. Cuando los dos jugadores estan en el mismo ordenador" <<endl;
     cout << "  Juego en (R)ed. Cuando los jugadores estan cada uno en un ordenador" <<endl;
     cout << endl << "Introduce L o R ";
     cin >> modalidad;
     modalidad = toupper(modalidad);
  }while ((modalidad != 'L') && (modalidad != 'R'));
  
  if (modalidad=='R'){
      do{
         cout << endl<<"Que papel quieres desempeñar" << endl;
         cout << "  (S)erver o (C)liente"<<endl;
         cout << "  Cada jugador debe elegir uno de estos papeles no afecta al juego"<<endl<<endl;
         cout << "Introduce S o C ";
         cin >> papel;
         papel = toupper(papel);
      }while((papel != 'S') && (papel != 'C'));
      if (papel=='S'){                              //Server
         j1=LeeJugador(CIRCULO,'R',"");
         j2=LeeJugador(CRUZ,'L',"");
         conexion.Crear_Servidor();
         conexion.Aceptar_Cliente();
         conexion.Recibir_Msg(msg);
         j1.setNombre(&msg[1]);
         j1.setnivel(msg[0]-'0');        
         msg[0]='0'+j2.getnivel();
         msg[1]='\0';
         strcat(msg,j2.Nombre().c_str());
         conexion.Enviar_Msg(msg);

      }else{                                         //Cliente
         j1=LeeJugador(CIRCULO,'L',"");
         j2=LeeJugador(CRUZ,'R',"");
         conexion.Establecer_Conexion(j2.getip().c_str());
         msg[0]='0'+j1.getnivel();
         msg[1]='\0';
         strcat(msg,j1.Nombre().c_str());
         conexion.Enviar_Msg(msg);
         conexion.Recibir_Msg(msg);
         j2.setNombre(&msg[1]);
         j2.setnivel(msg[0]-'0');

      } 
  }
  else { //Modalidad de juego local los dos juagadores son locales
     j1=LeeJugador(CRUZ,modalidad,"");
     j2=LeeJugador(CIRCULO,modalidad,"");
  }
  
  // Creamos un juego usando un tablero y dos jugadores leidos por teclado  
  Juego3Raya juego(Tablero(),j1,j2,modalidad,conexion);

  // También se podría hacer de esta otra forma:
  //   Jugador j1=LeeJugador(CRUZ);       // Creamos los jugadores
  //   Jugador j2=LeeJugador(CIRCULO);
  //   Tablero tab;                       // Creamos un tablero
  //   Juego3Raya juego(tab,j1,j2);       // Creamos el juego

  do {

    cout << "Los jugadores son: " << endl;
    cout << "  " << juego.ElJugador(0) << endl;
    cout << "  " << juego.ElJugador(1) << endl;
    cout << "Comenzamos!!!" << endl << endl;

    juego.NuevoJuego();    // Comenzamos el juego
    do {
      cout << "Le toca jugar a : " << juego.ElJugador(juego.AQuienLeToca()) << endl;
      juego.JugarTurno();    // Avanzamos turno
      cout << "Tras poner la ficha, el tablero queda así: " << endl
           << juego.ElTablero() << endl;
    } while (!juego.HemosAcabado());    // Comprobamos si hemos acabado

    cout << "Se acabó la partida !!!" << endl;

    int ganador=juego.QuienGana();   // Consultamos quien ganó
    if (ganador==-1)
      cout << "Hubo empate" << endl;
    else
      cout << "El ganador ha sido: " << juego.ElJugador(ganador) << endl;

    cout << "¿Otra partida (S/N)?";
    cin >> p;

  } while ((p=='s') || (p=='S'));
  
  if(modalidad == 'R') 
     conexion.Cerrar_Conexion();
}
