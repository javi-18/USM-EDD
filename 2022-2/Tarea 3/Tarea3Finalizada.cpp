#include <iostream>
#include <string>
#include <fstream>

#define CARTAS 1667
#define SOBRES 1667

#define VACIA -1
#define OCUPADA -2

using namespace std;

struct Carta{
  int id;
  string nombre;
  int ataque;
  int defensa;
  int precio;
  int estado = VACIA; //indica que todas las posiciones de carta comienzan vacias
  int cantidad = 0; //En resumidas cuentas, cada carta (que tiene un ID unico, por ende su cantidad esta definida aqui) representa 1 casilla en nuestra
};

struct Sobre{
  int id;
  Carta cartas[10];
  int estado = VACIA; //indica que todas las posiciones de sobre comienzan vacias 
};

class HashTable {
private:
  int inicio;
  int pos;
  int dinero;
public:
  //De puro latero van aqui
  Carta HTC[CARTAS];
  Sobre HTS[SOBRES];
  int contHTS;
  int contHTC;
  //Funciones necesarias para la tarea
  int hashGet(string str); //Funcion h
  int hashPos(); // Funcion p
  int hashInsert(int ID,string nombre, int ataque, int defensa, int precio); //Insertar en tabla
  int hashInsertSobre(int ID, int id, string nombre, int ataque, int defensa, int precio, int posicion);//, string nombre, int ataque, int defensa, int precio);

  //FUNCIONES RELACIONADAS A LAS CARTAS 
  void mostrar_cartas(); //      leer la tabla 
  int tengo_la_carta(int id); // Cantidad de esa carta, segun el ID
  void vender_carta(int id); //  Vender carta segun ID

  //FUNCIONES RELACIONADAS A LOS SOBRES
  void mostrar_sobres();
  void vender_sobre(int id);
  
  // Comenzar el programa
  void iniciarHashTable(); 

  //funciones tontas que son para que se lea mas bonito
  void volverInicio(){pos = 0;}
  int mostrar_dinero(){return dinero;}
  HashTable(){
    inicio = 0;
    pos = 0;
    dinero = 0;
    contHTC = 0;
  }
  ~HashTable(){}
};

/*****
* int hashGet
******
* Esta funcion recibe un string (que siempre seran numeros) y lo recorre sumando sus respectivos valores ascii (que se obtienen mediante un casting a int)
* Ademas para evitar colisiones, el primer valor se multiplica por el N° primo 7 y el ultimo por el N° primo 11
* La suma de todos los valores ascii luego modifica el valor pos, que se encuentra en la clase HashTable
* Viene siendo la funcion h() en los ppts 
******
* Input:
* string str: Toma un string para luego recorrerlo como una cadena, en este caso viene siendo el ID de la carta o sobre que previamente se transformo en string
* .......
******
* Returns:
* int i: Despues de sumar todos los valores, retorna la suma dividida segun MODULO en el total de las cartas (Cuyo valor es igual al de los sobres) 
* Para ser usada como posicion a la hora de insertar en la tabla (Se utiliza pos pero es el mismo valor que i)
*****/
int HashTable::hashGet(string str){
  int i = 0;
  int total = str.length();
  for (int j = 0; j < total; j++){
    if (j == 0){
      i += 7*int(str[j]);
    }
    if (j != 0 && j!=total-1){
      i+= int (str[j]);
    }
    if ( j == total-1){
      i += 11 * int(str[j]);
    }

  }
  i = i % CARTAS;
  pos = i;

  return i; //representa la posicion en la cual se va a insertar
}

/*****
* int hasPos
******
* Esta viene siendo la funcion p() de los ppts, esta funcion es llamada cuando existe una colision a la hora de insertar un dato en la tabla de hashing
* Modifica el valor pos en la clase, mediante una multiplicacion de si mismo por 3 y luego la division MODULO de pos entre el tamaño de cartas o sobres
* Tambien contiene en caso especial donde si la posicion es 0, entonces se suma 1 para seguir modificando pos
******
* Input:
* no contiene ningun parametro, ya que el valor que modifica constantemente es un valor privado que existe en la misma clase de la funcion
* .......
******
* Returns:
* int pos, Retorna una nueva posicion en la cual insertar, esta funcion tiende a llamarse varias veces segun la cantidad de colisiones en la tabla 
*****/
int HashTable::hashPos(){
  if (pos == 0){
    pos ++;
    pos = ((pos*3)%CARTAS);
    return pos;
  }else{
    pos = ((pos*3)%CARTAS);
    return pos;
  }
  
}

/*****
* int tengo_la_carta
******
* Esta funcion toma como parametro un valor int, lo transforma a un string y luego aplica la funcion de hasheo a ese mismo para obtener la posicion o la exisitencia
* del numero int pasado como referencia, en caso de no ser encontrado, se pasa a la funcion hashPos() y se sigue buscando la id pedida, la busqueda el valor id
* dentro de la tabla de hashing es el mismo con el que se insertan valores, por lo tanto deberia siempre encontrar el id pedido o simplemente ese id no existe
* luego despues de todo eso, retorna la cantidad de veces que existe la carta, ese valor fue agregado al struct cartas para hacer esta funcion mas sencilla
******
* Input:
* int id: Es el id de una carta dentro del programa, como toda la funcion hashea respecto al valor del id, es necesario
* .......
******
* Returns:
* int cant: Es un valor auxiliar que contiene la cantidad de veces que aparece una carta, valor que se encuentra en el arreglo de cartas mismo
*****/
int HashTable::tengo_la_carta(int id){
  bool flag = true;
  int contador = 0;
  string str = to_string(id);
  int cant;
  
  pos = hashGet(str);
  while (flag){
    if (HTC[pos].id == id && HTC[pos].estado == OCUPADA){
      //cout << "Para el ID " << id << " Quedan: " << HTC[pos].cantidad << " Cartas" << endl;
      cant = HTC[pos].cantidad;
      volverInicio();
      flag = false;
    }else{
      hashPos();
      contador++;
      if (contador > 20){
        cout << "No se logro encontrar la carta con la ID pedida" << endl;
        flag = false;
        volverInicio();
      }
    }
  }
  cout << endl;
  return cant;
}

/*****
* int hashInsertSobre
******
* La funcion toma los parametros dados y hashea en la tabla de Sobres el primer parametro, luego ingresa los valores de los atributos individuales de las cartas
* dentro de la misma tabla, en caso de fallar la insercion reintentara con una nueva posicion 500 veces antes de simplemente no insertar en la tabla
******
* Input:
* int ID : Valor con el cual se hashea la posicion
* int id:  id respectivo de cada carta dentro del sobre
* string nombre: nombre respectivo de cada carta dentro del sobre
* int ataque: ataque respectivo de cada carta dentro del sobre
* int defensa: defensa respectiva de cada carta dentro del sobre
* int precio: precio respectivo de cada carta dentro del sobre
* int posicion: como hay 10 cartas dentro de un sobre, este valor se refiere a el lugar donde se inserta cada carta dentro del sobre
* .......
******
* Returns:
* int posi: simplemente retorna la ultima posicion donde se inserto el sobre, el valor pos despues de la funcion retorna a 0 pero antes de eso lo guarda en posi
*****/
int HashTable::hashInsertSobre(int ID,int id,string nombre, int ataque, int defensa, int precio, int posicion){ //FALTA EL ID DE LA CARTA EN PARTICULAR
  bool flag = true;
  volverInicio();
  int contador;
  string aux;
  int posi;
  aux = to_string(ID);
  pos = hashGet(aux);
  while (flag){
    if (HTS[pos].estado == VACIA){
      HTS[pos].id = ID;
      HTS[pos].cartas[posicion].id = id;
      HTS[pos].cartas[posicion].nombre = nombre;
      HTS[pos].cartas[posicion].ataque = ataque;
      HTS[pos].cartas[posicion].defensa = defensa;
      HTS[pos].cartas[posicion].precio = precio;
      posi = pos;
      contHTS++;

      if (contHTS == 10){
        HTS[pos].estado = OCUPADA;
        contHTS= 0;
      }
      
      
      volverInicio();
      flag = false;
    }
    if (HTS[pos].estado == OCUPADA){
      hashPos();
      contador++;
      if (contador > 500){
        cout << "No se logro insertar el ID" << endl;
        flag = false;
      }
    }
  }
  volverInicio();
  return posi;
}

/*****
* int hashInsert
******
* Exactamente lo mismo que la funcion anterior, solo que ahora hashea respecto a la tabla de cartas y ocupa mas valores en los parametros porque son 
* necesarios para otras funciones y en este caso tiene que si existen 2 ids con los mismo valores de nombre, ataque, defensa, precio.
* Entonces aumenta la cantidad de esa carta en 1 
******
* Input:
* int ID : valor con el cual se hashea la posicion
* string nombre: nombre respectivo de cada carta
* int ataque : ataque respectivo de cada carta
* int defensa: defensa respectiva de cada carta
* int precio: precio respectivo de cada carta
*
* .......
******
* Returns:
* int posi: retorna la ultima posicion antes de insertar el valor y volver al inicio
*****/
int HashTable::hashInsert(int ID, string nombre, int ataque, int defensa, int precio){ //Aun falta el caso donde hay choques 
  bool flag = true;
  int contador = 0;
  int posi;
  string str = to_string(ID);
  pos = hashGet(str);
  while (flag){
    if (HTC[pos].estado == VACIA){
      HTC[pos].id = ID;
      HTC[pos].nombre = nombre;
      HTC[pos].ataque = ataque;
      HTC[pos].defensa = defensa;
      HTC[pos].precio = precio;
      HTC[pos].estado = OCUPADA;
      HTC[pos].cantidad++;
      posi = pos;
      volverInicio();
      flag = false;
    }
    if (HTC[pos].estado == OCUPADA && HTC[pos].nombre == nombre && HTC[pos].ataque == ataque && HTC[pos].defensa == defensa && HTC[pos].precio == precio){
      HTC[pos].cantidad ++;
      posi = pos;
      volverInicio();
      flag = false;
    }
    if (HTC[pos].estado == OCUPADA){
      hashPos();
      contador++;
      if (contador > 500){
        cout << "No se logro insertar el ID" << endl;
        flag = false;
        volverInicio();
      }
    }
  }
  return posi;
}

/*****
* void mostrar_cartas
******
* Recorre con un ciclo for toda la tabla de hashing de cartas y muestra por pantalla los datos de las casillas que estan ocupadas
******
* Input:
* no recibe parametros porque los valores modificados estan dentro de la clase misma
******
* Returns:
* no tiene retornos porque es una funcion void, solo modifica valores internos de la clase
*****/
void HashTable::mostrar_cartas(){
  cout << "Cartas en stock: " << endl;
  for (int i = 0; i < CARTAS; i++){
    if (HTC[i].estado == OCUPADA){
      cout << HTC[i].id << " " << HTC[i].nombre << " " << HTC[i].ataque << " ";
      cout << HTC[i].defensa << " " << HTC[i].precio << " " << HTC[i].cantidad << endl;
    }
  }
}

/*****
* void mostrar_sobres
******
* exactamente lo mismo que mostrar_cartas pero recorre la tabla de sobres y solo muestra por pantalla el id del los sobres en casilla ocupadas
******
* Input:
* no recibe parametros porque los valores modificados estan dentro de la clase misma
* .......
******
* Returns:
* no tiene retornos porque es una funcion void, solo modifica valores internos de la clase
*****/
void HashTable::mostrar_sobres(){
  cout << "Sobres en stock: " << endl;
  for (int i = 0; i < SOBRES; i++){
    if (HTS[i].estado == OCUPADA){
      cout << HTS[i].id << endl;
    }
  }
}

/*****
* void vender_carta
******
* Misma idea que tengo_la_carta o hashGet, toma un valor int id que luego hashea para obtener la posicion dentro de la tabla de hashing de cartas y luego comparar si 
* efectivamente existe la carta solicitada, en caso de existir se le quita en 1 la cantidad de cartas y se le suma el valor de la variable precio
* a una variable privada de la clase llamada dinero. 
* En caso de haber vendida la ultima carta de ese id, entonces "elimina" el valor de la tabla de hashing 
* Entiendase eliminar como cambiar el estado de la casilla de ocupado a vacia, por lo que a la hora de usar la siguiente funcion mostrar_cartas no aparezca
* COMO EL PROGRAMA NUNCA VA A AGREGAR NUEVAS CARTAS AL STOCK ENTONCES NO ES NECESARIO IGUALA LOS VALORES A 0 PARA MOSTRAR QUE ESTA VACIO
******
* Input:
* int id: misma idea que las funciones anteriores, hashea el id para devolver una posicion y luego buscar si existe la carta a vender
* .......
******
* Returns:
* FUNCION VOID, NO RETORNA NADA, SIMPLEMENTE MODIFICA VALORES INTERNOS DE LA CLASE
*****/
void HashTable::vender_carta(int id){
  bool flag = true;
  int contador = 0;
  string str = to_string(id);
  
  pos = hashGet(str);
  while (flag){
    if (HTC[pos].id == id && HTC[pos].estado == OCUPADA){
      HTC[pos].cantidad--;
      dinero += HTC[pos].precio;
      cout << "Vendida la Carta!" << endl;
      if (HTC[pos].cantidad == 0){
        HTC[pos].estado = VACIA;
      }
      volverInicio();
      flag = false;
    }else{
      hashPos();
      contador++;
      if (contador > 500){
        cout << "Ese ID no se encuentra!" << endl;
        volverInicio();
        flag = false;
      }
    }
  }
  cout << endl;
}

/*****
* void vender_sobre
******
* Recibe un id y luego busca en la tabla de sobres ese id mediante hashGet y hashPos, de encontrarlo aumenta el dinero en 1000 y elimina el sobre
* NO SABEMOS SI HAY QUE EFECTIVAMENTE ELIMINAR EL SOBRE PERO COMO TIENEN IDS UNICAS LO HAREMOS
******
* Input:
* int id: numero que utilizaremos para encontrar el sobre y venderlo
* .......
******
* Returns:
* no tiene retornos porque es una funcion void, solo modifica valores internos de la clase
*****/
void HashTable::vender_sobre(int id){
  volverInicio();
  bool flag = true;
  int contador = 0;
  string str = to_string (id);

  pos = hashGet(str);
  while (flag){
    if (HTS[pos].id == id && HTS[pos].estado == OCUPADA){
      for (int i = 0; i < 10; i++){
        cout << HTS[pos].cartas[i].id << " " << HTS[pos].cartas[i].nombre<< " " << HTS[pos].cartas[i].ataque << " " << HTS[pos].cartas[i].defensa << " ";
        cout << HTS[pos].cartas[i].precio << endl;
      }
      dinero += 1000;
      cout << "Vendido el Sobre!" << endl;
      HTS[pos].estado = VACIA;
      volverInicio();
      flag = false;
    }else{
      hashPos();
      contador++;
      if (contador > 20){
        cout << "Ese ID no se encuentra!" << endl;
        volverInicio();
        flag= false;
      }
    }
  } 
}

/*****
* void iniciarHashTable
******
* Funcion que efectivamente inicia todo el programa, aqui se lee el archivo Tienda.txt y luego se rellena toda la tabla de hashing de cartas y sobres mediante
* las funciones hashInsert y hashInsertSobre, con los parametros de estas siendo los valores leido del archivo txt
******
* Input:
* no tiene parametros la funcion, todos los valores existen en la clase misma
* .......
******
* Returns:
* no tiene retornos porque es una funcion void, solo modifica valores internos de la clase
*****/
void HashTable::iniciarHashTable(){
  
  int id, atk, def, precio;
  string nombre;
  int aux; //Aux toma el valor de la cantidad de sobres que van a haber
  int ID;
  ifstream file("Tienda.txt",ios::in);
  if (!file.is_open()){
    cout << "Error al abrir el archivo" << endl;
    return;
  }
  string cl;
  getline(file,cl);
  int cantCartas = stoi(cl);
  for (int j = 0; j < cantCartas; j++){
    file >> id >> nombre >> atk >> def >> precio;
    hashInsert(id, nombre , atk, def, precio);
  }
  
  file >> aux;
  for(int i = 0; i < aux; i++){
    file >> ID;
    for(int j = 0; j < 10; j++){
      file >> id >> nombre >> atk >> def >> precio;
      hashInsertSobre(ID,id,nombre,atk,def,precio,j);
    }

  }
  file.close();
}

int main(){
  HashTable Tienda;
  Tienda.iniciarHashTable();
  bool Tarea = true;
  int o; //que funcione la tarea
  int seleccion; //valor multiuso para vender cartas o sobres
  cout << "Bienvenido a la tienda de Cartas!" << endl;
  
  while (Tarea){
    cout << endl;
    cout << "Para continuar escoja numeros entre el 1 o el 6" << endl;

    cin >> o;
    cout << endl;
    switch (o)
    {
    case 1:
      cout << "El dinero total es: " << Tienda.mostrar_dinero() << endl;
      break;
    case 2:
      Tienda.mostrar_cartas();
      break;
    case 3:
      Tienda.mostrar_sobres();
      break;
    case 4:
      cout << "Ingrese el ID de la carta a vender: " << endl;
      cin >> seleccion;
      Tienda.vender_carta(seleccion);
      break;
    case 5:
      cout << "Ingrese el ID del sobre a vender" << endl;
      cin >> seleccion;
      Tienda.vender_sobre(seleccion);
      break;
    case 6:
      cout << "Gracias por visitarnos :D" << endl;
      Tarea = false;
      break;
    default:
      cout << "Valor dado no esta dentro de la opciones, por favor ingresar denuevo" << endl;
      break;
    }
  }

  return 0;
}