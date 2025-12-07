#include <iostream>
#include <string>
#include <cstdio>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        std::cerr << "Uso: " << argv[0] << " [archivo_entrada]" << std::endl;
        return 1;
    }

    std::string entrada = argv[1];

    // Comprobar si los ejecutables ya existen
    struct stat buffer;
    bool doxygen_existe = (stat("doxygen_prom", &buffer) == 0);
    bool linea80_existe = (stat("linea80_prom", &buffer) == 0);

    if(!doxygen_existe || !linea80_existe){
        std::string comandoflex_doxygen = "flex -o doxygen.cpp doxygen";
        std::string comandoflex_linea80 = "flex -o linea80.cpp linea80";

        std::string comandocompilar_doxygen = "g++ -std=c++17 -o doxygen_prom doxygen.cpp -lfl";
        std::string comandocompilar_linea80 = "g++ -std=c++17 -o linea80_prom linea80.cpp -lfl";

        system(comandoflex_doxygen.c_str());
        system(comandoflex_linea80.c_str());

        system(comandocompilar_doxygen.c_str());
        system(comandocompilar_linea80.c_str());
    }

    std::string comando = "./doxygen " + entrada + " | ./linea80";
    system(comando.c_str());

    return 0;
}