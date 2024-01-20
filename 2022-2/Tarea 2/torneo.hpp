
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include "Equipo.hpp"

using namespace std;

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
    void moveToStart();
    ~Torneo(){}
private:
    int cant_crear_torneo;
    int cant_avanzar_ronda;
    int cant_batallar;
    
public:
    bool endofgame;
    void crear_torneo(Equipo*equipos,int n); //Listo, en las primeras posiciones estan los equipos simplificados.
    void definirNiveles(int n);
    void imprimir_bracket();
    void avanzar_ronda();
    bool batallar(Equipo & a, Equipo &b);
    void batallar();

};