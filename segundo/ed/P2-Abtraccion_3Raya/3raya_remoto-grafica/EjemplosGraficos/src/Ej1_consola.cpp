/**
Este ejemplo ayuda a trabajar con una consola. Permite escribir y leer desde la consola
**/

#include <QApplication>
#include "consola.h"
#include <string>
#include <QTime> //delay
#include <filesystem>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
namespace fs = std::filesystem; //para listar el contenido de un directorio



int main(int argc, char *argv[]){
 //siempre se pone para poder usar el entorno grafico
 QApplication a(argc, argv);
 
 
 //creamos un tablerografico de tamaño 400x400 con 3x3 casillas
 Consola *con = new Consola();
 
 //se muestra la consola
 con->show();   
 
 //leemos las imagenes del directorio
 std::string path ="datos/caras_graph/";
 std::vector<string> nombres_files;
 for (const auto & a : fs::directory_iterator(path)){
	std::cout<<"Imagen "<<a.path()<<std::endl;
	nombres_files.push_back(a.path());
	//Escribimos los ficheros leidos 
	con->WriteText(a.path());	
 }
 //pedimos al usuario un numero para mostrarle el personaje asociado a ese numero
 string txt="Dime un numero entre 0 y "+std::to_string(nombres_files.size()-1);
 con->WriteText(txt);
 int n=con->ReadInt(); //ReadChar permite leer un caracter, ReadString leer cadenas de caracteres
 txt="El personaje escogido es "+nombres_files[n];
 con->WriteText(txt);
 
 txt="Pulse el boton X (arriba esquina derecha) para salir";
 con->WriteText(txt);


 //siempre se devuelve el valor de a.exec()
 return a.exec();
}
