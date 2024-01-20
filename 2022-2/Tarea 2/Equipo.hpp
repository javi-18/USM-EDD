
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Persona{ //Declaramos un struct persona el cual contiene los datos de cada integrante del equipo y un booleano que dice si es capitan o no
    string nombre;
    bool capitan;
    int poder;
};

struct Nodo { //Declaramos un struct Nodo el cual contiene la informacion de cada integrante del equipo
    Persona info;
    Nodo * sig;
};

class Equipo {  //Declaramos la clase equipo la cual nos ayudara a trabajar con todas las funciones necesarias para crear un equipo
private:
    Nodo * head;
    Nodo * tail;
    Nodo * curr;
    unsigned int listSize;
    unsigned int pos;

public:
    //Va al siguiente nodo de la lista
    void next();
    //deja curr en la posicion anterior a la que estaba
    void prev();
    void moveToStart(); //volver al inicio
    int currPos(); //devuelve pos actual, se usa en ciclos como punto de partida de ciclos despues de un moveToStart()
    unsigned int getSize(); //Tamaño de la lista enlazada, va de la mano con getPos() en los ciclos
    unsigned int getPoder(); //poder de un personaje
    string getNombre(); //nombre del personaje
    bool getCapitan();
    //funciones anteriores 
public:
    int agregar_companero(string, int); //Agrega un compañero al equipo
    void set_capitan(string); //Recorrer la lista y al primer match definir como capitan
    int calcular_poder(); //recorrer la lista y retornar un contador con la suma 
    void imprimir_equipo(); //recorrer la lista y devolver ciertos parametros 
    string return_capitan();//Retorna el capitan de un equipo
    
    Equipo();
    ~Equipo(){}
};



Equipo * ArregloDeListas(int * contador);