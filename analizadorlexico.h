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
    //Pruneda se te olvido definir getTokens aca xd
    void getTokens(string *STokens);
};

#endif // ANALIZADORLEXICO_H



