#include "pila.h"
#include <stack>
#include <string.h>
#include <iostream>

using namespace std;

#define MAX 50
stack<char> stck;

Pila::Pila()
{

}

char Pila::tope()
{
    return stck.top();
}

//UTILIZAR SU CLASE PILA
void insertapila(string elem){//(char *elem) //(char elem[])
    for(char c : elem)
        stck.push(c);
}

void eliminapila(){
        stck.pop();
}


