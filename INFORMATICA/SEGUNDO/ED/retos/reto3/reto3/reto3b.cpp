#include <iostream>
#include <list>

using namespace std;


//JUAN RECHE AGUILAR
//PABLO VARGAS DIAZ

const string SEPARATOR = "\n############################\n";

void representacion(const list<int> &L, int n=0) {

	cout << "Circulo" << "(" << n << "): ";

	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << SEPARATOR;
}

bool todos_iguales(const list<int> &list) {

	bool iguales = true;
	int list_0 = list.front(); //tomamos un valor como referencia

	for (int it: list) {
		if (it != list_0) iguales = false;
	}
	return iguales;
}

int circulo(list<int> &L) {

	int contador = 0;

	while (!todos_iguales(L)) {
		contador++;

		int first = L.front(); // Guardar el primer elemento
		list<int> new_list;	   // Creamos una lista auxiliar

		auto it = L.begin();

		while (it != L.end()) {
			int curr = *it;
			++it; // Avanzar el iterador
			int next = (it == L.end()) ? first : *it; // Siguiente elemento o circular al inicio
			new_list.push_back(abs(curr - next));
		}

		L.swap(new_list); // Reemplazar la lista original con la nueva
		representacion(L, contador);
	}

	return contador;
}


int main() {


	list<int> L = {8, 2, 5, 7};
	representacion(L);

	int result = circulo(L);
	cout << "P = " << result << endl;

	return 0;
}
