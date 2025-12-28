#include <iostream>
#include <string>
#include <cstdio>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada>" << std::endl;
        return 1;
    }

    std::string entrada = argv[1];

    // Comprobar si los ejecutables ya existen
    struct stat buffer;
    bool doxygen_existe = (stat("documentador_prom", &buffer) == 0);
    bool linea80_existe = (stat("linea80_prom", &buffer) == 0);

    if(!doxygen_existe || !linea80_existe){
        std::string comandoflex_doxygen = "flex -o documentador.cpp documentador";
        std::string comandoflex_linea80 = "flex -o linea80.cpp linea80";

        std::string comandocompilar_doxygen = "g++ -std=c++17 -o documentador_prom documentador.cpp -lfl";
        std::string comandocompilar_linea80 = "g++ -std=c++17 -o linea80_prom linea80.cpp -lfl";

        system(comandoflex_doxygen.c_str());
        system(comandoflex_linea80.c_str());

        system(comandocompilar_doxygen.c_str());
        system(comandocompilar_linea80.c_str());
    }

    std::string comando_documentacion = "./documentador_prom " + entrada;
    std::string comando_linea80 = "./linea80_prom " + entrada;
    system(comando_documentacion.c_str());
    system(comando_linea80.c_str());
    
    // Eliminar archivos temporales generados
    remove("documentador.cpp");
    remove("linea80.cpp");
    remove("documentador_prom");
    remove("linea80_prom");

    return 0;
}