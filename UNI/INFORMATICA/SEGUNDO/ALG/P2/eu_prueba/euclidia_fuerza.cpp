#include<iostream>
#include<fstream>
//#include<cmath>
#include <vector>
#include<algorithm>
#include <limits>
#include<chrono>


#include"Punto2D.h"

using namespace std;

double distMinFuerza(vector<Punto2D> puntos) {
	float min_dist = numeric_limits<float>::max();
	//Punto2D min1;
	//Punto2D min2;

	for (Punto2D i:puntos) {
		for(Punto2D j:puntos) {
			if (i != j) {
				float new_dist = i.distancia(j);
				if (new_dist < min_dist) {
					min_dist = new_dist;
					//min1 = i;
					//min2 = j;
				}
			}
		}
	} //O(n^2)

	return min_dist;
}

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
	double min_dist = distMinFuerza(puntos);
	auto end = chrono::high_resolution_clock::now();

	cout << "Tiempo fuerza tam " << puntos.size() << ": "
		 << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
	cout << "Distancia minima: " << min_dist << endl;

	return 0;
}