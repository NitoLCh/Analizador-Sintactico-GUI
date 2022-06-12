#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <fstream>
#include <QtGui>
using namespace std;

class Archivos
{
public:
    fstream Fd;
    Archivos();
        void generarArchivo();
        void abrirArchivo();
        int bytesArchivo();
        void cerrarArchivo();
};

#endif // ARCHIVOS_H
