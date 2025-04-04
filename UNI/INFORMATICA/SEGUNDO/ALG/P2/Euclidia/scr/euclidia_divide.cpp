#include<iostream>
#include<fstream>
#include <vector>
#include<algorithm>
#include <limits>
#include<chrono>

#include"Punto2D.h"

using namespace std;

double distMinDivide(vector<Punto2D> &v, int izq, int der, const string& func = "normal");

int main(int argc, char const *argv[]) {

    /*
    vector<Punto2D> puntos(i);


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
    cout << endl;

    // Calcular distancia mínima
    double minDist = distMinDivide(puntos, 0, puntos.size() - 1);


    cout << "Distancia minima: " << minDist << endl;
    */

    ofstream file("../tiempos_divide.csv");
    srand(time(NULL));

    for (int i = 5; i <= 105; i = i + 10) {
        //creacion array
        vector<Punto2D> puntos(i);

        for(int j = 0; j < i; j++) {
            puntos.push_back(Punto2D(rand()%100, rand()%100));
        }

        //sort(puntos.begin(), puntos.end()); //O(nlog(n)
        auto start = chrono::high_resolution_clock::now();
        double min_dist = distMinDivide(puntos,0, puntos.size()-1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time fuerza tam " << i << ": "
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
        file << i << ","
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
    }
    file.close();

    return 0;
}

// double distMinDivide(vector<Punto2D> &v, int izq, int der, const string& func) {
//
//     //cout << "Puntos: " << func << endl;
//     //cout << "izq: " << izq << " der: " << der << endl;
//     // Se corrige el límite del bucle para incluir el elemento en 'der'
//     //for (int i = izq; i <= der; i++) {
//     //    cout << v[i] << endl;
//     //}
//
//     // Caso base: 2 o menos puntos
//     if (der - izq + 1 <= 2) {
//         if (der - izq + 1 == 2) {
//             double dist = v[izq].distancia(v[der]);
//             //cout << "Distancia: " << dist << endl;
//             return dist;
//         }
//         return numeric_limits<double>::max();
//     }
//
//     // Punto medio
//     int mid = (izq + der) / 2;
//     Punto2D midPoint = v[mid];
//     //cout << "Mid: " << midPoint << endl << endl;
//
//     // Dividir y conquistar:
//     // Se utiliza la misma estrategia, dividiendo el arreglo en dos mitades que se solapan en el punto medio
//     double dl = distMinDivide(v, izq, mid);
//     double dr = distMinDivide(v, mid+1, der);
//     double d = min(dl, dr);
//
//     // Construir la franja de puntos cercanos a la línea media
//     vector<Punto2D> strip;
//     for (int i = izq; i <= der; i++) {
//         if (abs(v[i].getx() - midPoint.getx()) < d)
//             strip.push_back(v[i]);
//         /*
//         if (v[i].distancia(midPoint) <= d && v[i] != midPoint) {
//             strip.push_back(v[i]);
//         }
//         */
//     }
//
//     // Ordenar la franja por la coordenada y
//     sort(strip.begin(), strip.end(), [](const Punto2D &a, const Punto2D &b) {
//         return a.gety() < b.gety();
//     });
//
//     // Comparar cada punto de la franja solo con aquellos siguientes cuya diferencia en y sea menor que d
//     double dStrip = d;
//     int stripSize = strip.size();
//     for (int i = 0; i < stripSize; i++) {
//         for (int j = i + 1; j < stripSize && (strip[j].gety() - strip[i].gety()) < dStrip; j++) {
//             dStrip = min(dStrip, strip[i].distancia(strip[j]));
//         }
//     }
//
//     //FALLA EL COMO COMPROBAR LA FRANJA
//     /*
//     double dStrip = numeric_limits<double>::max();
//     if (!strip.empty()) {
//         int midStrip = strip.size() / 2;
//         // Llamadas recursivas para calcular la distancia mínima en la franja
//         double dStripl = distMinDivide(strip, 0, midStrip, "strip");
//         double dStripr = distMinDivide(strip, midStrip, strip.size() - 1, "strip");
//
//         dStrip = min(dStripl, dStripr);
//         //dStrip = distMinDivide(strip, 0, strip.size() - 1, "strip");
//     }
//     */
//
//
//     return min(d, dStrip);
// }
double distMinDivide(vector<Punto2D> &v, int izq, int der, const string& func) {

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