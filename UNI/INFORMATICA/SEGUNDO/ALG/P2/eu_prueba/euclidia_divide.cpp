#include<iostream>
#include<fstream>
#include <vector>
#include<algorithm>
#include <limits>
#include<chrono>

#include"Punto2D.h"

using namespace std;

double distMinDivide(vector<Punto2D> &v, int izq, int der);

int main(int argc, char* argv[]) {
    // Verifica que se haya pasado al menos un parámetro
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <N | puntos.txt>" << std::endl;
        return 1;
    }

    std::vector<Punto2D> puntos;
    std::string arg = argv[1];

    // Comprueba si el argumento es un número
    bool esNumero = true;
    for (char c : arg) {
        if (!std::isdigit(c)) {
            esNumero = false;
            break;
        }
    }

    if (esNumero) {
        // Caso 1: El usuario ingresa el número de puntos
        int n = std::stoi(arg);
        srand(time(NULL));
        for(int i = 0; i < n; i++) {
            puntos.push_back(Punto2D(rand()%100, rand()%100));
        }
    } else {
        // Caso 2: El argumento es el nombre de un archivo que contiene los puntos
        std::ifstream file(arg);
        if (!file) {
            std::cerr << "Error al abrir el archivo " << arg << std::endl;
            return 1;
        }
        Punto2D punto_2d;
        while (file >> punto_2d) {
            puntos.push_back(punto_2d);
        }
        file.close();
    }

    // Verifica que se hayan ingresado suficientes puntos para calcular distancias
    if (puntos.size() < 2) {
        std::cerr << "No hay suficientes puntos para calcular la distancia." << std::endl;
        return 1;
    }
    sort(puntos.begin(), puntos.end());

    cout << "Puntos: " << endl;
    for (int i = 0; i < puntos.size(); i++) {
        cout << puntos[i] << endl;
    }
    cout << "Total de puntos: " << puntos.size() << endl;

    auto start = chrono::high_resolution_clock::now();
    double min_dist = distMinDivide(puntos,0, puntos.size()-1);
    auto end = chrono::high_resolution_clock::now();

    cout << "Tiempo divide tam " << puntos.size() << ": "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    cout << "Distancia minima: " << min_dist << endl;

    return 0;
}

double distMinDivide(vector<Punto2D> &v, int izq, int der) {

    // Caso base: 2 o menos puntos
    if (der - izq + 1 <= 2) {
        if (der - izq + 1 == 2) {
            double dist = v[izq].distancia(v[der]);
            //cout << "Distancia: " << dist << endl;
            return dist;
        }
        return numeric_limits<double>::max();
    }

    //Creacion de pivote o punto medio
    int mid = (izq + der) / 2;
    Punto2D midPoint = v[mid];

    //Dividir
    double dl = distMinDivide(v, izq, mid);
    double dr = distMinDivide(v, mid+1, der);
    double d = min(dl, dr);

    //Franja para poder unir las soluciones
    vector<Punto2D> strip;
    for (int i = izq; i <= der; i++) {
        if (abs(v[i].getx() - midPoint.getx()) < d)
            strip.push_back(v[i]);
    }

    // Ordenar la franja por la coordenada y
    sort(strip.begin(), strip.end(), [](const Punto2D &a, const Punto2D &b) {
        return a.gety() < b.gety();
    });

    // Comparar cada punto de la franja solo con aquellos siguientes cuya diferencia en y sea menor que d
    double dStrip = d;
    int stripSize = strip.size();
    for (int i = 0; i < stripSize; i++) {
        for (int j = i + 1; j < stripSize && (strip[j].gety() - strip[i].gety()) < dStrip; j++) {
            dStrip = min(dStrip, strip[i].distancia(strip[j]));
        }
    }

    return min(d, dStrip);
}