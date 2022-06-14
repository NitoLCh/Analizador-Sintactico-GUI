#include "sintactico.h"
#include <string>
#include <string.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "pila.h"
#include "analizadorlexico.h"
//Commented by Water :D
using namespace std;

//----------------------------------------- NOSOTROS SOMOS MODULO SINTACTICO ----------------------------------------------------//

#define NUMPALRES 4
AnalizadorLexico anlex;

//Tenemos en un arreglo las palabras reservadas
string PalRes[5] = {"char", "float", "int", "puts"};
//string sLexema[127];
//string sLinea[127];
string non[6] = {"1","3","5","7","9"};//
string par[6] = {"2","4","6","8","0"};//

// QUITAMOS LOS METODOS DE ARCHIVOS Y LEXICOS
//string asTokens [MAXTOKEN];
Pila copiaAsTokens = anlex.scanner();

Pila pila; //Como tenemos una clase dinamica la estatica se desecha

//-------------------------------------------------------------------------------------------------------------------------------//

//Arreglo para los tokens
//                       1   2   3   4    5   6    7     8      9     10      11    12  13     14    15   16  17  18  19
string token[20] = {"x",";",",","*","Id","[","]","Num","char","int","float","puts","(",")","Cte.Lit","=","+","$","{","}"};

//Arreglo para los terminales
//                          1   2   3   4    5    6   7    8   9   10  11  12
string terminal[13] = {"x","D","L","L'","I","I'","A","A'","K","T","F","E","P"};

//-------------------------------------------------------------------------------------------------------------------------------//

//Matriz que contiene la tabla M
int tablaM[32][8] = {
    //fila, columna, terminal -> terminal|token|λ, terminal|token|λ, terminal|token|λ, terminal|token|λ, terminal|token|λ
    {1, 8 , 1, 9, 2, -1, 999, 999},         // D, char PRODUCE -> D -> TL;
    {1, 9 , 1, 9, 2, -1, 999, 999},         // D, int PRODUCE -> D -> TL;
    {1, 10, 1, 9, 2, -1, 999, 999},         // D, float PRODUCE -> D -> TL;
    //-----------------------------------------------------------------------------//
    {2, 3 , 2, 4, 3, 999, 999, 999},        // L, * PRODUCE -> L -> IL'
    {2, 4 , 2, 4, 3, 999, 999, 999},        // L, Id PRODUCE -> L -> IL'
    //-----------------------------------------------------------------------------//
    /* 5 */    {3, 1, 3, 999, 999, 999, 999, 999},     // L', ; PRODUCE -> L' -> λ
    {3, 2 , 3, -2, 5, 3, 999, 999},         // L', , PRODUCE -> L' -> ,I'L'     CORREGIDA
    {3, 3, 3, -3, 5, 3, 999, 999},          // L', * PRODUCE -> L' -> *I'L'     AGREGADA
    {3, 16, -16, 5, 3, 999, 999, 999},      // L', + PRODUCE -> L' -> +I'L'     AGREGADA
    {3, 18, 3, -18, 5, -19, 999, 999},      // L', { PRODUCE -> L' -> {I'}      AGREGADA
    //{3, 19, 3, -19, 999, 999, 999, 999},    // L', } PRODUCE -> L' -> }       AGREGADA
    //-----------------------------------------------------------------------------//
    {4, 3, 4, -3, -4, 5, 999, 999},         // I, * PRODUCE -> I -> *IdI'
    {4, 4, 4, -4, 5, 999, 999, 999},        // I, Id PRODUCE -> I -> IdI'
    //-----------------------------------------------------------------------------//
    {5, 1, 5, 999, 999, 999, 999, 999},     // I', ; PRODUCE -> I' -> λ
    /* 10 */    {5, 2, 5, 999, 999, 999, 999, 999},     // I', , PRODUCE -> I' -> λ
    {5, 4, 5, -4, 999, 999, 999, 999},      // I', Id PRODUCE -> I' -> Id       AGREGADA
    {5, 5, 5, 6, 999, 999, 999, 999},       // I', [ PRODUCE -> I' -> A
    {5, 15, 5, -15, 5, 999, 999, 999},      // I', = PRODUCE -> I' -> =I'       AGREGADA
    //{5, 16, 5, 999, 999, 999, 999, 999},    // I', + PRODUCE -> I' -> λ       ELIMINADA
    //{5, 17, 5, 999, 999, 999, 999, 999},    // I', $ PRODUCE -> I' -> λ       ELIMINADA
    //{5, 18, 5, 999, 999, 999, 999, 999},    // I', { PRODUCE -> I' -> λ       ELIMINADA
    //{5, 19, 5, 999, 999, 999, 999, 999},    // I', } PRODUCE -> I' -> λ       ELIMINADA
    //-----------------------------------------------------------------------------//
    {6, 5, 6, -5, 8,-6, 7, 999},            // A, [ PRODUCE -> A -> [K]A'
    //-----------------------------------------------------------------------------//
    {7, 1, 7, 999,999,999,999,999},         // A', ; PRODUCE -> A' -> λ
    {7, 2, 7, 999,999,999,999,999},         // A', , PRODUCE -> A' -> λ
    /* 15 */  //{7, 5, 6, -5, 8, -6, 7, 999},  // A', [ PRODUCE -> A -> [K]A'      *ERROR*
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

//-------------------------------------------------------------------------------------------------------------------------------//

Sintactico::Sintactico(){
}

//-------------------------------------------------------------------------------------------------------------------------------//

int Sintactico::buscaTabla(string a, string x){
    int indx=0, inda=0, i;
    for(i = 0; i < 15; i++)// correccion cambiar a 20
        if(a.compare(token[i])==0)
            inda = i;     //break;
    for(i = 0; i < 13; i++)
        if(x.compare(terminal[i])==0)
            indx=i;
    for(i = 0; i < 25; i++)
    {
        if(indx == tablaM[i][0])
            if(inda == tablaM[i][1])
                return i;
    }
    return 999;
}

//-------------------------------------------------------------------------------------------------------------------------------//

int Sintactico::estoken(string x){
    int i;

    for(i=0; i<23; i++)
    {
        if(x.compare(token[i]) == 0)
            return 1;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------//

void Sintactico::analizar(){
    int ip=0, i, j;   //IP = 0   i y j no inicializan
    int renglon, iast;
    string x, a; //cambio de arreglo de char a string
    pila.insertapila("$"); //InsertarPila

    //if(strcmp(asTokens[ip],"puts")== 0)
    if(copiaAsTokens.tope().compare("puts") == 0)
        pila.insertapila("F");// primera gramatica e inicia con F
    else
        pila.insertapila("D");// segunda gramatica e inicia con D

    //Salidas a pantalla
    printf("\nSalida del Analizador Sintactico (asTokens) \n\n");
    printf("Arreglo de Tokenss: \n\n");

    for(i = 0; copiaAsTokens.tope().compare("$") != 0; i++)
        printf("%s ", copiaAsTokens.tope().c_str());

    printf("\n\n Producciones: \n\n");
    //buscar tokens residuales como el ;
    do
    {
        //copy(pila.top(), x, pila.top());
        /*x[1] = pila.top().
        strcpy(a, asTokens[ip]);*/
        //strcpy(&x, pila.tope());
        //strcpy(&a, asTokens[ip].c_str());
        x = pila.tope();

        if(estoken(x) || (x.compare("$") == 0))
        {
            if(x.compare(a) == 0)
            {
                pila.eliminapila();
                ip++;
            }
            else{
                if(copiaAsTokens.tope().compare("puts") == 0)
                    pila.insertapila("F");
                else
                    pila.insertapila("D");
                //pila.top().copy(x, 0, sizeof(pila.top())-1);
                x = pila.tope();
            }
        }
        else{ //SI NO ES TOKEN(TERMINAL)
            renglon = buscaTabla(a,x);
            if(renglon != 999){
                pila.eliminapila();
                iast = 0;
                printf("%-3s -> ", terminal[tablaM[renglon][0]].c_str());
                for(j= 3; iast != 999; j++){
                    iast = tablaM[renglon][j];  //999
                    if(iast < 0){
                        iast *= -1;
                        printf("%s ",token[iast].c_str());

                    }
                    else{
                        if(iast !=999)
                            printf("%s", terminal[iast].c_str());
                    }
                }
                printf("\n");
                for(i = j-2; i > 2; i--){
                    iast = tablaM[renglon][i];
                    if(iast < 0){
                        iast *= -1;
                        pila.insertapila(token[iast]);
                    }
                    else
                        pila.insertapila(terminal[iast]);
                }
            }
            else{
                printf("\n\n Error de Sintaxis ");
                return;
            }
        }
    }while(x.compare("$")!= 0);
}

//------------------------------------------------------------------------------------------------------------------------------ //
