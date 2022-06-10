#include "sintactico.h"
#include <string>
#include <stack>

using namespace std;


//----------------------- NOSOTROS SOMOS MODULO SINTACTICO -------------
#define MAXTOKEN 20

// QUITAMOS LOS METODOS DE ARCHIVOS Y LEXICOS
int estoken(char x[]);

string asTokens [MAXTOKEN][10];
stack<string> pila;
int estoken(string x[]);

//------------------------------------ ARREGLOS ----------------------------

char token[15][8] = {"x",";",",","*","Id","[","]","Num","char","int","float","puts","(",")","Cte.Lit"};

char varsint[13][3]={"x","D","L","L'","I","I'","A","A'","K","T","F","E","P"};

int tablaM[25][8]= {{1, 8 , 1, 9, 2, -1, 999,999},  // PRODUCE ->
                    {1, 9 , 1, 9, 2, -1, 999,999},  // PRODUCE ->
                    {1, 10, 1, 9, 2, -1, 999,999},
                    {2, 3 , 2, 4, 3, 999, 999, 999},
                    {2, 4 , 2, 4, 3, 999, 999, 999},
         /* 5 */    {3, 1 , 3, 999,999,999,999,999},
                    {3, 2 , 3, -2, 4, 3, 999,999},
                    {4, 3, 4, -3, -4, 5, 999,999},
                    {4, 4, 4, -4, 5, 999,999,999},
                    {5, 1, 5, 999,999,999,999,999},
        /* 10 */    {5, 2, 5,999,999,999,999,999},
                    {5, 5, 5, 6, 999,999,999,999},
                    {6, 5, 6, -5, 8,-6, 7, 999 },
                    {7, 1, 7, 999,999,999,999,999},
                    {7, 2, 7, 999,999,999,999,999},
        /* 15 */    {7, 5, 6, -5, 8, -6, 7, 999},
                    {8, 4, 8, -4, 999, 999,999,999},
                    {8, 7, 8, -7, 999,999,999,999},
                    {9, 8, 9, -8,999,999,999,999},
         /* -> */   {9, 9, 9, -9,999,999,999,999},
        /* 20 */    {9,10,9,-10,999,999,999,999},
    /*segunda gramatica */
                    {10,11,10,-11,-11,-1,999,999},
                    {11, 12, 11,-12,12,-13,999,999},
                    {12,14,12,-14,999,999,999,999},
                    {12, 4, 12, -4,999,999,999,999}
};
//----------------------------------------------------------------------

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
