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

int main(int argc, char const *argv[]) {


	/*
	if (argc == 2) {
		ifstream file(argv[1]);
		Punto2D punto_2d;
		while (file >> punto_2d) {
			puntos.push_back(punto_2d);
		}
		file.close();
	}
	else {

	}
	*/

	ofstream file("../tiempos_fuerza.csv");
	srand(time(NULL));

	for (int i = 5; i <= 105; i = i + 10) {
		//creacion array
		vector<Punto2D> puntos(i);

		for(int j = 0; j < i; j++) {
			puntos.push_back(Punto2D(rand()%100, rand()%100));
		}

		//sort(puntos.begin(), puntos.end()); //O(nlog(n)
		auto start = chrono::high_resolution_clock::now();
		double min_dist = distMinFuerza(puntos);
		auto end = chrono::high_resolution_clock::now();

		/*
		cout << "Puntos: " << endl;
		for (Punto2D i:puntos) {
			cout << i << endl;
		}
		cout << endl;
		cout << "Distancia minima: " << min_dist << " entre los puntos: "<< min1 << " y " << min2 << endl;
		*/

		cout << "Time fuerza tam " << i << ": "
			 << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
		file << i << ","
			 << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
	}
	file.close();
	return 0;
}