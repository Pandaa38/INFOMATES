#include<chrono>
#include<vector>
#include<iostream>
#include<time.h>

using namespace std;

// **************************************************************************************************************** //
int partition(vector<int> &vec, int low, int high) {

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

void quickSort(vector<int> &vec, int low, int high) {

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
// **************************************************************************************************************** //
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

// **************************************************************************************************************** //

int main(int argc, char const *argv[]) {

    int numvectors = argc - 1;
    srand(time(NULL));
    /*
    for(int i = 0; i < numvectors; i++) {
        size_t n = std::stoi(argv[i + 1]);
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = rand() % 1000;
        }

        auto start = chrono::high_resolution_clock::now();
        quickSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time quickSort tam " << n << ": " 
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < numvectors; i++) {
        size_t n = std::stoi(argv[i + 1]);
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = rand() % 1000;
        }

        auto start = chrono::high_resolution_clock::now();
        mergeSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time mergeSort tam " << n << ": " 
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }
    */

    std::cout << std::endl;

    /*
    for(int i = 0; i < numvectors; i++) {
        size_t n = std::stoi(argv[i + 1]);
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = rand() % 1000;
        }

        auto start = chrono::high_resolution_clock::now();
        bubbleSort(vec);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time bubbleSort tam " << n << ": " 
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }
    */
   cout << endl;
   cout << "QuickSort ordenado" << endl;

   for(int i = 0; i < numvectors; i++) {
        size_t n = std::stoi(argv[i + 1]);
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = j;
        }

        auto start = chrono::high_resolution_clock::now();
        quickSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time quicksort tam " << n << ": " 
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }
    cout << endl;
    cout << "MergeSort ordenado" << endl;
    for(int i = 0; i < numvectors; i++) {
        size_t n = std::stoi(argv[i + 1]);
        vector<int> vec(n);

        for (size_t j = 0; j < n; j++) {
            vec[j] = j;
        }

        auto start = chrono::high_resolution_clock::now();
        mergeSort(vec, 0, n - 1);
        auto end = chrono::high_resolution_clock::now();

        cout << "Time mergeSort tam " << n << ": " 
             << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us" << endl;
    }
    

    return 0;
}