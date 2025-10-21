#include <iostream>
#include "listas.hpp"

using namespace std;

template <typename T> void mostrar(Nodo<T>* lista)
{
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}
template <typename T> void dup(Nodo<T>* &pila)
{
    T primero;
    if(pila!=nullptr)
    {
        primero=pop(pila);
        push(pila,primero);
        push(pila, primero);
    }
}

int main()
{
	Nodo<int> *pila = nullptr;
	push(pila, 1);
	push(pila, 2);
	cout << "Pila (1 2)" << endl;
	mostrar(pila);
    dup(pila);
    cout<<pila<<endl;

}