#include "archivos.h"
#include <iostream>
#include "string"
#include "stdlib.h"
#include "stdio.h"
using namespace std;

Archivos::Archivos(){

}

void Archivos::generarArchivo(fstream *Fd){
    char caracter;
    char buffer[100];

    string nombre;
    printf("Nombre del Archivo a GENERAR (sin extension): ");
                    //gets(Nombre);  //<--- ERROR CON ESTE METODO
    cin>>nombre;

    sprintf(buffer,"%s.dat",nombre.c_str());
    Fd->open(nombre, fstream::binary|fstream::out|fstream::in|fstream::trunc);
    if(Fd == NULL){
        cout<<"NO SE PUEDE ABRIR EL ARCHIVO : "<<nombre;
        exit(-1);
    }
    puts("teclea el archivo : ");         
    printf("Tecela @ para terminar el archivo \n");

    //LA INFO ESTA EN EL BUFFERs
    do{
        caracter = cin.get();
        //cin>>car;
        if(caracter == '\n'){
            caracter = '\n';
            printf("\n");
        }
        if(caracter == 0)  //NULL
            caracter = cin.get();
        if(caracter != '@')        //27 && car != 8)
            Fd->write(&caracter,sizeof(caracter));

    }while(caracter != '@');

    Fd->close();

}

void Archivos::abrirArchivo(fstream *Fd)
{
    char buffer[100];
    //char nombre[100];
    string nombre = "";

    printf("\n\n Nombre del Archivo a ABRIR(sin extension): ");
        //gets(nombre);
    cin>>nombre;
    //cin.get();  //ELIMINAR EL ENTER
    //cin.getline(nombre,100,'\n');


    sprintf(buffer,"%s.dat", nombre.c_str());  //,'\0');
    Fd->open(nombre, fstream::binary|fstream::out|fstream::in|fstream::trunc);

    if(Fd==NULL){
        printf("NO SE PUEDE ABRIR EL ARCHIVO");
        exit(-1);    //cin.get();

    }
    else{
        printf("EL ARCHIVO SE ENCUENTRA ABIERTO \n");

    }
}

int Archivos::bytesArchivo(fstream *Fd){
    int aux;
    //fseek(Fd,0L,SEEK_END);
    Fd->seekg(1, std::ios::end);
    //aux = (int) ftell(Fd);
    aux = Fd->tellg();
    //fseek(Fd,0L,SEEK_SET);
    Fd->seekg(1,std::ios::beg);
    return aux;
}


