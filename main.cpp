#include <iostream>
#include <stdlib.h>
#include "list.h"

using namespace std;
list * lista = new list; //Declaraci�n de la lista a utilizar para el m�todo FIFO
list * listaRR = new list; // Declaraci�n de la lista a utilizar para el m�todo RR
list * listaSJF = new list; //Declaraci�n de la lista a utilizar para el m�todo SJF
list * listaPriori = new list; //Declaraci�n de la lista a utilizar para el m�todo por prioridad
int ttotal=0, quantum=0, procesos=0; //Declaraci�n de variables distintas a utilizar durante la ejecuci�n
//Funci�n para imprimir el men� de opciones, as� como el quantum cuando este haya sido calculado
void imprimeMenu(){
    cout << ".:Calendarizacion de procesos:." << endl
         << "1.-Llenado de lista." << endl
         << "2.-Algoritmo FIFO" << endl
         << "3.-Algoritmo SJF" << endl
         << "4.-Algoritmo Round-Robin" << endl
         << "5.-Algoritmo por prioridad" << endl
         << "6.-Salir." << endl
         << "Elige una opci�n: ";
         if(quantum > 0){
            cout << endl << "Quantum: " << quantum << endl;
         }
}
//M�todo para insertar procesos en las distintas listas creadas
void crearProcesos(){
    char sel, nombre; int tiempo, priori; //Variables para almacenar los datos a insertar en los nodos
    cout << endl << "Creaci�n de procesos";
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
        listaSJF->insertarSJF(tiempo, priori, nombre);
        listaPriori->insertarPrioridad(tiempo, priori, nombre);
        cout << "Continuar agregando procesos? (s/n): "; //Pregunta si se desea continuar agregando nodos (procesos) a la lista
        cin >> sel;
    } while(sel != 'n');
    if(sel == 'n'){
        lista->imprimir(); //Imprime la lista de procesos despu�s de finalizar la captura
    }
}

int main(){
    int opc;
    do {
        imprimeMenu(); //Imprime el men� de opciones
        cin >> opc; //Almacena la opci�n deseada
        switch(opc){ //Comienza la ejecuci�n del men� de acuerdo a la opci�n seleccionada
            case 1: crearProcesos(); break; //Comienza la captura de procesos
            case 2: lista->impresionFIFO(); break; //Realiza la impresi�n del m�todo FIFO
            case 3: listaSJF->impresionFIFO(); break; //Realiza la impresi�n del m�todo SJF
            case 4: lista->metodoRR(quantum); break; //Realiza la impresi�n del m�todo Round-Robin
            case 5: listaPriori->metodoPrioridad(quantum); break; //Realiza la impresi�n del m�todo por prioridad
            case 6: cout << "Saliendo..." << endl; delete lista; delete listaPriori; delete listaRR; delete listaSJF; break; //Termina la ejecuci�n del programa, adem�s de eliminar las listas utilizadas para limpiar la memoria
            default: cout << "Opci�n no v�lida, intente de nuevo"; break; //De seleccionar una opci�n no v�lida, imprime un mensaje indicando que no es una opci�n v�lida

        }
    } while(opc != 6);
    return 0;
}
