#include <iostream>
#include "listas.hpp"
using namespace std;

template <typename T>
int contar(Nodo<T>* pila) {
    int cantidad = 0;
    Nodo<T>* aux = pila;
    while (aux != nullptr) {
        cantidad++;
        aux = aux->sig; 
    }
    return cantidad;
}

template <typename T> void swap(Nodo<T>* &pila)
{
    T primero;
    T segundo;
    int contador= contar(pila);
    if(contador >=3)
    {
        primero=pop(pila);
        segundo=pop(pila);
        push(pila,primero);
        push(pila, segundo);
    }
}

int main()
{
    Nodo<int> *pila = nullptr;
	push(pila, 1);
	push(pila, 2);
    push(pila, 3);
    swap(pila);
}