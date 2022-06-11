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


    //Pruneda se te olvido definir getTokens aca xD
    void getTokens(string *STokens);
};

#endif // ANALIZADORLEXICO_H



