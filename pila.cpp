#include "pila.h"


Pila::Pila(){

}

string Pila::tope(){
    return stck->top();
}

stack<string>* Pila::copiarPila(){
    stack<string> *copia;
    copia = this->stck;
    return copia;
}

//UTILIZAR SU CLASE PILA
void Pila::insertapila(string elem){//(char *elem) //(char elem[])
    stck->push(elem);
}

void Pila::eliminapila(){
    stck->pop();
}
