#include "analizadorlexico.h"
AnalizadorLexico::AnalizadorLexico()
{

}
void AnalizadorLexico::scanner(string cadena, string *resultado)
{
    char caracter;
    inicializaEstados();
    i = inicioToken = 0;

    while(i < cadena.length() || estadoAceptacion()){
        switch (estadoActual) {
            //DELIMITADORES
        case 0: caracter = leerCar(cadena);
                if(esDelimitador(caracter))
                    estadoActual = 1;
                else
                    fallo();
        break;
        case 1: caracter = leerCar(cadena);
                if(esDelimitador(caracter))
                    estadoActual = 1;
                else
                    estadoActual = 2;
        break;
        case 2: retrocederCar();
                *resultado += "DELIMITADOR\n";
                inicializaEstados();
                inicioToken = i;
        break;
        case 3: caracter = leerCar(cadena);
                if(esLetra(caracter) || caracter == '_'){
                    reservada += caracter;
                    estadoActual = 4;
                }
                else{
                    reservada = "";
                    fallo();
                }
        break;
        case 4: caracter = leerCar(cadena);
                if(esLetra(caracter) || esDigito(caracter) || caracter == '_')
                {
                    reservada += caracter;
                    estadoActual = 4;
                }
                else
                    estadoActual = 5;
            break;
        case 5: retrocederCar();
                if(esReservada(reservada))
                {
                    *resultado += "PALABRA RESERVADA\n";
                    inicializaEstados();
                    inicioToken = i;
                }
                else{
                //reservada="";
                *resultado += "IDENTIFICADOR\n";
                inicializaEstados();
                inicioToken = i;
                }
        break;
                //Numeros
        case 6: caracter = leerCar(cadena);
                if(esDigito(caracter))
                    estadoActual = 7;
                else
                    fallo();
        break;
        case 7: caracter = leerCar(cadena);
                if(esDigito(caracter))
                    estadoActual = 7;
                else if(caracter == '.')
                        estadoActual = 9;
                     else
                        estadoActual = 8;
        break;
        case 8: retrocederCar();
                *resultado += "NUMERO ENTERO\n";
                inicializaEstados();
                inicioToken = i;
        break;
        case 9: caracter = leerCar(cadena);
                if(esDigito(caracter))
                    estadoActual = 9;
                else
                    estadoActual = 10;
        break;
        case 10: retrocederCar();
                *resultado += "NUMERO REAL\n";
                inicializaEstados();
                inicioToken = i;
        break;
        case 11: caracter = leerCar(cadena);
                 if(caracter == '=')
                     estadoActual = 12;
                 else
                     fallo();
        break;
                 //OPERADOR DE ASIGNACION
        case 12: caracter = leerCar(cadena);
                 estadoActual = 13;
        break;
        case 13: retrocederCar();
                 *resultado += "OPERADOR DE ASIGNACION\n";
                 inicializaEstados();
                 inicioToken = i;
        break;
        case 14: caracter = leerCar(cadena);
                 if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '%')
                     estadoActual = 15;
                 else
                     fallo();
        break;
        case 15: caracter = leerCar(cadena);
                 estadoActual = 16;
        break;
        case 16: retrocederCar();
                 *resultado += "OPERADOR ARITMETICO\n";
                 inicializaEstados();
                 inicioToken = i;
        break;
        case 17:
            if(caracter==';')
            {
                *resultado += "$ FIN\n";
                i++;
                estadoActual=19;
                             }
            break;
        }
    }
}
char AnalizadorLexico::leerCar(string car)
{
  char carActual;
  carActual=car.at(i);
  i++;
  return carActual;
}

void AnalizadorLexico::retrocederCar()
{
   i--;
}

void AnalizadorLexico::inicializaEstados()
{
    estadoInicial = estadoActual = 0;
}

void AnalizadorLexico::fallo()
{
    switch (estadoInicial) {
            case 0: estadoInicial = 3; i = inicioToken; break;
            case 3: estadoInicial = 6; i = inicioToken; break;
            case 6: estadoInicial = 11;i = inicioToken; break;
            case 11: estadoInicial = 14; i = inicioToken; break;
            case 14: estadoInicial = 17; i = inicioToken; break;
            case 17: estadoInicial = 18; i= inicioToken;break;
    }
    estadoActual = estadoInicial;
}




bool AnalizadorLexico::estadoAceptacion()
{
    switch(estadoActual){
            case 2:
            case 5:
            case 8:
            case 10:
            case 13:
            case 16:
            case 17:
            case 18:
            return true;
            default: return false;
        }
}

bool AnalizadorLexico::esDelimitador(char c)
{
    return c == '\n' || c == '\t' || c == ' ';
}

bool AnalizadorLexico::esLetra(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool AnalizadorLexico::esDigito(char c)
{
    return c >= '0' && c <= '9';
}

bool AnalizadorLexico::esReservada(string cadena)
{
    int i = 0;
    while(i <= (int)sizeof(palabras)){
        if(cadena == palabras[i]){
            return true;
        }
         i++;
        }

    return false;
}





void AnalizadorLexico::getTokens(string *STokens){

    for(int i = 0;i<this->i;i++ )
    {
        STokens[i]=Tokens[i];
    }

}
