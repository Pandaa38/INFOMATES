#include<chrono>
#include<vector>
#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

// **************************************************************************************************************** //
int partition(vector<int> &vec, long int low, long int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int> &vec, long int low, long int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}
// **************************************************************************************************************** //

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    ofstream file("tiempos_quick_pequenios.csv");

    vector<int> tamanios;
    for(int i = 2; i <= 50; i+= 2){
        tamanios.push_back(i);
    }

    for(int i = 0; i < tamanios.size(); i++) {
        long int n = tamanios[i];
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = rand();
        }

        auto start = chrono::high_resolution_clock::now();
        quickSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time quickSort tam " << n << ": "
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
        file << n << ';'
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    }

    return 0;
}