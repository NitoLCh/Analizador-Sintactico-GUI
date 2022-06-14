#ifndef ANALIZADORLEXICO_H
#define ANALIZADORLEXICO_H

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string>
#include "pila.h"

using namespace std;

class AnalizadorLexico
{
public:
    AnalizadorLexico();

    int i, inicioToken, estadoInicial, estadoActual;
    string* resultado;
    string cadena;

    //palabras reservadas
    //Sabemos que declarar estas variables aqui no es lo ideal, porque consumimos memoria
    //y en ciertos casos no llegamos a utilizar todo
    char palabras[3][6] = {"int", "char", "float"};
    char op[5] = {'+','-', '*', '/', '%'};

    Pila scanner();
    void inicializaEstados();
    void fallo();
    char leerCar(string car);
    void retrocederCar();
    bool esReservada(string palabra);

    bool estadoAceptacion();
    bool esDelimitador(char c);
    bool esLetra(char c);
    bool esDigito(char c);
    void operador(char, string);

    void setCadena(string cadena);
    string getCadena();
    void setResultado(string *resultado);
    string* getResultado();

    void mostrar();

};

#endif // ANALIZADORLEXICO_H



