#ifndef SINTACTICO_H
#define SINTACTICO_H

#include <string>

using namespace std;

class Sintactico
{
public:
    Sintactico();
    int buscaTabla(string a, string x);
    int estoken(string x);
    void analizar();
};

#endif // SINTACTICO_H
