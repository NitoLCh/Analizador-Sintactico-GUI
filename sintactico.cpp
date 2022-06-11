#include "sintactico.h"
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "pila.h"
//Commented by Water :D
using namespace std;

//----------------------------------------- NOSOTROS SOMOS MODULO SINTACTICO ----------------------------------------------------//
#define MAXTOKEN 20
#define NUMPALRES 4
#define MAX 50

string PalRes[5][10] = {"char", "float", "int", "puts"};
string sLexema[127];
string sLinea[127];
string non[6] = {"1","3","5","7","9"};
string par[6] = {"2","4","6","8","0"};

// QUITAMOS LOS METODOS DE ARCHIVOS Y LEXICOS
int estoken(char x[]);

string asTokens [MAXTOKEN];
Pila pila;

//Matriz para los tokens
//                          1   2   3   4    5   6    7     8      9     10      11    12  13     14     15  16  17  18  19
string token[20] = {"x",";",",","*","Id","[","]","Num","char","int","float","puts","(",")","Cte.Lit","=","+","$","{","}"};

//Matriz para los terminales
//                             1   2   3   4    5    6   7    8   9   10  11  12
string terminal[13] = {"x","D","L","L'","I","I'","A","A'","K","T","F","E","P"};

int tablaM[32][8] = {
//                      fila, columna, terminal -> terminal|token|λ, terminal|token|λ, terminal|token|λ, terminal|token|λ, terminal|token|λ
                        {1, 8 , 1, 9, 2, -1, 999, 999},         // D, char PRODUCE -> D -> TL;
                        {1, 9 , 1, 9, 2, -1, 999, 999},         // D, int PRODUCE -> D -> TL;
                        {1, 10, 1, 9, 2, -1, 999, 999},         // D, float PRODUCE -> D -> TL;
                        //-----------------------------------------------------------------------------//
                        {2, 3 , 2, 4, 3, 999, 999, 999},        // L, * PRODUCE -> L -> IL'
                        {2, 4 , 2, 4, 3, 999, 999, 999},        // L, Id PRODUCE -> L -> IL'
                        //-----------------------------------------------------------------------------//
             /* 5 */    {3, 1 , 3, 999, 999, 999, 999, 999},    // L', ; PRODUCE -> L' -> λ
                        {3, 2 , 3, -2, 5, 3, 999, 999},         // L', , PRODUCE -> L' -> ,I'L'     CORREGIDA
                        {3, 18, 3, 5, 999, 999, 999, 999},      // L', { PRODUCE -> L' -> I'        AGREGADA
                        {3, 19, 3, -19, 999, 999, 999, 999},    // L', } PRODUCE -> L' -> }         AGREGADA
                        //-----------------------------------------------------------------------------//
                        {4, 3, 4, -3, -4, 5, 999, 999},         // I, * PRODUCE -> I -> *IdI'
                        {4, 4, 4, -4, 5, 999, 999, 999},        // I, Id PRODUCE -> I -> IdI'
                        //-----------------------------------------------------------------------------//
                        {5, 1, 5, 999, 999, 999, 999, 999},     // I', ; PRODUCE -> I' -> λ
            /* 10 */    {5, 2, 5, 999, 999, 999, 999, 999},     // I', , PRODUCE -> I' -> λ
                        {5, 5, 5, 6, 999, 999, 999, 999},       // I', [ PRODUCE -> I' -> A
                        {5, 15, 5, -15, 5, 999, 999, 999},      // I', = PRODUCE -> I' -> =I'       AGREGADA
                        {5, 16, 5, 999, 999, 999, 999, 999},    // I', + PRODUCE -> I' -> λ         AGREGADA
                        {5, 17, 5, 999, 999, 999, 999, 999},    // I', $ PRODUCE -> I' -> λ         AGREGADA
                        {5, 18, 5, 999, 999, 999, 999, 999},    // I', { PRODUCE -> I' -> λ         AGREGADA
                        {5, 19, 5, 999, 999, 999, 999, 999},    // I', } PRODUCE -> I' -> λ         AGREGADA
                        //-----------------------------------------------------------------------------//
                        {6, 5, 6, -5, 8,-6, 7, 999},            // A, [ PRODUCE -> A -> [K]A'
                        //-----------------------------------------------------------------------------//
                        {7, 1, 7, 999,999,999,999,999},         // A', ; PRODUCE -> A' -> λ
                        {7, 2, 7, 999,999,999,999,999},         // A', , PRODUCE -> A' -> λ
            /* 15 */  //{7, 5, 6, -5, 8, -6, 7, 999},           // A', [ PRODUCE -> A -> [K]A'    *ERROR*
                        //-----------------------------------------------------------------------------//
                        {8, 4, 8, -4, 999, 999,999,999},        // K, Id PRODUCE -> K -> Id
                        {8, 7, 8, -7, 999,999,999,999},         // K, num PRODUCE -> K -> num
                        //-----------------------------------------------------------------------------//
                        {9, 8, 9, -8,999,999,999,999},          // T, char PRODUCE -> T -> char
             /* -> */   {9, 9, 9, -9,999,999,999,999},          // T, int PRODUCE -> T -> int
             /* 20 */   {9, 10, 9, -10,999,999,999,999},        // T, float PRODUCE -> T -> float
                        //----------------------------- segunda gramatica -----------------------------//
                        {10, 11, 10, -11, 11, -1,999,999},      // F, puts PRODUCE -> F -> putsE    CORREGIDA
                        //-----------------------------------------------------------------------------//
                        {11, 12, 11,-12,12,-13,999,999},        // E, ( PRODUCE -> E -> (P)
                        //-----------------------------------------------------------------------------//
                        {12,14,12,-14,999,999,999,999},         // P, Cte.Lit PRODUCE -> P -> Cte.Lit
                        {12, 4, 12, -4,999,999,999,999}         // P, Id PRODUCE -> P -> Id
                        //-----------------------------------------------------------------------------//
};

// USAR DE PARAMETRO UN OBJETO SOBRE EL CUAL ESCRIBIR
Sintactico::Sintactico()
{

    int ip =  0, i, j;
    int renglon, iast;
    char x[10], a[10];
    pila.insertapila("$"); //InsertarPila

    //if(strcmp(asTokens[ip],"puts")== 0)
    if(asTokens[ip].compare("puts") == 0)
        pila.insertapila("F");
    else
        pila.insertapila("D");

    //Salidas a pantalla
     printf("\nSalida del Analizador Sintactico (asTokens) \n\n");
     printf("Arreglo de Tokenss: \n\n");

    for(i = 0; asTokens[i].compare("$") != 0; i++)
        printf("%s ", asTokens[i].c_str());

    printf("\n\n Producciones: \n\n");

    do
    {
        //copy(pila.top(), x, pila.top());
        /*x[1] = pila.top().
        strcpy(a, asTokens[ip]);*/
        strcpy(x,pila.tope().c_str());
        strcpy(a,asTokens[ip].c_str());

        if(estoken(x) || (strcmp(x, "$") == 0))
        {
            if(strcmp(x, a) == 0)
            {
                pila.eliminapila();
                ip++;
            }
            else
            {
                if(asTokens[ip].compare("puts") == 0)
                    pila.push("F");
                else
                    pila.push("D");
                pila.top().copy(x, 0, sizeof(pila.top())-1);
            }
        }
        else //SI NO ES TOKEN(TERMINAL)
        {

        }
    }while(strcmp(x,"$")!= 0);
}

int Sintactico::buscaTabla(string a[], string x[])
{
    int indx = 0;
    int inda = 0, i;
    for (i = 0; i < 15; i++)
        if()


}
























