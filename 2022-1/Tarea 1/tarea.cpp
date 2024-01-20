#include<iostream>      // Libreria para entrada y salida de datos
#include<fstream>       // Libreria para lectura y escritura de archivos
#include<string>        // Libreria para manejar strings

#define MAX_ALLOW 65536 // Máximo tamaño posible para un arreglo
using namespace std;    // usar namespace para evitar usar el std::

// Estructura de tickets
struct Ticket {
    char rut_funcionario[10];
    int day_of_month;
    char time[6];
};

// Estructura de servicios, para agrupar las estructuras
struct Servicio {
    string nombre, hora_inicio, hora_final;
    int limite_diario, limite_mensual;
};


/*****
* bool comparar_tickets
******
* Esta función compara dos Structs de Ticket
* La principal gracia de esta función, es que permite
* ordenar con un sistema jerarquico, siguiendo las siguientes condiciones
*  - Si ya está ordenado por Rut, se ordena por dia del mes
*  - Si ya está ordenado por dia del mes, ser ordena por la hora del dia
******
* Input:
* Ticket A : Cualquier Ticket A
* Ticket A : Cualquier Ticket B
* .......
******
* Returns:
* bool, Si es mayor que otro dependiendo la condiciones mencionadas anteriormente
*****/
bool comparar_tickets(Ticket A, Ticket B) {

    // Se pasa el rut a string, respectivamente
    string rut_a, rut_b;
    for (int i = 0; i < 10; i++) {
        rut_a += A.rut_funcionario[i];
        rut_b += B.rut_funcionario[i];
    }

    // Se pasa el horario a cantidad de segundos
    int time_a = (( (A.time[0]-'0') * 10) + A.time[1]-'0') * 60 + ( (A.time[3]-'0') * 10) + A.time[4]-'0';
    int time_b = (( (B.time[0]-'0') * 10) + B.time[1]-'0') * 60 + ( (B.time[3]-'0') * 10) + B.time[4]-'0';

    // Si ya es igual, sigue otra condicion
    if (rut_a == rut_b) {

        // Si ya es igual, sigue la otra condición
        if (A.day_of_month == B.day_of_month) {
            
            // Se compara por el horario
            if (time_a <= time_b)
                return true;
            return false;

        } else {

            // Se compara por el dia del mes
            if (A.day_of_month < B.day_of_month)
                return true;
            return false;
        }

    } else {
        // Se compara léxicograficamente
        if (rut_a < rut_b)
            return true;
        return false;
    }

    return false;
}


/*****
* bool comparar_servicios
******
* Esta función compara dos Structs de Servicio
* Ordena dependiendo los horarios
******
* Input:
* Servicio A : Un servicio A cualquiera
* Servicio B : Un servicio B cualquiera
* .......
******
* Returns:
* bool, Si es mayor que otro dependiendo la condiciones mencionadas anteriormente
*****/
bool comparar_servicios(Servicio A, Servicio B) {
    
    // Se transforma la hora a segundos
    int hi_a = (( (A.hora_inicio[0]-'0') * 10) + A.hora_inicio[1]-'0') * 60 + ( (A.hora_inicio[3]-'0') * 10) + A.hora_inicio[4]-'0';
    int hf_a = (( (A.hora_final[0]-'0') * 10) + A.hora_final[1]-'0') * 60 + ( (A.hora_final[3]-'0') * 10) + A.hora_final[4]-'0';

    // Se transforma la hora a segundos
    int hi_b = (( (B.hora_inicio[0]-'0') * 10) + B.hora_inicio[1]-'0') * 60 + ( (B.hora_inicio[3]-'0') * 10) + B.hora_inicio[4]-'0';
    int hf_b = (( (B.hora_final[0]-'0') * 10) + B.hora_final[1]-'0') * 60 + ( (B.hora_final[3]-'0') * 10) + B.hora_final[4]-'0';

    // Las condiciones a comparar
    if(hf_a < hi_b){
        return true;
    }

    if(hi_a > hf_b){
        return false;
    }

    return false;
}


/*****
* bool merge_servicio
******
* Esta funcion mezcla dos servicios ordenados
******
* Input:
* Servicios servicios[] : Arreglo de servicio
* int low  : La cota inferior
* int mid  : La mediana
* int high : La cota superior
* .......
******
* Returns:
* void
*****/
void merge_servicio(Servicio servicios[], int low, int mid, int high, int m) {
    int i;
    int left_index = low;
    int right_index = mid + 1;
    int combined_index = low;
    Servicio tempA[MAX_ALLOW];

    while(left_index <= mid && right_index <= high)
        if (comparar_servicios(servicios[left_index], servicios[right_index]))
            tempA[combined_index++] = servicios[left_index++];
        else
            tempA[combined_index++] = servicios[right_index++];

    if(left_index == mid + 1) 
        while(right_index <= high) 
            tempA[combined_index++] = servicios[right_index++];
    else
        while(left_index <= high)
            tempA[combined_index++] = servicios[left_index++];

    for(i = low; i <= high; i++)
        servicios[i] = tempA[i];
}

/*****
* bool merge_sort_servicios
******
* Esta funcion ordena recursivamente el arreglo
******
* Input:
* Servicios servicios[] : Arreglo de servicio
* int low  : La cota inferior
* int mid  : La mediana
* int high : La cota superior
* int m    : El largo del arreglo
* .......
******
* Returns:
* void
*****/
void merge_sort_servicios(Servicio servicios[], int low, int high, int m) {
    int mid = 0;

    if(low == high)
        return;
    else {
        mid = (low + high) / 2;

        // Primero ordena al final del arreglo
        merge_sort_servicios(servicios, low, mid, m);
        merge_sort_servicios(servicios, mid + 1, high, m);

        // Luego junta los ordenados
        merge_servicio(servicios, low, mid, high, m);
    }
}

/*****
* bool merge_tickets
******
* Esta funcion mezcla dos Tickets ordenados
******
* Input:
* Ticket tickets[] : Arreglo de servicio
* int low  : La cota inferior
* int mid  : La mediana
* int high : La cota superior
* .......
******
* Returns:
* void
*****/
void merge_tickets(Ticket tickets[], int low, int mid, int high, int m) {
    int i;
    int left_index = low;
    int right_index = mid + 1;
    int combined_index = low;
    Ticket tempA[MAX_ALLOW];

    while(left_index <= mid && right_index <= high)
        if (comparar_tickets(tickets[left_index], tickets[right_index]))
            tempA[combined_index++] = tickets[left_index++];
        else
            tempA[combined_index++] = tickets[right_index++];

    if(left_index == mid + 1) 
        while(right_index <= high) 
            tempA[combined_index++] = tickets[right_index++];
    else
        while(left_index <= high)
            tempA[combined_index++] = tickets[left_index++];

    for(i = low; i <= high; i++)
        tickets[i] = tempA[i];
}
/*****
* bool merge_sort_tickets
******
* Esta funcion ordena recursivamente el arreglo
******
* Input:
* Ticket tickets[] : Arreglo de servicio
* int low  : La cota inferior
* int mid  : La mediana
* int high : La cota superior
* int m    : El largo del arreglo
* .......
******
* Returns:
* void
*****/
void merge_sort_tickets(Ticket tickets[], int low, int high, int m) {
    int mid = 0;

    if(low == high)
        return;
    else {
        mid = (low + high) / 2;

        // Primero ordena al final del arreglo
        merge_sort_tickets(tickets, low, mid, m);
        merge_sort_tickets(tickets, mid + 1, high, m);

        // Luego junta los ordenados
        merge_tickets(tickets, low, mid, high, m);
    }
}

/*****
* bool rutEsIgual
******
* Esta función compara si dos ruts son iguales
******
* Input:
* string rut_A : Un rut en string
* string rut_B : Un rut en string
* .......
******
* Returns:
* bool, Si es igual, es verdadero, si no, falso
*****/
bool rutEsIgual(string rut_A, string rut_B) {

    // Revisamos los 10 digitos del rut
    for (int i = 0; i < 10; i++)
        if (rut_A[i] != rut_B[i])
            return false;
    return true;
}

/*****
* string charArrayToString
******
* Esta funcion transforma un arreglo de chars a un string
******
* Input:
* char arr[] : Un arreglo de caracteres
* int n : El largo de char array
* .......
******
* Returns:
* string, Un string, correspondiente a los caracteres del arreglo de chars
*****/
string charArrayToString(char arr[], int n) {

    // Una función que acumula todos los caracteres
    string ret = "";
    for (int i = 0; i < n; i++)
        ret += arr[i];
    
    return ret;
}

/*
retorna 0 -> si esta dentro del horario
retorna -1 -> si esta a la izquierda
retorna 1 -> si esta a la derecha
*/

/*****
* int horaContiene
******
* Esta funcion dice en que posición se encuentra
* la hora a comparar
******
* Input:
* string hora_inicio : La hora de inicio en string  Ej: 00:00
* string hora_final  : La hora final en string      Ej: 00:00
* string hora        : La hora que se quiere comparar
* .......
******
* Returns:
* Un numero entero
* 0     => Si la hora está completamente contenida en el horario
* -1    => Si la hora está a la izquierda del horario
* 1     => Si la hora está a la derecha del horario
*****/
int horaContiene(string hora_inicio, string hora_final, string hora) {

    // Transformamos la horas a segundos, respectivamentes para cada horario
    // Se le resta el '0' para que nos dé el valor numero desde el ASCII
    // Se le multiplica por 10 porque son las decenas y se le suma las unidades
    int hora_inicio_int =  ( ((hora_inicio[0]-'0') * 10) + hora_inicio[1]-'0' ) * 60;
    hora_inicio_int += ( (hora_inicio[3]-'0') * 10 ) + (hora_inicio[4] - '0');

    int hora_final_int = ( ((hora_final[0]-'0') * 10) + hora_final[1]-'0' ) * 60;
    hora_final_int += ( (hora_final[3]-'0') * 10 ) + (hora_final[4] - '0');

    int hora_int = ( ((hora[0]-'0') * 10) + hora[1]-'0' ) * 60;
    hora_int += ( (hora[3]-'0') * 10 ) + (hora[4] - '0');

    // Este seria el caso normal, cuando el Inicio < Final
    if(hora_final_int > hora_inicio_int) {

        // Está completamente contenida por el horario
        if (hora_int >= hora_inicio_int && hora_int <= hora_final_int)  return 0;

        // Está a la izquierda del horario
        else if(hora_int < hora_inicio_int) return -1;

        // Está a la derecha del horario
        return 1;
    } 

    // Esto soluciona el caso borde cuando un dia tiene horario del dia siguiente
    if ((hora_int >= hora_inicio_int && hora_int <= (24 * 60) ) || (0 <= hora_int && hora_int <= hora_final_int))  return 0;
    else if(hora_int < hora_inicio_int) return -1;
    return 1;
    
}

int main() {

    // Archivo servicios
    fstream archivo_servicios;
    archivo_servicios.open("servicios.txt") ;

    // En el caso de que no se pueda abrir, el programa no seguirá
    if (!archivo_servicios.is_open()) {
        cerr << "[Error] No se ha podido abrir el archivo servicios.txt" << endl ;
        return 1;
    }


    // n seria la cantidad total de servicios
    int n;
    archivo_servicios >> n;

    // Creamos un arreglo de servicio
    Servicio servicios[n];

    // Iteramos n veces, para los n servicios
    for (int i = 0; i < n; i++) {

        // Creamos las variables correspondientes para
        // pedir los datos
        int limite_diario, limite_mensual;
        string nombre;


        // Se piden los datos desde el archivo
        archivo_servicios >> nombre;
        archivo_servicios >> limite_diario >> limite_mensual;

        string hora_inicio, hora_final;
        archivo_servicios >> hora_inicio >> hora_final;

        // Se crea un struct de Servicio y se le asignan los valores
        Servicio servicio_actual;
        servicio_actual.nombre = nombre;
        servicio_actual.limite_diario = limite_diario;
        servicio_actual.limite_mensual = limite_mensual;
        servicio_actual.hora_inicio = hora_inicio;
        servicio_actual.hora_final = hora_final;

        // Se le asigna al arreglo de servicios
        servicios[i] = servicio_actual;
    }

    // Se cierra el archivo ya que no necesitamos más información de aquí
    archivo_servicios.close ();

    // Archivo tickets
    ifstream archivo_tickets("tickets.dat", ios::binary);

    // En el caso de que no se pueda abrir, el programa no seguirá
    if (!archivo_tickets) {
        cerr << "[Error] No se ha podido abrir el archivo tickets.dat" << endl;
        return 1;
    }

    // m seria la cantidad de tickets
    int m;
    archivo_tickets.read( (char*)&m, sizeof(int) );

    // Se crea el arreglo de tickets y se leen m tickets.
    Ticket tickets[m];
    for (int i = 0; i < m; i++) {
        Ticket ticket_actual;
        archivo_tickets.read( (char*)&(ticket_actual), sizeof(Ticket) );

        // Se le asignan los tickets
        tickets[i] = ticket_actual;
    }

    // Se ordenan los datos de los tickets y servicios
    // Se usa el algoritmo MergeSort que funciona en base a la técnica
    // de dividir y conquistar ordenando en complejidad O(n log2n)
    merge_sort_tickets(tickets, 0, m-1, m);
    merge_sort_servicios(servicios, 0, n-1, n);

    // Pasamos el primer rut como un string
    string rut = charArrayToString(tickets[0].rut_funcionario, 10);

    // Creamos las variables por defecto
    int validos = 0;
    int total = 0;
    int dia_actual = tickets[0].day_of_month;

    int tickets_usados_servicio_por_mes[n];
    int tickets_usados_servicio_por_dia[n];

    // Inicializamos todos los valores en 0
    for(int i = 0; i < n; i++){
        tickets_usados_servicio_por_mes[i] = 0;
        tickets_usados_servicio_por_dia[i] = 0;
    }

    // Se le agrega uno, por el rut que ya contamos
    total++;
    
    // Se recorren los n tickets
    for(int j = 0; j < n; j++){

        // Se obtiene la hora del ticket y se pasa a string
        string hora_ticket = charArrayToString(tickets[0].time, 6);

        // Se revisa en que posición se encuentra la hora que se obtuvo
        int retorno = horaContiene(servicios[j].hora_inicio, servicios[j].hora_final, hora_ticket);

        // Si está completamente contenida por la hora
        if(retorno == 0){
            if(tickets_usados_servicio_por_dia[j] < servicios[j].limite_diario && tickets_usados_servicio_por_mes[j] < servicios[j].limite_mensual){
                validos++;
                tickets_usados_servicio_por_dia[j]++;
                tickets_usados_servicio_por_mes[j]++;
            }

        // Si se encuentra a la derecha
        } else if(retorno == 1){
            tickets_usados_servicio_por_dia[j] = 0;

        // Si se encuentra a la izquierda
        } else {
            if(dia_actual > tickets[0].day_of_month) 
                tickets_usados_servicio_por_dia[j] = 0;
        }
    }

    // Se recorren los m tickets
    for (int i = 1; i < m; i++) {

        // Se obtiene un rut y se pasa a string
        string rut_B = charArrayToString(tickets[i].rut_funcionario, 10);

        // Si el rut no es igual, signfica que seguimos con otra persona
        // y reiniciamos los datos
        if (!rutEsIgual(rut, rut_B)) {
            cout << rut << " " << validos << "/" << total << endl;
            rut = rut_B;
            validos = 0;
            total = 0;
            for(int i = 0; i < n; i++){
                tickets_usados_servicio_por_mes[i] = 0;
                tickets_usados_servicio_por_dia[i] = 0;
            }
        }

        // Independiente de lo que pase, sumamos uno a la cantidad de tickets totales
        total++;

        // Se recorren los n tickets
        for(int j = 0; j < n; j++){

            // Se obtiene la hora del ticket y se pasa a string
            string hora_ticket = charArrayToString(tickets[i].time, 6);

            // Se obtiene en que posición está la hora
            int retorno = horaContiene(servicios[j].hora_inicio, servicios[j].hora_final, hora_ticket);

            // Si está completamente contenida por el horario
            if(retorno == 0){
                if(dia_actual < tickets[i].day_of_month){ 
                    dia_actual = tickets[i].day_of_month; 
                    tickets_usados_servicio_por_dia[j] = 0;
                }
                if(tickets_usados_servicio_por_dia[j] < servicios[j].limite_diario && tickets_usados_servicio_por_mes[j] < servicios[j].limite_mensual){
                    validos++;
                    tickets_usados_servicio_por_dia[j]++;
                    tickets_usados_servicio_por_mes[j]++;
                }
            
            // Si la hora está a la derecha
            } else if(retorno == 1){
                tickets_usados_servicio_por_dia[j] = 0;

            // Si la hora está a la izquierda
            } else {
                if(dia_actual > tickets[i].day_of_month) {
                    dia_actual = tickets[i].day_of_month; 
                    tickets_usados_servicio_por_dia[j] = 0;
                }
            }
        }
    }

    // Se imprime el rut correspondiente
    cout << rut << " " << validos << "/" << total << endl;

    // Se cierra el archivo, ya que no está en uso
    archivo_tickets.close();

    return 0;
}
