#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>

using namespace std;

struct Ventas
{
    string modelo;
    int cantidad;
};
const int lmodelo=10;

template <typename Nodo>
struct Nodo{
    Ventas info;
    Nodo* sig; 
};

int criterio_nombre(Ventas a, Ventas b)
{
	return (a.modelo < b.modelo) ? -1 : (a.modelo > b.modelo);
}

fstream& operator>>(fstream &fs, Ventas &venta) {
    venta.modelo = readstring(fs, lmodelo);
    fs.read(reinterpret_cast<char*>(&venta.cantidad), sizeof(venta.cantidad));
    return fs;
}


list<Ventas> leerVentas() {
    list<Ventas> venta;
    fstream archivo("datos01.bin", ios::binary | ios::in);
    if (!archivo) {
        cout << "No se pudo abrir datos01.bin" << endl;
        return venta;
    }
    Ventas vent;
    while (archivo >> vent) {
        if (!archivo) break; 
        venta.push_back(vent);
    }
    archivo.close();
    return venta;
}

template <typename T>
void ordenar(list<T> &lista, bool (*criterio)(const T&, const T&)) {
    lista.sort(criterio); 
}

void consolidarVentas(Nodo* &lista) {
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