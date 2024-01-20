#include "torneo.hpp"
using namespace std;


struct tNodo tnodo;

bool endofgame;
void Torneo::moveToStart(){ posX = 0;}

/*****
* void Torneo::crear_torneo()
******
* Crea el torneo a partir de la cantidad de equipos que reciba la función, que los coloca en el ultimo nivel del arbol binario que representa el torneo
******
* Input:
*  Equipo * equipos: Un puntero hacia la clase equipo que contiene todos los equipos creados a partir del archiv¿o "equipos.txt"
*   int n : un entero n que representa la cantidad de equipos que participaran en el torneo 
******
* Returns:
* Como es de tipo void no retorna nada
*****/
void Torneo::crear_torneo(Equipo * equipos, int n){
    if (cant_crear_torneo == 0){
        definirNiveles(n);
        for (int pos = posX; pos < n; pos++){
            clash[pos][posY].capitan = equipos[pos].return_capitan();
            clash[pos][posY].poder = equipos[pos].calcular_poder();
        }

        tamano = n;
        cant_crear_torneo ++;
    }
    else{
        cout << "El torneo ya fue creado 1 vez. Favor de relanzar el codigo si quiere otro torneo" << endl;
    }    
}


/*****
* void Torneo::imprimir_bracket()
******
* Funcion que muestra el estado actual del torneo,es decir, muestra por consola la ronda actual y los equipos que se enfrentan
******
* Input:
* La funcion no recibe un parametro, simplemente imprime el estado actual del torneo 
*
******
* Returns:
* Como es de tipo void no retorna nada
*****/
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


/*****
* boolTorneo::batallar(Equipo & a, Equipo &b)
******
* Funcion que recibe 2 equipos y compara el poder total de cada equipo, para decidir quien avanza a la siguiente ronda
******
* Input:
* Equipo & a: Un primer equipo que se obtiene de la lista de equipos
* Equipo &b: Un segundo equipo que se obtiene de la lista de equipos
******
* Returns:
* Retorna true si es que el equipo a tiene un poder mayor,y en caso contrario retorna false, el cual indica que 
el equipo b era el equipo de mayor poder 
*****/
bool Torneo::batallar(Equipo & a, Equipo &b){
    if (a.calcular_poder() <= b.calcular_poder()){
        return true;
    }else{
        return false;
    }
}

/*****
* void Torneo::batallar()
******
* Funcion que compara el poder de un equipo con el equipo siguiente, para despues decidir quien pasa a la siguiente ronda
******
* Input:
* La funcion no recibe ningun parametro, solamente compara los poderes de cada equipo 
*
******
* Returns:
* Como es de tipo void no retorna nada 
*****/
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


/*****
* void Torneo::avanzar_ronda()
******
* Funcion que hace avanzar al equipo ganador a la siguiente ronda del torneo
******
* Input:
* La funcion no recibe ningun parametro, simplemente permite avanzar a la siguiente ronda al equipo ganador
* 
******
* Returns:
* Como es de tipo void, no retorna nada
*****/
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


/*****
* void Torneo::definirNiveles(int n)
******
* Funcion que crea los niveles del arbol binario,es decir, las rondas del torneo 
******
* Input:
* int n : un entero n que define la cantidad de niveles del arbol que representa el torneo
* 
******
* Returns:
* Como es de tipo void, no retorna nada
*****/
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