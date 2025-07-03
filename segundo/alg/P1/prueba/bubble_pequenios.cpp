#include<chrono>
#include<vector>
#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
  
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}
int main(int argc, char const *argv[]) {

    srand(time(NULL));
    
    ofstream file("tiempos_bubble_pequenios.csv");

    vector<int> tamanios;
    for(int i = 2; i <= 50; i+= 2){
        tamanios.push_back(i);
    }

    for(int i = 0; i < tamanios.size(); i++) {
        long int n = tamanios[i];
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = rand() % 100;
        }

        auto start = chrono::high_resolution_clock::now();
        bubbleSort(vec);
        auto end = chrono::high_resolution_clock::now();
	
        cout << "Time bubbleSort tam " << n << ": " 
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
        file << n << ";"
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    }
    file.close();
    
    return 0;
}
