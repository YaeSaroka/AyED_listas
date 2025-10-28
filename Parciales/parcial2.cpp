#include <iostream>
#include "listas.hpp"
#include <string>
#include <fstream>
#include "rwstring.hpp"
#include <list>
using namespace std;

//ESTRUCTURAS
template <typename T>
struct Nodo
{
    T dato;
    Nodo<T>* sig;
};

struct Registro
{
    string Pais;
    string Empresa;
    string TipoPlanta;
    float EnergiaProducida;
    float Costo; 
};
const int longPais=9;
const int longEmpresa=8;
const int longTipo=11;


struct Empresa
{
    string Empresa;
    Nodo<Registro>* lista_registros=nullptr;
};

struct Pais
{
    string Pais;
   Nodo<Empresa>* lista_empresas=nullptr;
};

fstream& operator>>(fstream& fs, Registro& registro)
{
    registro.Pais=readstring(fs, longPais);
    registro.Empresa=readstring(fs,longEmpresa);
    registro.TipoPlanta=readstring(fs,longTipo);
    fs.read(reinterpret_cast<char*>(&registro.EnergiaProducida), sizeof(registro.EnergiaProducida));
    fs.read(reinterpret_cast<char*>(&registro.Costo), sizeof(registro.Costo));
    return fs;
}

int CriterioAscendentePais(Pais a, Pais b)
{
    if (a.Pais>b.Pais) return 1; // a va dsp de b
    if(a.Pais<b.Pais) return -1;
    else return 0;
}
int CriterioAscendenteEmpresa(Empresa a, Empresa b)
{
    if (a.Empresa>b.Empresa) return 1; // a va dsp de b
    if(a.Empresa<b.Empresa) return -1;
    else return 0;
}
int CriterioDescendente (Registro a, Registro b)
{
    if(a.TipoPlanta<b.TipoPlanta) return 1; //a va antes q b
    if(a.TipoPlanta>b.TipoPlanta) return -1;
    else return 0;
}
template <typename T>
Nodo<T>* InsertarOrdenado(Nodo<T>* &lista, T valor, int (*criterio)(T, T))
{
    Nodo<T>* actual = lista;
    Nodo<T>* anterior = nullptr;

    while (actual != nullptr && criterio(actual->dato, valor) < 0)
    {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual != nullptr && criterio(actual->dato, valor) == 0)
    {
        return actual; 
    }
    else
    {
        Nodo<T>* nuevo = new Nodo<T>;
        nuevo->dato = valor;
        nuevo->sig = actual;

        if (anterior == nullptr)
            lista = nuevo;
        else
            anterior->sig = nuevo;

        return nuevo;
    }
}

void CalcularTotales(Nodo<Registro>* lista_registros, float &CantidadEnergiaProducida, int &CantidadDias, float &promedio)
{
    Nodo<Registro>* registro_Actual=lista_registros;
    CantidadEnergiaProducida=0;
    CantidadDias=0;
    promedio=0;
    while (registro_Actual!=nullptr)
    {
        CantidadEnergiaProducida+=registro_Actual->dato.EnergiaProducida;
        CantidadDias ++;
        registro_Actual=registro_Actual->sig;
    }
    if (CantidadDias>0)
    {
        promedio=CantidadEnergiaProducida/CantidadDias;
    }
}

int main()
{
    Nodo<Pais>* listado_paises=nullptr;
    Registro registro;
    fstream Archivo("datos_pacial.bin", ios::binary| ios::in);
    if(!Archivo.is_open())
    {
        cout<<"ERROR AL ABRIR EL ARCHIVO"<<endl;
        return -1;
    }
    while (Archivo >> registro)
    {
        Pais pais;
        pais.Pais=registro.Pais;
        pais.lista_empresas=nullptr;
        Nodo<Pais>* nodo_Pais=InsertarOrdenado(listado_paises,pais, CriterioAscendentePais);

        Empresa empresa;
        empresa.Empresa=registro.Empresa;
        empresa.lista_registros=nullptr;
        Nodo<Empresa>* nodo_Empresa=InsertarOrdenado(nodo_Pais->dato.lista_empresas,empresa, CriterioAscendenteEmpresa);
        Nodo<Registro>* nodo_reg=InsertarOrdenado(nodo_Empresa->dato.lista_registros, registro,CriterioDescendente);
    }

    Nodo<Pais>* lista_paises=listado_paises;
    while (lista_paises!=nullptr)
    {
        Nodo<Empresa>* lista_empresas=lista_paises->dato.lista_empresas;
        while (lista_empresas!=nullptr)
        {
            Nodo<Registro>* listado_registros=lista_empresas->dato.lista_registros;
            
                float promedio=0; 
                float CantidadEnergiaProducida=0;
                int CantidadDias=0;
                CalcularTotales(listado_registros, CantidadEnergiaProducida, CantidadDias,promedio);
                
                cout<< "Pais: "<<lista_paises->dato.Pais<<endl;
                cout<< "Empresa: " <<lista_empresas->dato.Empresa<<endl;
                cout<< "Total Energia: "<<CantidadEnergiaProducida<<endl;
                cout<<"Cantidad de Días: "<<CantidadDias<<endl;
                cout<<"Promedio: "<<promedio<<endl;
            
                if(promedio > 20.1)
                {
                    cout << "----- DIAS CON PROMEDIO MAS DE 20.1 -------" <<endl;
                    Nodo<Registro>* aux = listado_registros;
                    while (aux != nullptr)
                    {
                        cout << "Tipo: " << aux->dato.TipoPlanta
                            << " | Costo: " << aux->dato.Costo << endl;
                        aux = aux->sig;
                    }
                        
                }
                lista_empresas=lista_empresas->sig;
        }
        lista_paises=lista_paises->sig;
        
    }
    











    
    
    
   
    
    
    





}

