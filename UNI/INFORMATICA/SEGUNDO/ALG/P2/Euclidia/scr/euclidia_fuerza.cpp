#include<iostream>
#include<fstream>
//#include<cmath>
#include <vector>
#include<algorithm>


#include"Punto2D.h"

using namespace std;

int main(int argc, char const *argv[]) {
	vector<Punto2D> puntos;

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

	sort(puntos.begin(), puntos.end()); //O(nlog(n)

	float min_dist = puntos[0].distancia(puntos[1]);
	Punto2D min1 = puntos[0];
	Punto2D min2 = puntos[1];

	for (Punto2D i:puntos) {
		for(Punto2D j:puntos) {
			if (i != j) {
				float new_dist = i.distancia(j);
				if (new_dist < min_dist) {
					min_dist = new_dist;
					min1 = i;
					min2 = j;
				}
			}
		}
	} //O(n^2)

	cout << "Puntos: " << endl;
	for (Punto2D i:puntos) {
		cout << i << endl;
	}
	cout << endl;
	cout << "Distancia minima: " << min_dist << " entre los puntos: "<< min1 << " y " << min2 << endl;

	return 0;
}