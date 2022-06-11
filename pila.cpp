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
void insertapila(string elem)//(char *elem) //(char elem[])
{
    if(stck.top() == -1)
    {
        stck.top() = 0;
        strcpy(&stck.top(),elem.c_str());
    }
    else
    {
        if(stck.top() == MAX - 1)
            puts("Pila LLena");
        else
        {
            stck.top();
            strcpy(&stck.top(),elem.c_str());
        }                        //pilac[cima+1][0]='\0';
    }
}

void eliminapila()
{
    if(stck.top() == -1)

        //IMPLEMENTAR VENTANA EMERGENTE
        puts("Pila Vacia");
    else
    {
        strcpy(&stck.top(),"");
        stck.pop();
    }
}


