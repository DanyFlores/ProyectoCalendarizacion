#ifndef __node_
#define __mode_

#include <iostream>
using namespace std;

class node {
private:
    int prioridad, tiempo;
    char nombre;
    node *next;
public:
    node(int priori, int time, char name, node *nxt = NULL){
        this->prioridad = priori;
        this->tiempo = time;
        this->nombre = name;
        next = nxt;
    }
    friend class list;
};

#endif // __node_

