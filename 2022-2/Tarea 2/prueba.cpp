#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;
struct Persona{
    string nombre;
    bool capitan;
    int poder;
};

struct Nodo {
    Persona info;
    Nodo * sig;
};

class Equipo {
private:
    Nodo * head;
    Nodo * tail;
    Nodo * curr;
    unsigned int listSize;
    unsigned int pos;
    int pospos;

public:
    //Va al siguiente nodo de la lista
    void next(){ 
        if (curr != tail){
            curr = curr -> sig;
            pos++;
        }
    }
    //deja curr en la posicion anterior a la que estaba
    void prev(){
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
    void moveToStart(){curr = head; pos = 0;} //volver al inicio
    int currPos(){return pos;} //devuelve pos actual, se usa en ciclos como punto de partida de ciclos despues de un moveToStart()
    unsigned int getSize(){return listSize;} //Tamaño de la lista enlazada, va de la mano con getPos() en los ciclos
    unsigned int getPoder(){return curr->sig->info.poder;} //poder de un personaje
    string getNombre(){return curr->sig->info.nombre;} //nombre del personaje
    bool getCapitan(){return curr->sig->info.capitan;}
    //funciones anteriores 
public:
    int agregar_companero(string nombre, int poder); 
    void set_capitan(string nombre); //Recorrer la lista y al primer match definir como capitan
    int calcular_poder(); //recorrer la lista y retornar un contador con la suma 
    void imprimir_equipo(); //recorrer la lista y devolver ciertos parametros 
    string return_capitan();
    
    Equipo(){
        head = tail = curr = new Nodo;
        listSize = 0; pos = 0;
    }
    ~Equipo(){}
};

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

int Equipo::calcular_poder(){
    unsigned int contPoder = 0;
    moveToStart();
    while (pos < getSize()){
        contPoder += getPoder();
        next();
    }
    return contPoder;
}

void Equipo::imprimir_equipo(){
    moveToStart();
    cout << "Equipo: " << currPos() << endl;
    cout << endl;
    while(pos < getSize()){
        cout << "Persona " << currPos() << ": " << getNombre() << " " << getCapitan() << " " << getPoder() << endl;
        next();
    }
}

string Equipo::return_capitan(){
    moveToStart();
    while (pos < getSize()){
        if (getCapitan()== 1){
            return getNombre();
        }
        next();
    }
    return NULL;
}

Equipo * ArregloDeListas(int * contador) {
    int k = 0;
    string nom, auxint, auxcap;
    int poder;
    //cout << " hola" << endl;
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

    while (k < cont){
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
            cout << "funciono esta caga" << endl;
        }
    }
    file.close();
    *contador = cont;
    return arreglo;
}

struct tNodo{       // -> representa 1 equipo
    string capitan = "BYE";
    int poder = 0;

};

class Torneo {
private:
    tNodo clash[256][256];  //En la matriz de equipos este representa Y
    //tNodo clashX[256]; //En la matriz de equipos este representa X 
    
    int tamano; //Cant equipos efectivos que hay
    int posX, posY; //posiciones respectivas para la matriz 
    int NivelArbol; //se ocupa para calcular peleas
    int cantNivelArbol; //cuantos equipos tienen que existir por arbol lleno, esto incluye a los BYE
    



public:
    void moveToStart(){ posX = 0;}
    Torneo(){
        tamano = 0; //Cantidad real de equipos en la cosa esta 
        posX = posY = 0;
        NivelArbol = 0;
        cantNivelArbol = 0;
        cant_crear_torneo = cant_avanzar_ronda = 0;
        cant_batallar = 0;
        endofgame = 1;
        //NivelArbol = NivelArbolActual =  cant_imprimir_bracket = 0;
        //cant_avanzar_ronda = 1;
    }
    ~Torneo(){}
private:
    int cant_crear_torneo;
    int cant_avanzar_ronda;
    int cant_batallar;
    
public:
    bool endofgame;
    void crear_torneo(Equipo * equipos, int n); //Listo, en las primeras posiciones estan los equipos simplificados.
    void definirNiveles(int n);
    void imprimir_bracket();
    void avanzar_ronda();
    bool batallar(Equipo & a, Equipo &b);
    void batallar();

};



void Torneo::crear_torneo(Equipo * equipos, int n){
    if (cant_crear_torneo == 0){
        definirNiveles(n);
        for (int pos = posX; pos < n; pos++){
            clash[pos][posY].capitan = equipos[pos].return_capitan();
            clash[pos][posY].poder = equipos[pos].calcular_poder();
        }

        tamano = n;
        cant_crear_torneo ++;
    }else{
        cout << "El torneo ya fue creado 1 vez. Favor de relanzar el codigo si quiere otro torneo" << endl;
    }    
}


void Torneo::imprimir_bracket(){
    moveToStart();
    if(posY == NivelArbol){
        cout << "El campeon del torneo es: " << clash[0][posY].capitan << endl;
        endofgame = 0;
        //codear la final 
    }else{
        for (int pos = 0; pos < cantNivelArbol; pos ++){ //previamente i < pos
            cout << clash[pos][posY].capitan << " " << clash[pos][posY].poder << " vs ";
            pos++;
            cout << clash[pos][posY].capitan << " " << clash[pos][posY].poder << " | ";
            //pos++;
        }
    }

    //esto caga cuando se imprime mas de 1 ronda 
    cout << endl;
    //cout << "dentro del arreglo pos es :" <<posX << endl;
}

bool Torneo::batallar(Equipo & a, Equipo &b){
    if (a.calcular_poder() <= b.calcular_poder()){
        return true;
    }else{
        return false;
    }
}
void Torneo::batallar(){
    for(int pos = 0; pos < cantNivelArbol; pos ++){
        if(clash[pos][posY].poder >= clash[pos+1][posY].poder){
            clash[cant_batallar][posY+1].poder = clash[pos][posY].poder;
            clash[cant_batallar][posY+1].capitan = clash[pos][posY].capitan;
            pos ++;
            cant_batallar++;
        }else{
            clash[cant_batallar][posY+1].poder = clash[pos+1][posY].poder;
            clash[cant_batallar][posY+1].capitan = clash[pos+1][posY].capitan;
            pos++;
            cant_batallar++;
        }
    }
}
void Torneo::avanzar_ronda(){
    batallar();
    posY ++;
    cantNivelArbol = (cantNivelArbol/2);
    cant_batallar = 0;
    if (cant_avanzar_ronda == NivelArbol){
        
        cout << "El campeon del torneo es: " << clash[0][posY].capitan << endl;
        endofgame = 0;

    }
    cant_avanzar_ronda ++;
    
}

void Torneo::definirNiveles(int n){
    if (n < 2){
        NivelArbol = 0;
    }
    int i = 1;

    while (true){
        if (n <= pow(2,i)){
            NivelArbol = i;
            break;
        }
        i++;
    }
    cantNivelArbol = pow(2,NivelArbol);
}


int main(){
    int muajaja;
    Equipo * arr = ArregloDeListas(&muajaja);
    int t;
    /*
    for (int i = 0; i < muajaja; i++){
        arr[i].imprimir_equipo();
        cout << "Y el capitan del equipo es: " << arr[i].return_capitan() << endl;
    }
    */
    Torneo torneito;
    torneito.crear_torneo(arr,muajaja);

    while (torneito.endofgame == 1){
        cout << "Hola ingresa numeros entre el 1 ,2 ,3 para avanzar en el torneo" << endl; cout << endl;
        cin >> t;
        cout << endl;

        switch(t){
            case 1:
                cout << "Elegiste avanzar de ronda" << endl;
                cout << endl;
                torneito.avanzar_ronda();
                break;
            case 2:
                cout << "Elegiste imprimir el estado de bracket" << endl; cout << endl;
                torneito.imprimir_bracket();
                break;
            case 3: 
                cout << "WIP, estate atento a nuevas actualizaciones" << endl;
                break;
        }
    }
    return 0;
}
