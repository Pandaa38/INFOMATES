/**
Este ejemplo ayuda a trabajar con un tablero. Se crea un tablero de solo una casilla
y en el se van mostrando las imagenes que estan en el directorio datos/caras_graph, con un
retardo de 2segundos entre cara y cara. 
**/

#include <QApplication>

#include "tablerografico.h"
#include <string>
#include <QTime> //delay
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem; //para listar el contenido de un directorio


// espera un numero de milisegundos
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

int main(int argc, char *argv[]){
 //siempre se pone para poder usar el entorno grafico
 QApplication a(argc, argv);
 
 
 //creamos un tablerografico de tamaño 200x200 con solo una casilla
 TableroGrafico *tg = new TableroGrafico(200,200,1,1);
 
 tg->show();  
 std::string path ="datos/caras_graph/";
 for (const auto & a : fs::directory_iterator(path)){
	std::cout<<"Imagen "<<a.path()<<std::endl;
 	tg->putImagen(0,0,a.path().c_str());
 	
 	delay(2000);
 } 
 //siempre se pone para finalizar el programa
 return a.exec();



}
