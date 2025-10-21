#include <iostream>
#include "listas.hpp"

using namespace std;

struct Pizza {
	string gusto;
	int cant;
};

// ============ ENTEROS
int criterio_int(int a, int b)
{
	return a - b;
}

// ============ STRING
int criterio_str(string a, string b)
{
	return (a < b) ? -1 : (a > b);
}

// ============ Pizza buscando por GUSTO
int criterio_pizza(Pizza a, Pizza b)
{
	if (a.gusto == b.gusto)
		return 0;
	else
		return a.gusto > b.gusto ? 1 : -1;
}

ostream& operator << (ostream &os, Pizza& p)
{
	os << p.gusto << " : " << p.cant;
	return os;
}

template <typename T> void mostrar(Nodo<T>* lista)
{
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}

template <typename T> T* buscar_lineal(T clave, Nodo<T>* lista, int criterio(T, T))
{
	while (lista != nullptr) {
		if (criterio(lista->dato, clave) == 0)
			return &lista->dato;
		lista = lista->sig;
	}
	return nullptr;
}

int main()
{
	Nodo<int> *pila = nullptr;
	//pop(pila);//provoco error para ver como funciona
	push(pila, 1);
	push(pila, 2);
	push(pila, 3);
	cout << "Pila (1 2 3)" << endl;
	mostrar(pila);
	cout << endl << "Eliminamos" << endl;
	while (pila != nullptr)
		cout << pop(pila) << endl;
	cout << endl << "Confirmamos pila vacía:" << endl;
	mostrar(pila);
	cout << "fin mostrar pila" << endl;
	cout << "-----------------" << endl;

	Nodo<string> *cola = nullptr;
	agregar(cola, "uno"s);
	agregar(cola, "dos"s);
	agregar(cola, "tres"s);
	cout << endl << "Cola (uno dos tres)" << endl;
	mostrar(cola);
	cout << endl << "Eliminamos" << endl;
	while (cola != nullptr)
		cout << pop(cola) << endl;
	cout << endl << "Confirmamos cola vacía:" << endl;
	mostrar(cola);
	cout << "fin mostrar cola" << endl;
	cout << "-----------------" << endl;

	agregar(cola, "Juan"s);
	agregar(cola, "Pedro"s);
	agregar(cola, "María"s);
	cout << endl << "Datos para la búsqueda" << endl;
	mostrar(cola);
	string nombre;
	cout << endl << "Ingrese el nombre a buscar: ";
	while (cin >> nombre) {
		if (buscar_lineal(nombre, cola, criterio_str) != nullptr)
			cout << nombre << " SI está en la lista" << endl;
		else
			cout << nombre << " NO está en la lista" << endl;
		cout << "Ingrese el nombre a buscar: ";
	}

	cin.clear(); // como force EOF debo limpiar los bits de error
	clearerr(stdin);
	cout << endl << "-----------------" << endl;
	Nodo<Pizza> *lista = nullptr;
	agregar(lista, {"Muza", 4});
	agregar(lista, {"Fugazzeta", 1});
	agregar(lista, {"Especial", 3});
	agregar(lista, {"Pizzaiola", 2});
	agregar(lista, {"Muza", 8}); //Notar que si busco Muza encuentra la primera
	cout << endl << "Pedidos en la lista:" << endl;
	mostrar(lista);
	Pizza pizzaClave;
	Pizza *ptrPizza;
	cout << endl << "Ingrese el gusto a buscar: ";
	while (cin >> pizzaClave.gusto) {
		ptrPizza = buscar_lineal(pizzaClave, lista, criterio_pizza);
		if (ptrPizza != nullptr)
			cout << pizzaClave.gusto << " SI está en la lista ==> " 
			     << *ptrPizza << endl;
		else
			cout << pizzaClave.gusto << " NO está en la lista" 
			     << endl;
		cout << "Ingrese el nombre a buscar: ";
	}
	return EXIT_SUCCESS;
}
