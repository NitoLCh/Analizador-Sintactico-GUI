#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <fstream>

class Archivos
{
public:
    Archivos();
        void generarArchivo(FILE *Fd);
        void abrirArchivo(FILE *Fd);
        int bytesArchivo(FILE *Fd);
};

#endif // ARCHIVOS_H
