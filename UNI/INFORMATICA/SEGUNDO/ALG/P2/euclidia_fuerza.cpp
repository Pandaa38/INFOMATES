#include<iostream>
#include<cmath>
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

int main() {

}