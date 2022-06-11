#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <fstream>
#include <QtGui>
using namespace std;

class Archivos
{
public:
    Archivos();
        void generarArchivo(fstream *Fd);
        void abrirArchivo(fstream *Fd);
        int bytesArchivo(fstream *Fd);
};

#endif // ARCHIVOS_H
