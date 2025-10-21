#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
using namespace std;

//ESTRUCTURAS DE DATOS

template <typename T>
struct Nodo 
{
    T dato;
    Nodo<T>* sig;
};

struct Registro
{
    string Ciudad;
    string Producto;
    string MedioPago;
    int Cantidad;
    float Monto;
};

const int longCiudad=10;
const int longProducto=18;
const int longMedioPago=2;

struct MedioPago
{
    string MedioPago;
    int CantidadVentas=0;
};

struct Producto
{
    string Producto;
    float Monto=0;
    int Cantidad_Ventas=0;
    Nodo<MedioPago>* venta_por_medio= nullptr;
};


struct Ciudad
{
    string Ciudad;
    int Cantidad_Productos_Vendidos=0;
    int Cantidad_Unidades_Vendidas=0;
    Nodo<Producto>* lista_productos=nullptr; 
};

fstream& operator>> (fstream &fs, Registro &registro)
{
    registro.Ciudad=readstring(fs, longCiudad);
    registro.Producto=readstring(fs, longProducto);
    registro.MedioPago=readstring(fs, longMedioPago);
    fs.read(reinterpret_cast<char*>(&registro.Cantidad),sizeof(registro.Cantidad));
    fs.read(reinterpret_cast<char*>(&registro.Monto),sizeof(registro.Monto));
    return fs;
}

//CRITERIOS
int CriterioAscendente(string a, string b)
{
    if(a > b) return 1; //si a es mayor a b, a va dsp que b
    if(a<b) return -1; //a va antes q b
    return 0; //a igual a b
}

Nodo<Ciudad>* InsertarOrdenadoPorCiudad(Nodo<Ciudad>* &lista_ciudades, Ciudad ciudad)
{
    Nodo<Ciudad>* actual=lista_ciudades;
    Nodo<Ciudad>* anterior=nullptr;

    while(actual!= nullptr && CriterioAscendente(actual->dato.Ciudad, ciudad.Ciudad)<0)
    {
        anterior=actual;
        actual=actual->sig;
    }
    if(actual!= nullptr && CriterioAscendente(actual->dato.Ciudad,ciudad.Ciudad)==0)
    {
        return actual;
    }
    else
    {
        Nodo<Ciudad>* nuevo=new Nodo <Ciudad>;
        nuevo->dato=ciudad;
        if(anterior==nullptr)
        {
            lista_ciudades=nuevo;
        }
        else
        {
            anterior->sig=nuevo;
        }
        nuevo->sig=actual;
        return nuevo;
    }
}

Nodo<Producto>* InsertarOrdenadoPorProducto(Nodo<Producto>* &lista_productos, Producto prod)
{
    Nodo<Producto>* actual=lista_productos;
    Nodo<Producto>* anterior=nullptr;

    while(actual!= nullptr && CriterioAscendente(actual->dato.Producto, prod.Producto)<0)
    {
        anterior=actual;
        actual=actual->sig;
    }
    if(actual!= nullptr && CriterioAscendente(actual->dato.Producto,prod.Producto)==0)
    {
        return actual;
    }
    else
    {
        Nodo<Producto>* nuevo=new Nodo <Producto>;
        nuevo->dato=prod;
        if(anterior==nullptr)
        {
            lista_productos=nuevo;
        }
        else
        {
            anterior->sig=nuevo;
        }
        nuevo->sig=actual;
        return nuevo;
    }
}

int main()
{
    Nodo<Ciudad>* lista_ciudades= nullptr;
    Registro registro;
    fstream archivo("datos02.dat", ios::binary | ios::in);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo datos02.dat\n";
        return 1;
    }

    while (archivo >> registro)
    {
        Ciudad ciu;
        ciu.Ciudad=registro.Ciudad;
        ciu.Cantidad_Productos_Vendidos=1;
        ciu.Cantidad_Unidades_Vendidas=registro.Cantidad;
        ciu.lista_productos=nullptr;

        Nodo<Ciudad>* nodo_ciudad=InsertarOrdenadoPorCiudad(lista_ciudades,ciu);

        Producto prod;
        prod.Producto=registro.Producto;
        prod.Cantidad_Ventas=registro.Cantidad;
        prod.Monto=registro.Monto;
        prod.venta_por_medio=nullptr;

        Nodo<Producto>* nodo_producto= InsertarOrdenadoPorProducto(nodo_ciudad->dato.lista_productos,prod);
    
        MedioPago medio_pago;
        medio_pago.MedioPago=registro.MedioPago;
        medio_pago.CantidadVentas=1;

        agregar(nodo_producto->dato.venta_por_medio, medio_pago);
    }

    Nodo<Ciudad>* listado_final=lista_ciudades;
    while (listado_final != nullptr)
    {
    cout << "CIUDAD: " << listado_final->dato.Ciudad
         << " Cantidad de productos vendidos: " << listado_final->dato.Cantidad_Productos_Vendidos
         << " Cantidad de unidades vendidas: " << listado_final->dato.Cantidad_Unidades_Vendidas << endl;

    Nodo<Producto>* prod = listado_final->dato.lista_productos;
    while (prod != nullptr)
    {
        cout << "  PRODUCTO: " << prod->dato.Producto
             << " Monto: " << prod->dato.Monto
             << " Cantidad de ventas: " << prod->dato.Cantidad_Ventas << endl;

        Nodo<MedioPago>* mp = prod->dato.venta_por_medio;
        while (mp != nullptr)
        {
            cout << "    Medio de pago: " << mp->dato.MedioPago
                 << " Cantidad de ventas: " << mp->dato.CantidadVentas << endl;
            mp = mp->sig;
        }

        prod = prod->sig;
    }

    listado_final = listado_final->sig;
}
    
    return 0;
}

