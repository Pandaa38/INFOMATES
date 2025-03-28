#include<iostream>
#include<cmath>
#include <vector>
//#include<random>
//#include<time.h>
using namespace std;

struct Punto2D {
	int x;
	int y;
};
int Distancia(Punto2D p1, Punto2D p2) {
	int dx = abs(p1.x - p2.x);
	int dy = abs(p1.y - p2.y);
	return sqrt(dx*dx + dy*dy);
}
pair<Punto2D, Punto2D> min_dist(vector<Punto2D>) {




	return make_pair(Punto2D(0, 0), Punto2D(0, 0));
}

int main(int argc, char const *argv[]) {
	vector<Punto2D> puntos;
	int tam = stoi(argv[1]);

	//if (argc > 2) {
		srand(time(NULL));

		for(int i = 0; i < tam; i++) {
			Punto2D p;
			p.x = rand() % 100;
			p.y = rand() % 100;
			puntos.push_back(p);
		}
	//}



}