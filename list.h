#ifndef __list_
#define __list_

#include <iostream>
#include "node.h"
using namespace std;

class list {
   private:
       node *first;
       node *actual;
       //Prueba para saber si la lista est� vac�a
       bool emptyness(){
        return(this->first == NULL);
       }
   public:
    list(){
        this->first = NULL;
        this->actual = NULL;
    }
    //M�todo para insertar nodos (procesos) a la lista
    void insertar(int time, int prior, char name){
        node *nuevo = new node(prior, time,name); // Creaci�n de un nuevo nodo
        if(emptyness()){ //Prueba para determinar si es el primer nodo o no
            this->first = nuevo; //De ser verdadera, el nodo se inserta al inicio
        } else {
            this->actual->next = nuevo; // De lo contrario, se inserta despu�s del �ltimo nodo insertado
        }
        this->actual = nuevo; //El nuevo nodo se vuelve el �ltimo insertado
    }
    //M�todo para imprimir la lista despu�s de insertar los datos
    void imprimir(){
        node *p = first; //Inicializaci�n del nodo utilizado para recorrer la lista
        do {
            cout << p->nombre << "(" << p->tiempo << "," << p->prioridad << ")"; //Imprime la informaci�n almacenada en el nodo (Formato: Nombre(Tiempo,Prioridad).
            cout << "->"; //Flecha apuntadora al siguiente nodo
            p = p->next; //El nodo de recorrido avanza al siguiente nodo
        } while(p != NULL);
        cout << "NULL" << endl; //Impresi�n de NULL para indicar el final de la lista
    }

    //M�todo para realizar la impresi�n por algoritmo FIFO, con tiempos de retorno
    void impresionFIFO(){
        if(!emptyness()){ //Prueba l�gica para evitar errores en la ejecuci�n
            int TRs = 0; //Variable para almacenar los Tiempos de Retorno de cada proceso
            node *aux = first; //Nodo auxiliar para avanzar la impresi�n
            node *p; //Nodo de recorrido de la lista para impresi�n de la misma
            do {
                p = aux; //Establecer el nodo de recorrido al nodo por procesar
                do{
                    cout << p->nombre << "(" << p->tiempo << "," << p->prioridad << ")"; //Impresi�n del nodo (Formato: Nombre(Tiempo,Prioridad)).
                    cout << "->"; //Flecha apuntadora al siguiente nodo
                    p = p->next; //El nodo de recorrido avanza al siguiente nodo.
                } while(p != NULL);
                cout << "NULL" << endl; //Impresi�n de NULL para indicar el final de la lista.
                TRs = TRs + aux->tiempo; //Se guarda el nuevo tiempo de retorno para cada proceso, sumando su tiempo a los tiempos de los anteriores
                cout << endl << "Tiempo de retorno de " << aux->nombre << ": " << TRs << endl; //Impresi�n del tiempo de retorno del nodo procesado
                aux = aux->next; //Avanza el nodo auxiliar para indicar el siguiente nodo a procesar
            } while (aux != NULL);
        } else {
            cout << "Lista vacia." << endl; //De otra manera, se imprime que la lista est� vac�a para evitar crash del programa
        }
    }

    //M�todo para impresi�n del algoritmo Round-Robin
    void metodoRR(int quantum){ //Recibe como par�metro el quantum, que resulta como promedio de los tiempos ingresados a lo largo de la captura
        if(!emptyness()){ //Prueba l�gica para comprobar que la lista no est� vac�a; de ser verdadera, procede con la impresi�n
            int TRs = 0; //Declaraci�n de la variable para almacenar los tiempos de retorno
            node *p = first; //Inicializaci�n del nodo que recorre la lista
            do {
                if(p->tiempo <= quantum){ //Prueba l�gica para determinar si el quantum asignado es suficiente para procesar el nodo. De cumplirse:
                    impresionRR(p); //Muestra la lista de nodos a procesar
                    TRs += p->tiempo; //Aumenta el tiempo de retorno del proceso
                    cout << "Tiempo de retorno de " << p->nombre << ": " << TRs << endl; //Muestra en pantalla el tiempo de retorno del proceso
                    p = p->next; //El nodo de recorrido avanza al siguiente nodo
                } else { //De no cumplirse:
                    impresionRR(p); //Muestra la lista de nodos a procesar
                    TRs += quantum; //Aumenta a los tiempos de retorno el quantum
                    int newTime = p->tiempo - quantum; //Calcula el tiempo restante para procesar al nodo
                    insertar(newTime, p->prioridad, p->nombre); //A�ade el nodo al final de la lista para procesarlo posteriormente
                    p = p->next; //El nodo empleado para el recorrido avanza al siguiente nodo
                }
            } while(p != NULL);
        }
    }
    //M�todo para mostrar en pantalla la lista de procesos para el m�todo Round-Robin
    void impresionRR(node *inicial){ //La funci�n recibe como par�metro el nodo desde el cual comenzar� a mostrar (el cual es el nodo a procesar)
        node *p = inicial; //Inicializa un nuevo nodo para realizar el recorrido
            do{
                cout << p->nombre << "(" << p->tiempo << "," << p->prioridad << ")"; //Muestra el nodo actual
                cout << "->"; //Muestra la flecha que apunta al siguiente nodo
                p = p->next; //Avanza el nodo de recorrido al siguiente nodo
            } while(p != NULL);
            cout << "NULL" << endl; // Muestra NULL en pantalla, indicando el final de la lista.
    }
    //M�todo para insertar datos de manera ordenada (tomando como argumento para el ordenamiento el tiempo requerido)
    void insertarSJF(int tiempo, int prioridad, char nombre){
        node *nuevo = new node(prioridad, tiempo, nombre); //Creaci�n del nodo a insertar
        if(emptyness()){ //Si la lista est� vac�a, establece el nodo creado como primer nodo de la lista
            this->first = nuevo;
            this->actual = first; //Establece el nodo creado como el �ltimo nodo insertado
        } else if(nuevo->tiempo < first->tiempo){ // De otro modo, si el tiempo del nuevo nodo es menor al del primero
            nuevo->next = first; //Se establece el nuevo nodo como primer nodo, recorriendo la lista hacia la derecha
            this->first = nuevo;
        } else if(nuevo->tiempo > actual->tiempo){ //De otro modo, si el tiempo del nuevo nodo es mayor al del �ltimo nodo, se agrega el nodo al final
            this->actual->next = nuevo;
            this->actual = nuevo;
        } else { // De otro modo, se recorre la lista hasta que el nodo se pueda posicionar entre uno con menor tiempo y uno con mayor tiempo que el nodo reci�n creado
            node *q = first; //Nodo principal
            node *r = q->next; //Nodo auxiliar
            do {

                if(nuevo->tiempo > q->tiempo && nuevo->tiempo < r->tiempo){ //Si el tiempo del nuevo nodo es mayor al anterior y menor al siguiente
                    nuevo->next = r; //Se inserta el nodo entre esos nodos
                    q->next = nuevo;
                } else{
                    q = q->next; //De otra manera contin�a recorriendo la lista
                    r = r->next;
                }
            } while(r->next != NULL); //Se repite mientras el nodo secundario no sea nulo

        }
    }

    void insertarPrioridad(int tiempo, int prioridad, char nombre){
        node *nuevo = new node(prioridad, tiempo, nombre); //Creaci�n del nodo a insertar
        if(emptyness()){ //Si la lista est� vac�a, establece el nodo creado como primer nodo de la lista
            this->first = nuevo;
            this->actual = nuevo; //Establece el nodo creado como el �ltimo nodo insertado
        } else if(nuevo->prioridad < actual->prioridad){ // De otro modo, si el tiempo del nuevo nodo es menor al del primero
            this->actual->next = nuevo;  //Se establece el nuevo nodo como primer nodo, recorriendo la lista hacia la derecha
            this->actual = nuevo;
        } else if(nuevo->prioridad > first->prioridad){ //De otro modo, si el tiempo del nuevo nodo es mayor al del �ltimo nodo, se agrega el nodo al final
            nuevo->next = first;
            this->first = nuevo;
        } else { // De otro modo, se recorre la lista hasta que el nodo se pueda posicionar entre uno con menor tiempo y uno con mayor tiempo que el nodo reci�n creado
            node *q = first; //Nodo principal
            node *r = q->next; //Nodo auxiliar
            do {
                if(nuevo->prioridad < q->prioridad && nuevo->prioridad > r->prioridad){ //Si el tiempo del nuevo nodo es mayor al anterior y menor al siguiente
                    nuevo->next = r; //Se inserta el nodo entre esos nodos
                    q->next = nuevo;
                    break;
                } else if(nuevo->prioridad < q->prioridad && nuevo->prioridad == r->prioridad){
                    nuevo->next = r->next;
                    r->next = nuevo;
                    break;
                } else{
                    q = q->next; //De otra manera contin�a recorriendo la lista
                    r = r->next;
                }
            } while(r->next != NULL); //Se repite mientras el nodo secundario no sea nulo
        }
    }

   void metodoPrioridad(int quantum){
        if(!emptyness()){ //Prueba l�gica para comprobar que la lista no est� vac�a; de ser verdadera, procede con la impresi�n
            int TRs = 0; //Declaraci�n de la variable para almacenar los tiempos de retorno
            node *p = first; //Inicializaci�n del nodo que recorre la lista
            do {
                if(p->tiempo <= quantum){ //Prueba l�gica para determinar si el quantum asignado es suficiente para procesar el nodo. De cumplirse:
                    impresionRR(p); //Muestra la lista de nodos a procesar
                    TRs += p->tiempo; //Aumenta el tiempo de retorno del proceso
                    cout << "Tiempo de retorno de " << p->nombre << ": " << TRs << endl; //Muestra en pantalla el tiempo de retorno del proceso
                    p = p->next; //El nodo de recorrido avanza al siguiente nodo
                } else { //De no cumplirse:
                    impresionRR(p); //Muestra la lista de nodos a procesar
                    TRs += quantum; //Aumenta a los tiempos de retorno el quantum
                    int newTime = p->tiempo - quantum; //Calcula el tiempo restante para procesar al nodo
                    int newPriori = p->prioridad - 1;
                    insertarPrioridad(newTime, newPriori, p->nombre); //A�ade el nodo al final de la lista para procesarlo posteriormente
                    p = p->next; //El nodo empleado para el recorrido avanza al siguiente nodo
                }
            } while(p != NULL);
        }
    }
};
#endif // __list_
