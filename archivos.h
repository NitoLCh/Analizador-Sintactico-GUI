#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <fstream>

class Archivos
{
public:
    Archivos();
        void generararch(FILE *Fd);
        void vabrirarch(FILE *Fd);
        int bytesarch(FILE *Fd);
};

#endif // ARCHIVOS_H
