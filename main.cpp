//#include "dialog.h"
//#include <QApplication>

#include <iostream>
#include <string.h>

//CLASES
#include "analizadorlexico.h"
#include "sintactico.h"
#include "archivos.h"
#include <fstream>
using namespace std;

int main(){
    int numBytesArchivo;
    Archivos archivo;
    AnalizadorLexico anlex;
    Sintactico sintac;
    /*QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();*/

    char resp;
    do
    {
        puts("Desea Generar el Archivo (s/n) : ");

        resp = cin.get();
        //cin.get();  //USAR CUANDO SE REQUIERA ELIMINAR EL ENTER

        if(strchr("S/s",resp))
            archivo.generarArchivo();
        archivo.abrirArchivo();
        numBytesArchivo = archivo.bytesArchivo();
        if(numBytesArchivo==0)
        {
            printf("El archivo NO Tiene Datos. Pulse una tecla");
            if(cin.get() == 0) //  getch()==0)
            { cin.get();//getch();
                exit(-1);
            }
        }
        //fclose(Fd);

        else
            anlex.scanner();

        archivo.cerrarArchivo();

        printf("Salida del Analizador Lexico (asTokens)");
        anlex.mostrar();
        printf("Pulse una tecla para continuar");

        if(cin.get() == 0) //getch()==0)
            cin.get();     //getch();
        sintac.analizar();
        cin.get();

        printf("Presiona (sS) para continuar ? : " );
        cin>>resp;
        cin.get();
    }while (strchr("Ss",resp));

    return 0;
}
