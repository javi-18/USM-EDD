#include "Equipo.hpp"

using namespace std;

void Equipo::next(){ 
    if (curr != tail){
        curr = curr -> sig;
        pos++;
    }
}
//deja curr en la posicion anterior a la que estaba
void Equipo::prev(){
    Nodo * ant;
    if (curr == head){
        return;
    }
    ant = head;
    while(ant->sig != curr){
        ant = ant->sig;
    }
    curr = ant;
    pos--;
}
void Equipo::moveToStart(){curr = head; pos = 0;} //volver al inicio
int Equipo::currPos(){return pos;} //devuelve pos actual, se usa en ciclos como punto de partida de ciclos despues de un moveToStart()
unsigned int Equipo::getSize(){return listSize;} //Tamaño de la lista enlazada, va de la mano con getPos() en los ciclos
unsigned int Equipo::getPoder(){return curr->sig->info.poder;} //poder de un personaje
string Equipo::getNombre(){return curr->sig->info.nombre;} //nombre del personaje
bool Equipo::getCapitan(){return curr->sig->info.capitan;}

Equipo::Equipo(){
    head = tail = curr = new Nodo;
    listSize = 0; pos = 0;
}


/*****
* int Equipo::agregar_companero()
******
* Funcion que agrega un compañero a algun equipo
******
* Input:
*  string nombre: Un string que es nombre de la persona
*   int poder : un entero que representa el poder que tiene la persona
******
* Returns:
* Retorna la posicion donde se inserto el compañero
*****/
int Equipo::agregar_companero(string nombre, int poder){ 
    Nodo * aux = curr -> sig;
    curr -> sig = new Nodo;
    curr -> sig -> info.nombre = nombre;
    curr -> sig -> info.poder = poder;
    curr -> sig -> sig = aux;
    if (curr == tail){
        tail = curr -> sig;
    }
    listSize++;
    pos++;
    return pos;
}


/*****
* void Equipo::set_capitan(string nombre)
******
* Funcion que recorre la lista y al primer match define un capitan
******
* Input:
*  string nombre: Un string que es nombre de la persona
*   
******
* Returns:
* Como es de tipo void, no retorna nada, simplemente define el capitan del equipo
*****/
void Equipo::set_capitan(string nombre){ 
    moveToStart();
    while (pos < getSize()){
        if(nombre == getNombre()){
            curr -> sig -> info.capitan = 1;
            break;
        }
        next();
    }
}


/*****
* int Equipo::calcular_poder()
******
* Funcion que recorre la lista y va sumando los poderes de los integrantes del equipo
******
* Input:
*  La funcion no recibe un parametro, simplemente recorre la lista para obtener los poderes de cada integrante del equipo y sumarlos
 para obtener el poder total del equipo
* 
******
* Returns:
* Como es de tipo void, no retorna nada, simplemente define calcula el poder del equipo
*****/
int Equipo::calcular_poder(){ 
    unsigned int contPoder = 0;
    moveToStart();
    while (pos < getSize()){
        contPoder += getPoder();
        next();
    }
    return contPoder;
}

/*****
* void Equipo::imprimir_equipo()
******
* Funcion que imprime por pantalla un equipo entero
******
* Input:
*  La funcion no recibe parametros, simplemente muestra un equipo por pantalla
*   
******
* Returns:
* Como es de tipo void, no retorna nada
*****/
void Equipo::imprimir_equipo(){ 
    moveToStart();
    cout << "Equipo: " << currPos() << endl;
    cout << endl;
    while(pos < getSize()){
        cout << "Persona " << currPos() << ": " << getNombre() << " " << getCapitan() << " " << getPoder() << endl;
        next();
    }
}
/*****
* string Equipo::return_capitan()
******
* Funcion que te retorna el integrante que es capitan de un equipo
******
* Input:
*  La funcion no recibe parametros, simplemente muestra el capitan de un equipo
*   
******
* Returns:
* Como es de tipo void, no retorna nada
*****/
string Equipo::return_capitan(){ 
    moveToStart();
    while (pos < getSize()){
        if (getCapitan()== 1){
            return getNombre();
        }
        next();
    }
    return NULL;
};


/*****
* Equipo * ArregloDeListas(int * contador)
******
* Funcion la cual nos ayuda a abrir el archivo y sacar la informacion necesaria para trabajar con el
******
* Input:
*  int * contador : puntero de tipo int que apunta hacia una variable contador que se obtiene del archvio 
    "Equipos.txt", el cual representa el tamaño del arreglo de equipos
*   
******
* Returns:
* Retorna un arreglo que contiene a los equipos 
*****/
Equipo * ArregloDeListas(int * contador){ 
    int k = 0;
    string nom, auxint, auxcap;
    int poder;

    ifstream file("Equipos.txt", ios::in);
    if (!file.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return NULL;
    }

    string cl;
    int cantLineas = 0;
    while(getline(file,cl)){
        cantLineas++;
    }
    file.clear();
    file.seekg(0,ios::beg);

    getline(file, cl);
    int cont = stoi(cl); //cont se refiere a la cantidad de equipos

    Equipo * arreglo = new Equipo[cont];

    while (true){
        file >>cl;
        int contPorEquipo = stoi(cl);

        for (int i = 0; i<contPorEquipo; i++){
            file >> nom;
            file >> auxint;
            poder = stoi(auxint);
            arreglo[k].agregar_companero(nom,poder);
        }

        file >> auxcap; 
        arreglo[k].set_capitan(auxcap);

        k++;
        if (file.eof()){
            break;
        }
    }
    file.close();
    *contador = cont;
    return arreglo;
}
