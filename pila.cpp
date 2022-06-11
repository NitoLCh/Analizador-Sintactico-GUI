#include "pila.h"
#include <stack>
#include <string.h>
#include <iostream>

using namespace std;

#define MAX 50
stack<char>pila;

Pila::Pila()
{

}

char Pila::tope()
{
    return pila.top();
}

//UTILIZAR SU CLASE PILA
void insertapila(string elem)//(char *elem) //(char elem[])
{
    if(pila.top() == -1)
    {
        pila.top() = 0;
        strcpy(&pila.top(),elem.c_str());
    }
    else
    {
        if(pila.top() == MAX - 1)
            puts("Pila LLena");
        else
        {
            pila.top();
            strcpy(&pila.top(),elem.c_str());
        }                        //pilac[cima+1][0]='\0';
    }
}

void eliminapila()
{
    if(pila.top() == -1)

        //IMPLEMENTAR VENTANA EMERGENTE
        puts("Pila Vacia");
    else
    {
        strcpy(&pila.top(),"");
        pila.pop();
    }
}


