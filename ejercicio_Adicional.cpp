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

struct Pedido
{
    int id;
    string zona;
    string producto;
    int cantidad;
};
const int long_zona=10;
const int long_producto=15;

struct Representante
{
    int id;
    string zona;
    int cantidad_pedidos_realizados=0;
    int cantidades_pedidas=0;
    Nodo<Pedido>* lista_pedidos=nullptr;
};

struct Zona
{
    string zona;
    Nodo<Pedido>* lista_zonas=nullptr;
};

fstream& operator>> (fstream& fs, Pedido &pedido)
{
    fs.read(reinterpret_cast<char*>(&pedido.id), sizeof(pedido.id));
    pedido.zona=readstring(fs,long_zona);
    pedido.producto=readstring(fs,long_producto);
    fs.read(reinterpret_cast<char*>(&pedido.cantidad), sizeof(pedido.cantidad));
    return fs;
}

void MostrarRepresentante(Nodo<Representante>* listado_representantes)
{
    Nodo<Representante>* rep_actual=listado_representantes;
    while (rep_actual !=nullptr)
    {
        cout << "Representante ID: " << rep_actual->dato.id 
             << " | Zona: " << rep_actual->dato.zona 
             << " | Pedidos: " << rep_actual->dato.cantidad_pedidos_realizados 
             << " | Total Cantidades: " << rep_actual->dato.cantidades_pedidas 
             << endl;
        Nodo<Pedido>* pedido_Actual=rep_actual->dato.lista_pedidos;
        while (pedido_Actual!=nullptr)
        {
            cout<<pedido_Actual->dato.producto<< " "<<pedido_Actual->dato.cantidad;
            pedido_Actual=pedido_Actual->sig;
        }
        rep_actual=rep_actual->sig;
    }
    
}


bool ExisteCombinacion(Nodo<Representante>* listado_representantes, int id_buscado, string zona_buscada)
{
    Nodo<Representante>* representante_Actual=listado_representantes;
    bool existe_combinacion=false;
    while (representante_Actual!=nullptr)
    {
        if (representante_Actual->dato.id==id_buscado && representante_Actual->dato.zona==zona_buscada)
        {
            existe_combinacion=true;
        }
        representante_Actual=representante_Actual->sig;
        
    }
    return existe_combinacion;
    
}

void MostrarProductoPorRepresentante_Zona(Nodo<Representante>* listado_representante, string producto_buscado, string zona_buscada, int id_buscado)
{
    Nodo<Representante>* representante_Actual=listado_representante;
   
    while (representante_Actual!=nullptr)
    {
        Nodo<Pedido>* pedido_Actual= representante_Actual->dato.lista_pedidos;
        while (pedido_Actual!= nullptr)
        {
            if(representante_Actual->dato.id==id_buscado && representante_Actual->dato.zona== zona_buscada && pedido_Actual->dato.producto==producto_buscado)
            {
                cout<<"Pedido: "<<pedido_Actual->dato.producto<<" Cantidad: "<<pedido_Actual->dato.cantidad<<endl;
            }
            pedido_Actual=pedido_Actual->sig;
        }
        representante_Actual=representante_Actual->sig;
    }
    
}
int main()
{
    Nodo<Representante>* listado_representantes=nullptr;
    Nodo<Zona>* listado_zonas=nullptr;
    Pedido pedido;
    fstream archivo("pedidos.bin", ios::binary | ios::in);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo datos02.dat\n";
        return 1;
    }
   

    while (archivo >> pedido)
    {
        Nodo<Representante>*Rep_actual=listado_representantes;
        Representante rep;
        rep.id=pedido.id;
        rep.zona=pedido.zona;
        rep.cantidad_pedidos_realizados=0;
        rep.cantidades_pedidas=0;
        rep.lista_pedidos=nullptr;
        bool existe=false;
        
        while (Rep_actual!=nullptr)
        {
           if (Rep_actual->dato.id==rep.id && Rep_actual->dato.zona== rep.zona)
           {
                existe=true;
                break;
           }
           Rep_actual=Rep_actual->sig;
           
        }
        //Si no existe el representante
        if(!existe)
        { 
            agregar(listado_representantes,rep);
        }
        else //si existe el representante
        {
            Nodo<Pedido>* pedido_nuevo=new Nodo<Pedido>;
            pedido_nuevo->dato=pedido;
            pedido_nuevo->sig=nullptr;

            if(Rep_actual->dato.lista_pedidos==nullptr) //si la lista de pedidos esta vacía
            {
                Rep_actual->dato.lista_pedidos=pedido_nuevo;
            }
            else //si no está vacía mando el nuevo pedido al final porque no me importa el orden.
            {
                Nodo<Pedido>* pedido_agregar= Rep_actual->dato.lista_pedidos;
                while (pedido_agregar->sig!=nullptr)
                {
                    pedido_agregar=pedido_agregar->sig;
                }
                pedido_agregar->sig=pedido_nuevo;
                Rep_actual->dato.cantidad_pedidos_realizados++;
                Rep_actual->dato.cantidades_pedidas += pedido.cantidad;
                
            }

        }
        
        Nodo<Zona>* zona_Actual=listado_zonas;
        bool existe_zona=false;
        Zona zona;
        zona.zona=pedido.zona;
        zona.lista_zonas=nullptr;
        while (zona_Actual!=nullptr)
        {
            if (zona_Actual->dato.zona==zona.zona)
            {
               existe_zona=true;
               break;
            }
            zona_Actual=zona_Actual->sig;
            
        }
        if(!existe_zona)
        {
            agregar(listado_zonas,zona);
        }
    }
    MostrarRepresentante(listado_representantes);
    int id_buscado=0;
    string zona_buscada;
    string producto_buscado;
    bool existe_combinacion=false;
    do
    {
        cout<<"Ingrese el id del represenante que desea buscar: "<<endl;
        cin>>id_buscado;
        cout<<"Ingrese la zona que desea buscar: "<<endl;
        cin>>zona_buscada;
        existe_combinacion=ExisteCombinacion(listado_representantes, id_buscado, zona_buscada);
        if (existe_combinacion)
        {
            cout<<"Ingrese el producto que desee buscar: "<<endl;
            cin>>producto_buscado;
            MostrarProductoPorRepresentante_Zona(listado_representantes,producto_buscado,zona_buscada,id_buscado);
        }
        else cout<<"No existe la combinación solicitada"<<endl; 
        
        
    } while (id_buscado!=-1 && zona_buscada!="");
    

    return 0;
}