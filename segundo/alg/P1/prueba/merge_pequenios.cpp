#include<chrono>
#include<vector>
#include<iostream>
#include<time.h>
#include<fstream>

using namespace std;

// **************************************************************************************************************** //
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    ofstream file("tiempos_merge_pequenios.csv");

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
        mergeSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time mergeSort tam " << n << ": " 
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns" << endl;
        file << n << ';'
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    }

    return 0;
}