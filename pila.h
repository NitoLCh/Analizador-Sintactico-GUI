#ifndef PILA_H
#define PILA_H

#include <string>
#include <stack>

using namespace std;

class Pila
{
public:
    stack <string> *stck;
    Pila();
    void insertapila(string elem);
    void eliminapila();
    string tope();
    stack<string>* copiarPila();
};

#endif // PILA_H
