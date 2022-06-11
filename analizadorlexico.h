#ifndef ANALIZADORLEXICO_H
#define ANALIZADORLEXICO_H

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>

using namespace std;

class AnalizadorLexico
{
public:
    AnalizadorLexico();

    int i, inicioToken, estadoInicial, estadoActual;
    string reservada = "";

    //palabras reservadas
    char palabras[3][6] = {"int", "char", "float"};
    char op[5] = {'+','-', '*', '/', '%'};
    string Tokens[20];

    void scanner(string cadena, string *resultado);
    void inicializaEstados();
    void fallo();
    char leerCar(string car);
    void retrocederCar();

    bool estadoAceptacion();
    bool esDelimitador(char c);
    bool esLetra(char c);
    bool esDigito(char c);
    bool esReservada(string palabra);
<<<<<<< HEAD


    //Pruneda se te olvido definir getTokens aca xD
=======
    //Pruneda se te olvido definir getTokens aca xd
>>>>>>> ed193d0376293c061c4aec3da037f5e0038ba2be
    void getTokens(string *STokens);
};

#endif // ANALIZADORLEXICO_H



