
/* 
 * File:   main.cpp
 * Author: juan
 *
 * Created on 15 de julio de 2024, 21:04
 */


#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

void removeEmptyDirectories(const fs::path& directory) {
   for (fs::directory_iterator it(directory); it != fs::directory_iterator(); ++it) {
       const fs::directory_entry& entry = *it;
       if (fs::is_directory(entry.path())) {
           removeEmptyDirectories(entry.path()); // Recursivamente elimina subdirectorios vacíos
       }
   }

   // Eliminar el directorio si está vacío después de eliminar sus subdirectorios
   if (fs::is_empty(directory)) {
       fs::remove(directory);
       std::cout << "Eliminado directorio vacío: " << directory << std::endl;
   }
}

int main(int argc, char* argv[]){
    
    fs::path targetDirectory = "/ruta/al/directorio"; // Cambia esto por el directorio que deseas limpiar
    boost::filesystem::remove(targetDirectory); 

   if (fs::exists(targetDirectory) && fs::is_directory(targetDirectory)) {
       removeEmptyDirectories(targetDirectory);
   } else {
       std::cerr << "El directorio especificado no existe o no es un directorio válido." << std::endl;
   }

    return 0;
}

