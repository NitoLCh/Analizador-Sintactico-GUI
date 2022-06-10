#include "archivos.h"
#include <iostream>
#include "string"
#include "stdlib.h"
#include "stdio.h"
using namespace std;

Archivos::Archivos()
{

}

<<<<<<< HEAD
void Archivos::generarArchivo(FILE *Fd)
{
    char car;
    char nomArch[100];

    // char *nombre = new char[100];
    //cin.getline(nombre,100,'\n');

    string nombre;
    printf("Nombre del Archivo a GENERAR (sin extension): ");
                    //gets(Nombre);  //<--- ERROR CON ESTE METODO
    cin>>nombre;

          // cin.get();    //ELIMINAR ENTER


    sprintf(nomArch,"%s.dat",nombre.c_str());
    Fd = fopen(nomArch,"w+b");
    if(Fd == NULL)
    {
        cout<<"NO SE PUEDE ABRIR EL ARCHIVO : "<<nomArch;
        exit(-1);
    }
    puts("teclea el archivo : ");
            //cin.get();  //eliminar el enter
   // printf("Tecela <ESC> -USAR UNICODE DEL ESC -para terminar el archivo \n");

    printf("Tecela @ para terminar el archivo \n");

    //LA INFO ESTA EN EL BUFFERs
    do
    {
        car = cin.get();
        //cin>>car;
        if( car == '\n')  //13)
        {
            car = '\n';
            printf("\n");
        }
        if(car == 0)  //NULL
            car = cin.get();
        if(car != '@')        //27 && car != 8)
            fwrite(&car,sizeof(car),1,Fd);

    }while(car != '@');

    fclose(Fd);

}

void Archivos::abrirArchivo(FILE *Fd)
{
    char nomArch[100];
    //char nombre[100];
    char *nombre = new char[100];

    printf("\n\n Nombre del Archivo a ABRIR(sin extension): ");
        //gets(nombre);
    //cin>>nombre;
    cin.get();  //ELIMINAR EL ENTER
    cin.getline(nombre,100,'\n');

    //sprintf(nomArch,"/Users/martinos/Desktop/appASintactico_XCode/%s.dat",nombre);  //,'\0');
    sprintf(nomArch,"%s.dat",nombre);  //,'\0');


    Fd = fopen(nomArch,"r+b");

    if(Fd==NULL)
    {
        printf("NO SE PUEDE ABRIR EL ARCHIVO");
        exit(-1);    //cin.get();

    }
    else
    {
        printf("EL ARCHIVO SE ENCUENTRA ABIERTO \n");

    }
=======

void Archivos::generararch(FILE *Fd){

}

void Archivos::vabrirarch(FILE *Fd){


>>>>>>> cambios de la clase archivo
}

int Archivos::byteArchivo(FILE *Fd)
{
    int aux;
    fseek(Fd,0L,SEEK_END);
    aux = (int) ftell(Fd);
    fseek(Fd,0L,SEEK_SET);
    return aux;
}


