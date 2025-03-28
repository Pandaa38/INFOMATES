#include "Punto2D.h"
#include<iostream>
#include<cmath>

Punto2D::Punto2D() : x(0), y(0) {}
Punto2D::Punto2D(int x, int y) : x(x), y(y) {}

float Punto2D::distancia(const Punto2D& punto) const {
	int dx = abs(this->x - punto.x);
	int dy = abs(this->y - punto.y);
	return sqrt(dx * dx + dy * dy);
}

int Punto2D::getx() const {  return x;  }
int Punto2D::gety() const {  return y;  }

bool operator<(const Punto2D &p1, const Punto2D &p2) {
	return p1.getx() < p2.getx();
}
bool operator==(const Punto2D &p1, const Punto2D &p2) {
	return p1.getx() == p2.getx() && p1.gety() == p2.gety();
}
bool operator!=(const Punto2D &p1, const Punto2D &p2) {
	return !(p1 == p2);
}

std::ostream &operator<<(std::ostream &os, const Punto2D &punto){
	os << "(" << punto.getx() << ", " << punto.gety() << ")";
	return os;
}
std::istream &operator>>(std::istream &is, Punto2D &punto) {
	int x, y;
	char open, coma, close;
	is >> open >> x >> coma >> y >> close;
	//is >> x >> y;
	punto = Punto2D(x, y);
	return is;
}
