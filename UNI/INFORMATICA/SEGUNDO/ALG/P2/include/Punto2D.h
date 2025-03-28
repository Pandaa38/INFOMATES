#include<iostream>

#ifndef PUNTO2D_H
#define PUNTO2D_H


class Punto2D {
	int x;
	int y;

public:
	Punto2D();
	Punto2D(int x, int y);

	float distancia(const Punto2D& punto) const;
	int getx() const;
	int gety() const;
};

std::ostream &operator<<(std::ostream &os, const Punto2D &punto);
std::istream &operator>>(std::istream &is, Punto2D &punto);

bool operator<(const Punto2D &p1, const Punto2D &p2);
bool operator==(const Punto2D &p1, const Punto2D &p2);
bool operator!=(const Punto2D &p1, const Punto2D &p2);

#endif //PUNTO2D_H
