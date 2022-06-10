#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>




class Archivos
{
public:
    Archivos();
        void generararch(FILE *Fd);
        void vabrirarch(FILE *Fd);
        int bytesarch(FILE *Fd);
};

#endif // ARCHIVOS_H
