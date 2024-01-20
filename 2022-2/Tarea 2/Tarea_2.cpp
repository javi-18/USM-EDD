#include <iostream>
#include <string>
#include <fstream>
#include "torneo.hpp"

using namespace std;


int main(){
    int muajaja;
    Equipo * arr = ArregloDeListas(&muajaja);
    int t;
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

