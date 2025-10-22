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

void CantidadVentasPorMedioPago (Nodo<Ciudad>* listado_ciudad)
{
    Nodo<Ciudad>* actual=listado_ciudad;
    int contador_ventas_bv=0;
    int contador_ventas_ef=0;
    int contador_ventas_tc=0;
    int contador_ventas_td=0;

    while (actual!=nullptr)
    {
        Nodo<Producto>* producto_Actual= actual->dato.lista_productos;
        while(producto_Actual!=nullptr)
        {
            Nodo<MedioPago>* medio_Actual= producto_Actual->dato.venta_por_medio;
            while (medio_Actual!=nullptr)
            {
                if(medio_Actual->dato.MedioPago == "BV")
                {
                    contador_ventas_bv++;
                    medio_Actual=medio_Actual->sig;
                }
                else if( medio_Actual->dato.MedioPago == "EF")
                {
                    contador_ventas_ef++;
                    medio_Actual=medio_Actual->sig;
                }
                else if( medio_Actual->dato.MedioPago == "TC")
                {
                    contador_ventas_tc++;
                    medio_Actual=medio_Actual->sig;
                }
                else
                {
                    contador_ventas_td++;
                    medio_Actual=medio_Actual->sig;
                }
            }
            producto_Actual=producto_Actual->sig;
            
        }
        actual=actual->sig;
        
    }
    cout<<"TOTAL VENTAS POR MEDIO DE PAGO: "<<endl;
    cout<< "BV: "<<contador_ventas_bv<<endl;
    cout<<"EF: "<<contador_ventas_ef<<endl;
    cout<<"TC: "<<contador_ventas_tc<<endl;
    cout<<"TD: "<<contador_ventas_td<<endl;
    
}

int BuscarPorProducto_MedioPago(Nodo<Ciudad>* listado_ciudades, string producto_buscado, string medio_buscado)
{
    Nodo<Ciudad>* ciudadActual=listado_ciudades;
    
   
    int contador_ventas=0;

    while (ciudadActual!=nullptr)
    {
        Nodo<Producto>* productoActual=ciudadActual->dato.lista_productos;
        while (productoActual!=nullptr)
        {
            Nodo<MedioPago>* medio_actual= productoActual->dato.venta_por_medio;
            while (medio_actual!=nullptr)
            { 
                if(productoActual->dato.Producto==producto_buscado && medio_actual->dato.MedioPago==medio_buscado)
                {
                    contador_ventas++;
                }
                medio_actual=medio_actual->sig;   
            }
            productoActual=productoActual->sig;
        }
        ciudadActual=ciudadActual->sig;
    }
    return contador_ventas;
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
    //PUNTO 2
    CantidadVentasPorMedioPago(lista_ciudades);

    //Punto 3
    string producto_buscar;
    string medio_pago_buscar;
    cout<<"Ingrese el producto que desee buscar: "<<endl;
    cin>>producto_buscar;
    cout<<"Ingrese el medio de pago: "<<endl;
    cin>>medio_pago_buscar;
    int contador_ventas=0;
    contador_ventas=BuscarPorProducto_MedioPago(lista_ciudades,producto_buscar,medio_pago_buscar);
    cout<<"Cantidad de ventas de ese porducto con ese medio: "<<contador_ventas<<endl;
    return 0;
}

