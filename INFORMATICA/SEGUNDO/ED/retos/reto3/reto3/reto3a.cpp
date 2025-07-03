#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;

// Pablo Vargas Diaz, Juan Reche Aguilar

template <typename T>
void Imprimir(T comienzo,T fin){
    for (auto it =comienzo; it!=fin; ++it){
        cout<<*it<<" ";
    }
}

bool esta_contenido (list<int> &l, list<int> &L) {
    if (l.empty()) return true;
    if (l.size() > L.size()) return false;


    for (auto itL = L.begin(); itL != L.end(); ++itL) {

        auto itTmp = itL;
        auto itSmall = l.begin();

        while (itSmall != l.end() && itTmp != L.end() && *itTmp == *itSmall) {
            ++itTmp;
            ++itSmall;
        }

        if (itSmall == l.end()) return true;
    }

    return false;
}

bool iscomb (vector<list<int>> &VL, list<int> &L) {
    int vector_total_size = 0;

    for (auto it = VL.begin(); it != VL.end(); ++it) {
        vector_total_size += it->size();
        if (!esta_contenido(*it,L)) return false;
    }

    if (vector_total_size != L.size()) return false;

    return true;
}


int main() {
    vector<list<int> >VL={{1,2,3},{4,5,6},{7,8}};

    list<int>L2={3,2,1,7,8,4,5,6};
    cout<<"L: ";
    Imprimir(L2.begin(),L2.end());
    if (iscomb(VL,L2))
        cout<<"VL esta en L"<<endl;
    else
        cout<<"VL no esta en L"<<endl;



}
