
#include <iostream>
using namespace std;


int main(){

    int A[] = {1,2,3,4,5};
    int tam = 5;

    for(int i = 0; i < tam; i++){
        cout << A[i] << ", ";
    }
    cout << endl;

    
    for(int i = 0; i < tam/2; i++) {
        int temp = A[i];
        A[i] = A[(tam-1)-i];
        A[(tam-1)-i] = temp;
    }

    for(int i = 0; i < tam; i++){
        cout << A[i] << ", ";
    }
    cout << endl;


    return 0;
}