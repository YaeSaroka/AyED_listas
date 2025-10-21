#include <iostream>

using namespace std;

struct Manada {
	string descrip;	//tipo de animal
	int cab;	//cantidad de cabezas
	double peso;	//peso total
};

struct Nodo {
	Manada dato; // valor que contiene el nodo
	Nodo* sig; // puntero al siguiente nodo
};

// Notar que en push, pop y agregar no cambian en nada
// salvo el tipo de dato int por Manada
void push(Nodo* &pila, Manada valor)
{
	Nodo* nuevo = new Nodo;
	nuevo->dato = valor;
	nuevo->sig = pila;
	pila = nuevo;
}

Manada pop(Nodo* &pila)
{
	Manada valor = pila->dato;
	Nodo* aux_elim = pila;
	pila = pila->sig;
	delete aux_elim;
	return valor;
}

void agregar(Nodo*& cola, Manada valor)
{
	Nodo* nuevo = new Nodo;
	nuevo->dato = valor;
	nuevo->sig = nullptr;
	if (cola == nullptr) {
		cola = nuevo;
	} else {
		Nodo* aux = cola;
		while (aux->sig != nullptr) //mientras que no sea el último
			aux = aux->sig;  //avanzo al siguiente
		aux->sig = nuevo;
	}
}

ostream& operator << (ostream &os, Manada m)
{
	os << m.descrip << '\t' << m.cab << '\t' << m.peso;
	return os;
}

void mostrar(Nodo* lista)
{
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}

int criterio_TipoAnimal(Manada a, Manada b)
{
	return a.descrip.compare(b.descrip);
}

bool buscar_lineal(Manada clave, Nodo* lista, int criterio(Manada, Manada)) //Notar que no puse (*criterio)
{
	while (lista != nullptr) {
		if (criterio(lista->dato, clave) == 0)
			return true;
		lista = lista->sig;
	}
	return false;
}

void ingresarManada(Manada &m)
{//Lee los datos y los coloca en la estructura que nos pasan como parámetro
	cout << "Tipo de animal:\t\t";
	cin >> m.descrip;
	cout << "Cantidad de cabezas:\t";
	cin >> m.cab;
	cout << "Peso total:\t\t";
	cin >> m.peso;
	cout << endl;
}

Manada crearManada(void)
{// devuelve una estructura, así que no hace falta pasarle parámetro
	Manada m;
	cout << "Tipo de animal:\t\t";
	cin >> m.descrip;
	cout << "Cantidad de cabezas:\t";
	cin >> m.cab;
	cout << "Peso total:\t\t";
	cin >> m.peso;
	cout << endl;
	return m;
}

int main()
{
	Nodo *pila = nullptr; //MUY IMPORTANTE no olvidar de inicializar en nullptr
	Manada m;

	cout << "----- Usando pila" << endl;
	cout << "Apilo Perros"<< endl;
	push(pila, {"Perros", 5, 100.3});
	cout << "Apilo Novillos" << endl;
	push(pila, {"Novillos", 30, 12607.5});
	cout << "Ingrese uno manualmente" << endl << endl;
	ingresarManada(m);
	push(pila, m);
	cout << "Listando Pila:" << endl;
	mostrar(pila);
	cout << endl << "Eliminamos" << endl;
	while (pila != nullptr)
		cout << pop(pila) << endl;
	cout << endl << "Confirmamos pila vacía:" << endl;
	mostrar(pila);
	cout << "fin mostrar pila" << endl;

	Nodo* cola = nullptr; //MUY IMPORTANTE no olvidar de inicializar en nullptr
	cout << "------------------------" << endl;
	cout << "----- Usando cola" << endl;
	cout << "Agrego Perros"<< endl;
	agregar(cola, {"Perros", 5, 100.3});
	cout << "Agrego Novillos" << endl;
	agregar(cola, {"Novillos", 30, 12607.5});
	cout << "Ingrese uno manualmente" << endl << endl;
	agregar(cola, crearManada());
	//También podría haber hecho m = crearManada(); agregar(cola, m);
	cout << endl << "Listando cola:" << endl;
	mostrar(cola);
	cout << endl << "Eliminamos" << endl;
	while (cola != nullptr)
		cout << pop(cola) << endl;
	cout << endl << "Confirmamos cola vacía:" << endl;
	mostrar(cola);
	cout << "fin mostrar cola" << endl;

	cout << endl << "Ingreso para búsqueda:" << endl;
	agregar(cola, crearManada());
	agregar(cola, crearManada());
	agregar(cola, crearManada());
	cout << endl << "Datos" << endl;
	mostrar(cola);

	cout << "------------------------" << endl;
	cout << "Ingrese El tipo de animal a buscar: " << endl;
	//IMPORTANTE no ingreso un string suelto, sino dentro de una Manada
	while (cin >> m.descrip) { //Ingresar EOF para cortar
		if (buscar_lineal(m, cola, criterio_TipoAnimal)) //Notar que la clave es una Manada
			cout << "SI está en la lista" << endl;
		else
			cout << "NO está en la lista" << endl;
		cout << endl << "Ingrese El tipo de animal a buscar: "<< endl;
	}
	return EXIT_SUCCESS;
}
