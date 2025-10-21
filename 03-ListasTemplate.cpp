#include <iostream>

using namespace std;

template <typename T> struct Nodo {
	T dato; // valor que contiene el nodo
	Nodo<T>* sig; // puntero al siguiente nodo
};

template <typename T> void push(Nodo<T>* &pila, T valor)
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;
	nuevo->sig = pila;
	pila = nuevo;
}

template <typename T> T pop(Nodo<T>* &pila)
{
	T valor = pila->dato;
	Nodo<T>* aux_elim = pila;
	pila = pila->sig;
	delete aux_elim;
	return valor;
}

template <typename T> void agregar(Nodo<T>*& cola, T valor)
{
	Nodo<T>* nuevo = new Nodo<T>;
	nuevo->dato = valor;
	nuevo->sig = nullptr;
	if (cola == nullptr) {
		cola = nuevo;
	} else {
		Nodo<T>* aux = cola;
		while (aux->sig != nullptr) //mientras que no sea el último
			aux = aux->sig;  //avanzo al siguiente
		aux->sig = nuevo;
	}
}

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

template <typename T> void mostrar(Nodo<T>* lista)
{
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}

template <typename T> bool buscar_lineal(T clave, Nodo<T>* lista, int (*criterio)(T, T))
{
	while (lista != nullptr) {
		if (criterio(lista->dato, clave) == 0)
			return true;
		lista = lista->sig;
	}
	return false;
}

int main()
{
	Nodo<int> *pila = nullptr;
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

	Nodo<string> *cola = nullptr;
	/* En la sentencia siguiente, si no especifico <string> da error
	  no matching function for call to
	  agregar(Nodo<std::__cxx11::basic_string<char> >*&, const char [4]
	  Esto se debe a que los literales cadena no son string sino arreglo
	  de caracteres */
	agregar<string>(cola, "uno");
	agregar(cola, "dos"s); //Esta alternativa válida de C++14 en adelante
	agregar(cola, string("tres")); //Otra es construir un string
	cout << endl << "Cola (uno dos tres)" << endl;
	mostrar(cola);
	cout << endl << "Eliminamos" << endl;
	while (cola != nullptr)
		cout << pop(cola) << endl;
	cout << endl << "Confirmamos cola vacía:" << endl;
	mostrar(cola);
	cout << "fin mostrar cola" << endl;

	agregar<string>(cola, "Juan");
	agregar(cola, "Pedro"s);
	agregar(cola, string("María"));
	cout << endl << "Datos" << endl;
	mostrar(cola);
	string nombre;
	cout << endl << "Ingrese el nombre a buscar: ";
	while (cin >> nombre) {
		if (buscar_lineal(nombre, cola, criterio_str))
			cout << nombre << " SI está en la lista" << endl;
		else
			cout << nombre << " NO está en la lista" << endl;
		cout << "Ingrese el nombre a buscar: ";
	}
	return 0;
}
