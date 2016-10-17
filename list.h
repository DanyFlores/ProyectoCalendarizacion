#ifndef __list_
#define __list_

#include <iostream>
#include "node.h"
using namespace std;

class list {
   private:
       node *first;
       node *actual;
       bool emptyness(){
        return(this->first == NULL);
       }
   public:
    list(){
        this->first = NULL;
        this->actual = NULL;
    }
    void insertar(int time, int prior, char name){
        node *nuevo = new node(prior, time,name);
        if(emptyness()){
            this->first = nuevo;
        } else {
            this->actual->next = nuevo;
        }
        this->actual = nuevo;
    }

    void imprimir(){
        node *p = first;
        do {
            cout << p->nombre << "(" << p->tiempo << "," << p->prioridad << ")";
            cout << "->";
            p = p->next;
        } while(p != NULL);
        cout << "NULL";
    }
};

#endif // __list_
