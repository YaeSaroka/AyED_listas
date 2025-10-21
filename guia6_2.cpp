#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
using namespace std;

struct OrdenCompra{
    int id;
    string cliente;
    string producto;
    int cantidad;
};
const int lcliente =8;
const int lproducto=10;
fstream& operator>>(fstream &fs, OrdenCompra &o) {
    fs.read(reinterpret_cast<char*>(&o.id), sizeof(o.id));
    o.cliente = readstring(fs, lcliente);
    o.producto = readstring(fs, lproducto);
    fs.read(reinterpret_cast<char*>(&o.cantidad), sizeof(o.cantidad));
    return fs;
}


list<OrdenCompra> leerOrdenCompras() {
    list<OrdenCompra> orden;
    fstream archivo("datos02.bin", ios::binary | ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir datos02.bin" << endl;
        return orden;
    }
    OrdenCompra oc;
    while (archivo >> oc) {
        if (!archivo) break; 
        orden.push_back(oc);
    }
    archivo.close();
    return orden;
}
int main()
{
   

	
}