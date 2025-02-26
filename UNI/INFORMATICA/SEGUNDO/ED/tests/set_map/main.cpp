#include <iostream>
#include <set>
#include <map>
#include <algorithm>

#include <vector>
#include <list>

using namespace std;

void esta_en_conjunto(vector<set<int>> &v, map<int,list<int> > &recuento ){

	for (int i = 0; i < v.size(); i++) {
		for (int num:v[i]) {
			recuento[num].push_back(i);
		}
	}

	//mostrar en pantalla
	for (const auto &entry : recuento) {
		cout << entry.first << ": {";
		for (auto it = entry.second.begin(); it != entry.second.end(); ++it) {
			if (it != entry.second.begin()) cout << ", ";
			cout << *it;
		}
		cout << "}" << endl;
	}
}



bool subconjunto_propio (vector< set<int> > &v) {

	bool propio = true;

	for (int i = 0; i < v.size()-1; i++) {
		for (int num:v[i]) {
			if (v[i+1].find(num) == v[i+1].end()) propio = false;
		}
	}

	return propio;
}



bool contiene_parejas(vector< set<int> > &sw, int n){
	for (int i=0; i<n-1; i++){
		for (int j=i+1; j<n; j++){
			bool enc=false;
			for (auto it=sw.begin(); it!=sw.end() && !enc; ++it){
				if (it->find(i)!=it->end() && it->find(j)!=it->end())
					enc=true;
			}
			if (!enc) return false;
		}
	}
	return true;
}

int main(){

	vector<set<int>> v = {{1,2},{1,2,3}, {1,2,3,4}};
	vector<set<int>> v2 = {{1,2},{1,2,3}, {1,2,4}};

	//map<int,list<int> > recuento;
	//esta_en_conjunto(v, recuento);

	cout << "v es propio?"<< boolalpha << subconjunto_propio(v) << endl;
	cout << "v2 es propio?" << boolalpha << subconjunto_propio(v2) << endl;


	return 0;
}