/**
Este ejemplo ayuda a trabajar con un tablero,consola y ventana. Se crea una ventana que integra
un tablero de 4x4 casillas y un consola. Cada vez que el usuario hace doble-click derecho sobre
una casilla se muestra el nombre del personaje.

**/

#include <QApplication>
#include "tablerografico.h"
#include <string>
#include <QTime> //delay
#include <filesystem>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
namespace fs = std::filesystem; //para listar el contenido de un directorio
using namespace std;


int main(int argc, char *argv[]){
 //siempre se pone para poder usar el entorno grafico
 QApplication a(argc, argv);
 Ventana v = new Ventana("Ejemplo Ventana");
 
 //creamos un tablerografico de tamaño 400x400 con 4x4 casillas
 TableroGrafico *tg = new TableroGrafico(400,400,4,4);
 
 //leemos las imagenes del directorio
 std::string path ="datos/caras_graph/";
 std::vector<std::string> nombres_files;
 for (const auto & a : fs::directory_iterator(path)){
	std::cout<<"Imagen "<<a.path()<<std::endl;
	nombres_files.push_back(a.path());
 }
 v->setTablero
 v->show();   
 //Iniciamos el tablero con 3x3 imagenes
 srand(time(0));
 for (int i=0;i<tg->getNrows();i++){
   for (int j=0;j<tg->getNcols();j++){
        string nf = nombres_files[rand()%nombres_files.size()];
        tg->putImagen(i,j,nf.c_str());
    }    
 } 
 
 //mientras que el usuario pulse una casill (doble-click derecho)
 //modificamos la imagen de la casilla escogida
 //pulsar CTRL +C para salir del bucle
 while (1){
  int r,c;
  tg->getCasillaElegida(r,c);
  string nf = nombres_files[rand()%nombres_files.size()];
  tg->putImagen(r,c,nf.c_str());
 
  }
  
 //siempre se devuelve el valor de a.exec()
 return a.exec();



}
