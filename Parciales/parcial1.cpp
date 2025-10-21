#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
using namespace std;

struct RegistroEnergia
{
    string Pais;
    string Empresa;
    string Tipo;
    float Energia;
    float Costo;
};
const int longitud_pais=9;
const int longitud_empresa=8;
const int longitud_tipo=11;

struct nodo
{
    RegistroEnergia informacion;
    nodo* siguiente;
};

fstream& operator>> (fstream &fs, RegistroEnergia &registros)
{
    registros.Pais=readstring(fs, longitud_pais);
    registros.Empresa=readstring(fs, longitud_empresa);
    registros.Tipo=readstring(fs,longitud_tipo);
    fs.read(reinterpret_cast<char*>(&registros.Energia), sizeof(registros.Energia));
    fs.read(reinterpret_cast<char*>(&registros.Costo),sizeof(registros.Costo));
    return fs;
}

void InsertarOrdenado (nodo* &lista, RegistroEnergia &registro_nuevo)
{
    nodo* nuevo_nodo= new nodo;
    nuevo_nodo->informacion= registro_nuevo; //b
    nuevo_nodo->siguiente=nullptr; //b

    if(lista==nullptr || criterio_Pais_Empresa(registro_nuevo, lista->informacion) <0) //si es menor a 0, entonces el nuevo nodo va antes
    {
        nuevo_nodo->siguiente=lista;
        lista=nuevo_nodo;
        return;
    }
    nodo* actual=lista;
    while (actual->siguiente!=nullptr && criterio_Pais_Empresa(registro_nuevo, actual->siguiente->informacion)>=0)
    {
        actual=actual->siguiente;
    }
    nuevo_nodo->siguiente=actual->siguiente;
    actual->siguiente=nuevo_nodo;
    
}

void Informe(nodo* lista)
{
    nodo* nodo_Actual=lista;
    nodo* lista_auxiliar=nullptr;
    int dias=0;
    int total_energia=0;
    while(nodo_Actual!=nullptr)
    {
        string pais_Actual=nodo_Actual->informacion.Pais;
        string empresa_Actual=nodo_Actual->informacion.Empresa;

        nodo* temporal=nodo_Actual;
        dias=0;
        total_energia=0;

        while (temporal!=nullptr && temporal->informacion.Pais==pais_Actual && temporal->informacion.Empresa==empresa_Actual)
        {   
            dias++;
            total_energia+=temporal->informacion.Energia;
            temporal=temporal->siguiente;
        }

        float promedio= total_energia/dias;
        cout<< "Pais: " << pais_Actual <<" |Empresa: "<<empresa_Actual<<"| Dias: "<<dias<<"|Total Energía: "<<total_energia<<"|Promedio: "<<promedio;
        if (promedio>20.1)
        {
            while (lista_auxiliar != temporal) // recorremos solo los nodos del grupo
            {
                cout << "Tipo: " << lista_auxiliar->informacion.Tipo
                     << " | Costo: " << lista_auxiliar->informacion.Costo << endl;
                lista_auxiliar = lista_auxiliar->siguiente;
            }
        }
        nodo_Actual = temporal;
    }
}


void Buscar(nodo* lista, string paisBuscado, string empresaBuscada)
{
    nodo* actual = lista;
    while (actual != nullptr && 
        (actual->informacion.Pais != paisBuscado || actual->informacion.Empresa != empresaBuscada)) 
    {
        actual = actual->siguiente;
    }
    if(actual==nullptr)
    {
        cout<<"No existe dicha combinacion.";
        return;
    }
    float totalEnergia = 0;
    int dias = 0;
    nodo* temp = actual;

    while (temp != nullptr && 
        temp->informacion.Pais == paisBuscado && 
        temp->informacion.Empresa == empresaBuscada)
    {
        totalEnergia += temp->informacion.Energia;
        dias++;
        temp = temp->siguiente;
    }

    float promedioActual = totalEnergia / dias;if (temp == nullptr) {
    cout << "No hay combinacion siguiente." << endl;
    } else {
    string paisSiguiente = temp->informacion.Pais;
    string empresaSiguiente = temp->informacion.Empresa;

    float totalEnergiaSiguiente = 0;
    int diasSiguiente = 0;

    nodo* tempSiguiente = temp;
    while (tempSiguiente != nullptr &&
           tempSiguiente->informacion.Pais == paisSiguiente &&
           tempSiguiente->informacion.Empresa == empresaSiguiente)
    {
        totalEnergiaSiguiente += tempSiguiente->informacion.Energia;
        diasSiguiente++;
        tempSiguiente = tempSiguiente->siguiente;
    }

    float promedioSiguiente = totalEnergiaSiguiente / diasSiguiente;

    if (promedioActual > promedioSiguiente) {
        cout << "El promedio de la combinacion buscada es MAYOR al siguiente." << endl;
    } else {
        cout << "El promedio de la combinacion buscada NO es mayor al siguiente." << endl;
    }
}
}
//CRITERIOS
int criterio_Pais_Empresa(const RegistroEnergia &registro_a, const RegistroEnergia &registro_b )
{
    if(registro_a.Pais<registro_b.Pais) return -1; //registro a va antes que el b
    if(registro_a.Pais>registro_b.Pais) return 1;
    if(registro_a.Empresa<registro_b.Empresa) return -1;
    if(registro_a.Empresa>registro_b.Empresa) return 1;
    return 0; //iguales pais y empresa
}

int main()
{
    nodo* lista= nullptr;
    RegistroEnergia registro;
    fstream archivo("energia.dat", ios::binary | ios::in);
    while (archivo >> registro) {
        InsertarOrdenado(lista, registro);
    }
    Informe(lista);
    string paisBuscado, empresaBuscada;
    cout << "Ingrese Pais: ";
    getline(cin, paisBuscado);
    cout << "Ingrese Empresa: ";
    getline(cin, empresaBuscada);

}