#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;
list * lista = new list; //Declaración de la lista a utilizar para el método FIFO
list * listaRR = new list; // Declaración de la lista a utilizar para el método RR
list * listaSJF = new list; //Declaración de la lista a utilizar para el método SJF
list * listaPriori = new list; //Declaración de la lista a utilizar para el método por prioridad
int ttotal=0, quantum=0, procesos=0; //Declaración de variables distintas a utilizar durante la ejecución
//Función para imprimir el menú de opciones, así como el quantum cuando este haya sido calculado
void imprimeMenu(){
    cout << ".:Calendarizacion de procesos:." << endl
         << "1.-Llenado de lista." << endl
         << "2.-Algoritmo FIFO" << endl
         << "3.-Algoritmo SJF" << endl
         << "4.-Algoritmo Round-Robin" << endl
         << "5.-Algoritmo por prioridad" << endl
         << "6.-Salir." << endl
         << "Elige una opción: ";
         if(quantum > 0){
            cout << endl << "Quantum: " << quantum << endl;
         }
}
//Método para insertar procesos en las distintas listas creadas
void crearProcesos(){
    char sel, nombre; int tiempo, priori; //Variables para almacenar los datos a insertar en los nodos
    cout << endl << "Creación de procesos";
    do {
        cout << endl << "Inserte caracter de proceso: ";
        cin >> nombre; //Almacena el nombre (o identificador) del proceso
        cout << "Inserte tiempo del proceso: ";
        cin >> tiempo; //Almacena el tiempo del proceso
        cout << "Inserte prioridad del proceso: ";
        cin >> priori; //Almacena la prioridad del proceso
        ttotal += tiempo; //Calcula el tiempo total necesario para terminar de procesar todos los procesos
        lista->insertar(tiempo, priori, nombre); //Crea un nuevo nodo, insertando los datos almacenados previamente
        procesos++; //Aumenta la cantidad de procesos almacenados
        quantum = ttotal / procesos; //Calcula el quantum
        listaRR->insertar(tiempo, priori, nombre); //Inserta un nuevo nodo en la lista para el algoritmo Round-Robin
        cout << "Continuar agregando procesos? (s/n): "; //Pregunta si se desea continuar agregando nodos (procesos) a la lista
        cin >> sel;
    } while(sel != 'n');
    if(sel == 'n'){
        lista->imprimir(); //Imprime la lista de procesos después de finalizar la captura
    }
}

int main(){
    int opc;
    do {
        imprimeMenu(); //Imprime el menú de opciones
        cin >> opc; //Almacena la opción deseada
        switch(opc){ //Comienza la ejecución del menú de acuerdo a la opción seleccionada
            case 1: crearProcesos(); break; //Comienza la captura de procesos
            case 2: lista->impresionFIFO(); break; //Realiza la impresión del método FIFO
            case 3: break; //Realiza la impresión del método SJF
            case 4: lista->metodoRR(quantum); break; //Realiza la impresión del método Round-Robin
            case 5: break; //Realiza la impresión del método por prioridad
            case 6: cout << "Saliendo..." << endl; delete lista; break; //Termina la ejecución del programa, además de eliminar las listas utilizadas para limpiar la memoria
            default: cout << "Opción no válida, intente de nuevo"; break; //De seleccionar una opción no válida, imprime un mensaje indicando que no es una opción válida

        }
    } while(opc != 6);
    return 0;
}
