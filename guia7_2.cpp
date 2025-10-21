#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
using namespace std;

struct Registros //lo que se lee directamente del archivo
{
    string ciudad;
    string modelo;
    int cantidad;
};
const int long_ciudad=12;
const int long_modelo=10;

struct Venta //cada venta particular de una ciudad
{
    string modelo;
    int cantidad;
};
struct Ciudad // agrupa las ventas que se hicieron en esa ciudad
{
    string ciudad;
    int totventas=0;
    int totcant=0;
    Nodo<Venta>* lista_ventas=nullptr;
};

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* sig = nullptr;
};


//CRITERIOS
int CriterioOrdenadoPorCiudad(string a, string b)
{
    if(a>b) return 1; //a va despues de b
    if(a<b) return -1; //a va antes de b
    return 0; //a es igual a b
}

fstream& operator>> (fstream &fs, Registros &ventas)
{
    ventas.ciudad=readstring(fs, long_ciudad);
    ventas.modelo=readstring(fs, long_modelo);
    fs.read(reinterpret_cast<char*>(&ventas.cantidad),sizeof(ventas.cantidad));
    return fs;
}

Nodo<Ciudad>* InsertarOrdenadoAscendente(Nodo<Ciudad>* &lista_ciudades, Ciudad c)
{
    Nodo<Ciudad>* anterior=nullptr;
    Nodo<Ciudad>* actual=lista_ciudades;

    while(actual!=nullptr && CriterioOrdenadoPorCiudad(actual->dato.ciudad, c.ciudad)<0)
    {
        anterior=actual;
        actual=actual->sig;
    }
    if (actual!=nullptr && CriterioOrdenadoPorCiudad(actual->dato.ciudad, c.ciudad)==0) return actual;    
    else
    {
        Nodo<Ciudad>* nuevo = new Nodo<Ciudad>;
		nuevo->dato = c;
		//si el anterior sigue siendo nulo, quiere decir que va al cominenzo de la lista
		if (anterior == nullptr)
			lista_ciudades = nuevo;
		else
			anterior->sig = nuevo;
		//en cualquier caso:
		nuevo->sig = actual;
		return nuevo;
	}
    }
    
    void BuscarPorCiudad(string nombre_ciudad, Nodo<Ciudad>* lista_ciudades)
    {
        Nodo<Ciudad>* nodo_Actual = lista_ciudades;
        while (nodo_Actual!=nullptr)
        {
            if (nodo_Actual->dato.ciudad==nombre_ciudad)
            {
                cout << "Ciudad: "<< nodo_Actual->dato.ciudad<<endl;
                Nodo<Venta>* lista_ventas_por_ciudad= nodo_Actual->dato.lista_ventas;
                while (lista_ventas_por_ciudad!=nullptr)
                {
                    cout << "VENTAS:"<<endl;
                    cout<< "Modelo: "<<lista_ventas_por_ciudad->dato.modelo;
                    cout<<"Cantidad: "<<lista_ventas_por_ciudad->dato.cantidad;
                    lista_ventas_por_ciudad=lista_ventas_por_ciudad->sig;
                }
                if (lista_ventas_por_ciudad==nullptr)
                {
                    cout <<"No hay ventas registradas en esta ciudad"<<endl;
                    return;
                }    
            
            }
            nodo_Actual=nodo_Actual->sig;

        }
        cout<<"NO EXISTE LA CIUDAD"<<endl;
        
    }

    void BuscarPorCantidadMinima(Nodo<Ciudad>* lista_ciudades, int cantidad_minima, string nombre_ciudad)
    {
        Nodo<Ciudad>* nodo_Actual= lista_ciudades;
        int contador_ventas=0;

        while (nodo_Actual!=nullptr)
        {
           if (nodo_Actual->dato.ciudad == nombre_ciudad)
           {
                Nodo<Venta>* venta=nodo_Actual->dato.lista_ventas;
                while (venta!=nullptr)
                {
                    if (venta->dato.cantidad>=cantidad_minima)
                    {
                        contador_ventas++;
                    }
                    venta=venta->sig;
                }
               if (contador_ventas==0)
               {
                    cout<<"No hay ventas que superen la cantidad minima"<<endl;
               }
           }
           
           nodo_Actual=nodo_Actual->sig;
           
        }
        
    }


int main()
{
    Nodo<Ciudad>* lista_ciudades = nullptr;
    Registros registro;
    fstream archivo("datos02.dat", ios::binary | ios::in);

    while (archivo >> registro) {
        Ciudad ciu;
        ciu.ciudad = registro.ciudad;
        ciu.totcant = 0;
        ciu.totventas = 0;
        ciu.lista_ventas = nullptr;

        // Insertar u obtener ciudad
        Nodo<Ciudad>* nodo_ciudad = InsertarOrdenadoAscendente(lista_ciudades, ciu);

        // Crear la venta
        Venta venta;
        venta.cantidad = registro.cantidad;
        venta.modelo = registro.modelo;

        // Insertar venta en la ciudad correspondiente
        agregar(nodo_ciudad->dato.lista_ventas, venta);

    }

    Nodo<Ciudad>* aux = lista_ciudades;
    while (aux != nullptr) {
        cout << aux->dato.ciudad << " - Ventas: " << aux->dato.totventas 
             << " - Cantidad: " << aux->dato.totcant << endl;
        aux = aux->sig;
    }

    string ciudad_abuscar;
    cout <<"Ingrese la ciudad que desea buscar: ";
    cin>> ciudad_abuscar;
    BuscarPorCiudad(ciudad_abuscar,lista_ciudades);

    string ciudad_abuscar2;
    int cantidad_a_buscar;
    cout <<"Ingrese la ciudad que desea buscar: ";
    cin>> ciudad_abuscar2;
    cout <<"Ingrese la cantidad que desea buscar: ";
    cin>> cantidad_a_buscar;
    return 0;
}
