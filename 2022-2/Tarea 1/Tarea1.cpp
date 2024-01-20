#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;


//Declaramos la estructura "Registro" la cual guarda los datos ingresados por el usuario su posterior uso 
struct Registro { 
	int dia;
  int mes;
  int anio;
  char rol[12];
  int ppm;
  float precision;
};


//Declaramos la estructura "Datos" la cual guarda los datos del estudiante que se encuentran en "Estudiantes.txt"
struct Datos {
	string rol;
	string nombre;
  string apellido;
  int paralelo;
};

/*
* Struct Datos TamanoDatos
**
* Resumen Función: La funcion abre el archivo txt de estudiantes y lee todas las entradas presentes en este, luego procesa la cantidad de personas y genera un arreglo del tipo struct donde se almacena la informacion de las personas 
**
* Input:
* No contiene ningun input como tal, solo pasa por referencia el valor de contador para retornar no solo el arreglo, si no tambien su tamaño 
* .......
**
* Returns:
* Arreglo del tipo struct, Contiene los datos de todos las personas en el archivo txt
*/
Datos* TamanoDatos(int *contador){
  ifstream file("estudiantes.txt", ios::in);
  if (!file.is_open()){
    cout << "Error al abrir el archivo" << endl;
    return NULL;
  }
  string cl;
  int cont = 0,i = 0;
  
  while(getline(file,cl)){
    cont++;
  }
  file.clear();
  file.seekg(0,ios::beg);
  
  
  Datos * da = new Datos[cont];
  
  while (file >> da[i].rol >> da[i].nombre >> da[i].apellido >> da[i].paralelo){
    i++;
  }
  
  file.close();
  *contador = cont;
  return da;
}

/*
* Struct Registro TamanoDatosBin
**
* Al igual que la vez anterior, la funcion abre y lee todas las entradas del archivo binario para luego pasarlas a un arreglo de tipo struct
**
* Input:
* Ningun tipo de input, solo pasa por referencia el tamaño del arreglo para un uso futuro. (quiza sea innecesario pero se hace por buena conducta)
* .......
**
* Returns:
* arreglo struct registro, Arreglo de la informacion del archivo binario.
*/
Registro* TamanoDatosBin(int * contador){
  ifstream bin("registro.dat", ios::binary);
  if (!bin.is_open()){
    cout << "Error al abrir el archivo" << endl;
    return NULL;
  }

  int cont2;
  bin.read((char*)&cont2, sizeof(int));
  int cont = cont2;

  Registro * ba = new Registro[cont2];
  
  bin.read((char*)ba, sizeof(Registro)* cont);

  *contador = cont;
  return ba;
}


int main(){
  int cantAlumnos, cantAlumnosBin; // No se si lo vayamos a ocupar pero es bueno tener ese dato disponible 
  Datos * da = TamanoDatos(&cantAlumnos);
  Registro * ba = TamanoDatosBin(&cantAlumnosBin);
  int Q; //Cantidad de consultas a leer por entrada estándar.
  int t;//Si se quiere PPM o Precision 
  int d;//Se guarda el valor que corresponde al dia, si es 0 o mayor a 31, el intento se perdera
  int m;//Se guarda el valor que corresponde al mes, si es 0 o mayor a 12, el intento se perdera
  int a;//Se guarda el valor que corresponde al año, si es menor a 1 o mayor a 3000, el intento se perdera
  int j;
  float ganador = 0.00; //Valor para guardar una posicion
  int ganadorPPM = 0;
  int posicion = 0;



  cout << "Inserte la cantidad de entradas a pedir" << endl; cin >> Q;
  if(Q>cantAlumnos){
    cout << "La cantidad de entradas a pedir no puede ser mas grande que la cantidad de alumnos en el curso!" << endl;
    return 1;
  }


  
  for(int i = 0; i < Q; i++){
    cout << "Inserte t" << endl; cin >> t;
    if(t < 0 || t > 1){
      cout << "t no se encuentra en valores validos!" << endl;
      return 1;
    }
    cout << "Inserte el dia" << endl;cin >> d;
    if(d < -1 || d > 31 || d == 0){
      cout << "Dia no se encuentra en los valores validos!" << endl;
      return 1;
    }
    cout << "Inserte m" << endl;cin >> m;
    if(m < -1 || m == 0 || m > 12){
      cout << "Mes no se encuentra en los valores validos!" << endl;
      return 1;
    }
    
    cout << "Inserte Año" << endl;cin >> a;
    if(a < 1 || a >3000){
      cout << "Año no se encuentra entre los valores validos!" << endl;
      return 1;
    }
    
    if(t == 0){
      cout << "Usted selecciono: Precision" << endl;
      cout << " " << endl;
      //Escribir casos especiales dma esta hecho
      if(d != -1 && m!= -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            if(ba[j].mes == m){
              if(ba[j].dia == d){
                //aqui escribir condiciones
                if(ba[j].precision > ganador){
                  posicion = j;
                  ganador = ba[j].precision;
                }
                else if(ba[j].precision == ganador){
                  cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
                  posicion = j;
                }
              }
            }
          }
        }
      }
      else if(d == -1 && m != -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            if(ba[j].mes == m){
              //aqui escribir condiciones
              if(ba[j].precision > ganador){
                posicion = j;
                ganador = ba[j].precision;
              }
              else if(ba[j].precision == ganador){
                cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
                posicion = j;
              }
            }
          }
        }
      }
      else if(d == -1 && m == -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            //aqui escribir condiciones
            if(ba[j].precision > ganador){
              posicion = j;
              ganador = ba[j].precision;
            }
            else if(ba[j].precision == ganador){
              cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
              posicion = j;
            }
          }
        }
      }


      if (ganador == 0.0){
        cout << "No hubo un ganador / los datos ingresados no corresponden a ninguna fecha" << endl;
      }else{
        cout << da[posicion].nombre << " " << da[posicion].apellido <<endl;
      }
      
      //a este punto ya ocurrieron los 3 casos posibles
      j = 0;
      posicion = 0;
      ganador = 0.0;
    }

    //---------------------------------------------------------------------------------------------------------------
    else if (t == 1){
      cout << "Usted ha seleccionado PPM" << endl;
      cout << " " << endl;
      if(d != -1 && m!= -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            if(ba[j].mes == m){
              if(ba[j].dia == d){
                //aqui escribir condiciones
                if(ba[j].ppm > ganadorPPM){
                  posicion = j;
                  ganadorPPM = ba[j].ppm;
                }
                else if(ba[j].ppm == ganadorPPM){
                  cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
                  posicion = j;
                }
              }
            }
          }
        }
      }
      else if(d == -1 && m != -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            if(ba[j].mes == m){
              //aqui escribir condiciones
              if(ba[j].ppm > ganadorPPM){
                posicion = j;
                ganadorPPM = ba[j].ppm;
              }
              else if(ba[j].ppm == ganadorPPM){
                cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
                posicion = j;
              }
            }
          }
        }
      }
      else if(d == -1 && m == -1){
        for(j = 0; j < cantAlumnos; j++){
          if(ba[j].anio == a){
            //aqui escribir condiciones
            if(ba[j].ppm > ganadorPPM){
              posicion = j;
              ganadorPPM = ba[j].ppm;
            }
            else if(ba[j].ppm == ganadorPPM){
              cout << "Hubo un empate de valores, se utilizara el segundo dato ingresado." << endl;
              posicion = j;
            }
          }
        }
      }


      if (ganadorPPM == 0){
        cout << "No hubo un ganador / los datos ingresados no corresponden a ninguna fecha" << endl;
      }else{
        cout << da[posicion].nombre << " " << da[posicion].apellido <<endl;
      }
      
      //a este punto ya ocurrieron los 3 casos posibles
      j = 0;
      posicion = 0;
      ganadorPPM = 0;
    }
  }





  delete[] ba;
  delete[] da;
  return 0;
}