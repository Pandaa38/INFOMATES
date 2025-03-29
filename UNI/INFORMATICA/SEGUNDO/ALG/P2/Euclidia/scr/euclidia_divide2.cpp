#include<iostream>
#include<fstream>
#include <vector>
#include<algorithm>
#include <limits>

#include"Punto2D.h"

using namespace std;

float distanciaStrip(vector<Punto2D>& strip, float d);
float distMin(vector<Punto2D>& v, int izq, int der);

int main(int argc, char const *argv[]) {
    vector<Punto2D> puntos;

    // Leer puntos desde archivo o generar aleatorios
    if (argc == 2) {
        ifstream file(argv[1]);
        Punto2D punto_2d;
        while (file >> punto_2d) {
            puntos.push_back(punto_2d);
        }
        file.close();
    }
    else {
        srand(time(NULL));
        for(int i = 0; i < 10; i++) {
            puntos.push_back(Punto2D(rand()%100, rand()%100));
        }
    }

    // Ordenar puntos por coordenada x
    sort(puntos.begin(), puntos.end());

    // Imprimir puntos
    cout << "Puntos: " << endl;
    for (const Punto2D& p : puntos) {
        cout << p << endl;
    }

    // Calcular distancia mínima
    float minDist = distMin(puntos, 0, puntos.size() - 1);

    cout << endl;
    cout << "Distancia minima: " << minDist << endl;

    return 0;
}

float distanciaStrip(vector<Punto2D>& strip, float d) {
    // Ordenar la franja por coordenada y
    sort(strip.begin(), strip.end(), [](const Punto2D& a, const Punto2D& b) {
        return a.gety() < b.gety();
    });
    /*
    float dist = d;
    float minDist = distMin(strip, 0, strip.size() - 1);

    return min(d, minDist);
    */

    float minDist = d;

    // Limitar comparaciones a un número constante (máximo 7)
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() &&
             (strip[j].gety() - strip[i].gety()) < minDist &&
             j < i + 7; ++j) {
            float dist = strip[i].distancia(strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
             }
    }

    return minDist;
}

float distMin(vector<Punto2D>& v, int izq, int der) {

    if (der - izq + 1 == 2) {           // Caso base: 2 puntos
        return v[izq].distancia(v[der]);
    }else if (der - izq + 1 <= 1) {     // Caso base: 1 punto
        return numeric_limits<float>::max();
    }

    // Punto medio
    int mid = izq + (der - izq) / 2;
    Punto2D midPoint = v[mid];

    // Dividir y conquistar
    float dl = distMin(v, izq, mid);
    float dr = distMin(v, mid + 1, der);
    float d = min(dl, dr);

    // Construir franja de puntos cercanos a la línea media
    vector<Punto2D> strip;
    for (int i = izq; i <= der; ++i) {
        if (abs(v[i].getx() - midPoint.getx()) < d) {
            strip.push_back(v[i]);
        }
    }

    // Calcular distancia mínima en la franja
    float dStrip = distanciaStrip(strip, d);

    return min(d, dStrip);
}