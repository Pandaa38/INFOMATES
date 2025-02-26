#include <iostream>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;


queue<int> mergeSortedStackQueue(stack<int> A, queue<int> B) {

    queue<int> result;

    while( !A.empty() && !B.empty()) {

        if(A.top() <= B.front()) {
            result.push(A.top());
            A.pop();
        }else {
            result.push(B.front());
            B.pop();
        }
    }

    while(!A.empty()) {
        result.push(A.top());
        A.pop();
    }
    while(!B.empty()) {
        result.push(B.front());
        B.pop();
    }

    return result;
}

int main()
{
    queue<int> cola;
    stack<int> stack;
    char p;

    std::cout << "COLA: " << std::endl;
    while((p = std::cin.get()) != '\n') {
        cola.push(p - '0');  // Convertimos el carácter a número entero
    }

    std::cout << "PILA: " << std::endl;
    while((p = std::cin.get()) != '\n') {
        stack.push(p - '0');  // Convertimos el carácter a número entero
    }

    queue<int> resultado = mergeSortedStackQueue(stack, cola);

    std::cout << "RESULTADO: ";
    while (!resultado.empty()) {
        std::cout << resultado.front() << " ";
        resultado.pop();
    }
    std::cout << std::endl;

    return 0;
}
