#include<iostream>
#include<fstream>
//#include<cmath>
#include <vector>
#include<algorithm>
#include <limits>


#include"Punto2D.h"

using namespace std;

float distMin(vector<Punto2D> v, int izq, int der) {

	if (v.size() == 2) {
		float dist = v.front().distancia(v.back());
		cout << "distncia v==2: " << dist << endl;
		return dist;
	}
	else if (v.size() == 1) {
		return numeric_limits<float>::max();
	}
	int mid = (der + izq) / 2;
	Punto2D midPoint = v[mid];

	float dl = distMin(v, izq, mid);
	float dr = distMin(v, mid + 1, der);
	float d = min(dl, dr);

	vector<Punto2D> strip;
	for (int i = izq; i <= der; ++i) {
		if (abs(v[i].getx() - midPoint.getx()) < d) {
			strip.push_back(v[i]);
		}
	}

	float dStrip = distMin(strip, 0, strip.size() - 1);

	return min(d, dStrip);
}

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
	cout << "Puntos: " << endl;
	for (Punto2D i:puntos) {
		cout << i << endl;
	}

	//funcion recursiva divide y venceras
	float minDist = distMin(puntos, 0, puntos.size() - 1);

	cout << endl;
	cout << "Distancia minima: " << minDist << endl;

	return 0;
}