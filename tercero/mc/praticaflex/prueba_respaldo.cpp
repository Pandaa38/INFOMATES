#include <iostream>
#include <vector>
#include <string>

int suma(int a, int b) {
    return a + b;
}

void procesar_datos(const std::string& nombre, int* valores, double factor = 1.5) {
    int contador = 0;
    
    if (contador < 10) {
        std::cout << "Contador es menor que 10" << std::endl;
    }
    
    while (factor >= 0.5) {
        factor = factor - 0.1;
    }
    
    for (int i = 0; i < 100; i++) {
        if (valores[i] == 42) {
            std::cout << "Encontrado!" << std::endl;
        }
    }
    
    if (nombre != "test") {
        // Este es un comentario de linea muy largo que deberia ser cortado por el programa linea80 cuando supere los 80 caracteres de longitud
        std::cout << "El nombre no es test, es: " << nombre << std::endl;
    }
}

/* Este es un comentario
   de bloque que ocupa
   varias lineas */

std::vector<int> generar_numeros(int inicio, int fin) {
    std::vector<int> resultado;
    
    for (int j = 0; j <= fin; j++) {
        if (j > inicio) {
            resultado.push_back(j);
        }
    }
    
    while (resultado.size() <= 5) {
        resultado.push_back(0);
    }
    
    return resultado;
}

int main() {
    int x = 5;
    int y = 10;
    
    if (x <= y) {
        std::cout << "x es menor o igual que y" << std::endl;
    }
    
    if (x >= 3) {
        std::cout << "x es mayor o igual que 3" << std::endl;
    }
    
    while (x > 0) {
        x--;
    }
    
    procesar_datos("ejemplo", nullptr, 2.0);
    
    return 0;
}
