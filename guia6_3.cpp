#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
#include <Nodo>
using namespace std;

struct Deuda{
    string cliente;
    int mes;
    int cantidad;

};
const int lcliente =8;

struct Nodo {
    Deuda info;
    Nodo* sig;
};

fstream& operator>>(fstream &fs, Deuda &deuda) {
    deuda.cliente = readstring(fs, lcliente);
    fs.read(reinterpret_cast<char*>(&deuda.mes), sizeof(deuda.mes));
    fs.read(reinterpret_cast<char*>(&deuda.cantidad), sizeof(deuda.cantidad));
    return fs;
}


list<Deuda> leerDeuda() {
    list<Deuda> deudas;
    fstream archivo("datos03.bin", ios::binary | ios::in);
    if (!archivo) {
        cout << "No se pudo abrir datos03.bin" << endl;
        return deudas;
    }
    Deuda deudita;
    while (archivo >> deudita) {
        if (!archivo) break; 
        deudas.push_back(deudita);
    }
    archivo.close();
    return deudas;
}

template <typename T>
void ordenar(list<T> &lista, bool (*criterio)(const T&, const T&)) {
    lista.sort(criterio); 
}


bool criterio_nombre(const Deuda &a, const Deuda &b) {
    return a.cliente < b.cliente;
}

bool criterio_mes(const Deuda &a, const Deuda &b) {
    return a.mes < b.mes;
}

void consolidarDeudas(Nodo* &lista) {
    Nodo* p = lista;
    while (p != nullptr) {
        Nodo* anterior = p;
        Nodo* q = p->sig;
        while (q != nullptr) {
            if (p->info.cliente == q->info.cliente && p->info.mes == q->info.mes) {
                p->info.cantidad += q->info.cantidad;
                anterior->sig = q->sig;
                delete q;
                q = anterior->sig;
            } else {
                anterior = q;
                q = q->sig;
            }
        }
        p = p->sig;
    }
}

template <typename T> void mostrar(Nodo<T>* lista)
{
	while (lista != nullptr) {
		cout << lista->dato << endl;
		lista = lista->sig;
	}
}

int main()
{
    list<Deuda> deudas = leerDeuda();
    cout << "Ordenadas por nombre:\n";
    ordenar(deudas, criterio_nombre);
    for (auto &d : deudas) {
        cout << d.cliente << " " << d.mes << " " << d.cantidad << endl;
    }

    cout << "\nOrdenadas por mes:\n";
    ordenar(deudas, criterio_mes);
    for (auto &d : deudas) {
        cout << d.cliente << " " << d.mes << " " << d.cantidad << endl;
    }
    consolidarDeudas(deudas);
    mostrar(deudas);
    return 0;
	
}