#include <set>
#include <vector>
#include <iostream>

using namespace std;

/**
* @brief Imprime un conjunto de enteros
* @param conjunto Set a imprimir
*/
void muestraConj(set<int> &conjunto) {
    set<int>::iterator it;

    cout << "{ ";
    for (it=conjunto.begin(); it != conjunto.end(); ++it) {
        // recorre el conjunto y muestra cada elemento
        cout << *it << " ";
    }
    cout << "} ";
}

/**
* @brief Imprime un vector de conjuntos de enteros
* @param v Vector a imprimir
*/
void muestraVector(vector< set<int> > &v) {
    vector< set<int> >::iterator it;

    cout << "{ ";
    for (it=v.begin(); it != v.end(); ++it) {
        // recorre el vector y muestra cada conjunto
        muestraConj(*it);
    }
    cout << "} ";
}

/**
* @brief Comprueba si un vector de conjuntos es un subconjunto propio
* @param v conjuntos para comprobar
* @return true si v es subconjunto propio y false en caso contrario
*/
/*
bool subconjunto_propio (vector< set<int> > &v) {
    // FUNCIÓN QUE HAY QUE IMPLEMENTAR
    bool propio = true;

    for (int i = 0; i < v.size()-1; i++) {
        for (int num:v[i]) {
            if (v[i+1].find(num) == v[i+1].end()) propio = false;
        }
    }

    return propio;
}
*/

//Con el fin de mejor modularizacion creamos 2 funiones:
//Comprueba si A esta incluido en B
bool incluido(set<int> &A, set<int> &B) {
    bool incluido = true;

	//if(size(A)>=size(B) false
	
    if (size(B) < size(A))
        incluido = false;
    else{
        for (int num:A) {
            if (B.find(num) == B.end()) incluido = false;
        }
    }

    return incluido;
}
//usa icluido para ver si cada set esta incluido en el siguiente
bool subconjunto_propio (vector< set<int> > &v) {

    bool propio = true;

    for (int i=0; i<size(v)-1; i++) {
        propio = incluido(v[i], v[i+1]); //comprobamos si el set i esta incluido en el siguiente(i+1)
    }

    return propio;
}

int main() {
    vector< set<int> > v;
    bool result;
    
    // se inicializan los vectores que formarán el conjunto
    int c1[3]={1,2,3};
    int c2[4]={1,2,3};
    int c3[5]={1,2,3,4,5};
    //int c3[4]={1,3,4,6}; // por si quieres probar otro ejemplo
    
    set<int> conj1(c1,c1+3), conj2(c2,c2+4), conj3(c3,c3+5);
    // para probar el otro ejemplo, comenta la línea anterior y descomenta la siguiente
    // set<int> conj1(c1,c1+3), conj2(c2,c2+4), conj3(c3,c3+4);


    // se insertan los conjuntos en el vector
    v.push_back(conj1);
    v.push_back(conj2);
    v.push_back(conj3);

    // se muestra el vector de ejemplo
    cout << "El vector de ejemplo: ";
    muestraVector(v);

    // se llama a la función para comprobar si es subconjunto propio
    result = subconjunto_propio (v);
    if (result == true)
        cout << " es propio" << endl;
    else
        cout << " no es propio" << endl;
}
