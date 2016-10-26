#ifndef __node_
#define __mode_

#include <iostream>
using namespace std;

class node {
private: //Declaración del contenido de los nodos como privados
    int prioridad, tiempo; //Cada nodo almacena dos datos de tipo entero: su tiempo requerido y su prioridad
    char nombre; //Cada nodo almacena también un dato de tipo caracter: El nombre (o identificador) del proceso
    node *next; //Además, almacena un apuntador al siguiente nodo
public:
    node(int priori, int time, char name, node *nxt = NULL){ //Constructor de un nodo que recibe los tres parámetros a almacenar en el nodo, además de establecer su siguiente a NULL
        this->prioridad = priori; //Almacena la prioridad declarada en el nodo
        this->tiempo = time; //Almacena el tiempo indicado en el nodo
        this->nombre = name; //Almacena el nombre (o identificador) indicado en el nodo
        next = nxt; //Establece que el nodo apunta a NULL, mientras no se modifique
    }
    friend class list; //Declara la clase list como clase amiga, con el fin de que esta pueda utilizar sus métodos.
};

#endif // __node_

