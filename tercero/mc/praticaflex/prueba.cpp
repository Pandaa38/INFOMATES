#include <iostream>
#include <vector>
#include <string>

/**
 * @brief Funcion suma
 *
 * @param a
 * @param b
 * @return 
 */
int suma(int a, int b) {
    return a + b;
}

/**
 * @brief Funcion procesar_datos
 *
 * @param nombre
 * @param valores
 * @param factor
 */
void procesar_datos(const std::string& nombre, int* valores, double factor = 
1.5) {
    int contador = 0;
    
    // Si contador es menor que 10...
    if (contador < 10) {
        std::cout << "Contador es menor que 10" << std::endl;
    } // end if
    
    // Mientras que factor sea mayor o igual que 0.5...
    while (factor >= 0.5) {
        factor = factor - 0.1;
    } // end while
    
    // Desde 0 hasta 100...
    for (int i = 0; i < 100; i++) {
        // Si valores[i] es igual a 42...
        if (valores[i] == 42) {
            std::cout << "Encontrado!" << std::endl;
        } // end if
    } // end for
    
    // Si nombre es diferente de "test"...
    if (nombre != "test") {
        // Este es un comentario de linea muy largo que deberia ser cortado por 
// el programa linea80 cuando supere los 80 caracteres de longitud
        std::cout << "El nombre no es test, es: " << nombre << std::endl;
    } // end if
}

/* Este es un comentario
   de bloque que ocupa
   varias lineas */

/**
 * @brief Funcion generar_numeros
 *
 * @param inicio
 * @param fin
 * @return 
 */
std::vector<int> generar_numeros(int inicio, int fin) {
    std::vector<int> resultado;
    
    // Desde 0 hasta fin...
    for (int j = 0; j <= fin; j++) {
        // Si j es mayor que inicio...
        if (j > inicio) {
            resultado.push_back(j);
        } // end if
    } // end for
    
    /**
     * @brief Funcion while
     *
     */
    while (resultado.size() <= 5) {
        resultado.push_back(0);
    }
    
    return resultado;
}

/**
 * @brief Funcion main
 *
 * @return 
 */
int main() {
    int x = 5;
    int y = 10;
    
    // Si x es menor o igual que y...
    if (x <= y) {
        std::cout << "x es menor o igual que y" << std::endl;
    } // end if
    
    // Si x es mayor o igual que 3...
    if (x >= 3) {
        std::cout << "x es mayor o igual que 3" << std::endl;
    } // end if
    
    // Mientras que x sea mayor que 0...
    while (x > 0) {
        x--;
    } // end while
    
    procesar_datos("ejemplo", nullptr, 2.0);
    
    return 0;
}
