#include "sintactico.h"
#include <string>
#include <stack>

using namespace std;

#define MAXTOKEN 20

string asTokens [MAXTOKEN][10];
stack<string> pila;
int estoken(string x[]);

Sintactico::Sintactico()
{
    int ip =  0, i, j;
    int renglon, iast;
    string x[10], a[10];
    pila.push("$");

    if(asTokens[ip]->compare("puts") == 0)
        pila.push("F");
    else
        pila.push("D");

    // Salidas a pantalla

    for(i = 0; asTokens[i]->compare("$") != 0; i++)
        //printf("%s ", asTokens[i]);
    printf("\n\n Producciones: \n\n");

    do
    {
        copy(pila.top(), x);
        strcpy(a, asTokens[ip]);
        if(estoken(x) || (strcmp(x, "$") == 0))
        {

        }
    }
}
