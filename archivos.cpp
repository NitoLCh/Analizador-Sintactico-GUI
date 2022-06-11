#include "archivos.h"
#include <iostream>
#include "string"
#include "stdlib.h"
#include "stdio.h"
//Commented by Water :p
using namespace std;

Archivos::Archivos(){

}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para generar el archivo, donde se recibe el identificador de X archivo
void Archivos::generarArchivo(fstream *Fd){
    char caracter;// Variable caracter para guardar un char
    char buffer[100]; // buffer array para guardar simplemente info
    string nombre;

    //Se puede usar tambien puts("Nombre del Archivo a GENERAR (sin extension): "); pero puts ya esta fuera de onda y es de C
    //usamos printf
    printf("Nombre del Archivo a GENERAR (sin extension): ");
    //gets(Nombre); //<--- ERROR CON ESTE METODO
    //usar gets ya no es recomendado ya que esta funcion no reconoce si quiera el tamaño de la cadena que se la va a pasar
    //gets solo lee los datos de entrada hasta el final, ocasionado problemas en caso de tener un array declarado con cierto tamaño
    //e ingresamos mas caracteres de los que se puede almacenar en dicho array.... esta fuera de onda igual que puts jejej

    cin>>nombre; // Se usa un cinpara tomar y almacenar el nombre del archivo, sip, cin (ง •̀_•́)ง

    //La funcion sprintf la usamos para escribir en la salida que se genera
    //En este caso al nombre del archivo se le concatena el tipo de formato que sera el archivo, el cual es .dat (espero no equivocarme, no me mates jorge D:)
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
    //variable aux donde se guardara y retornara el tamaño en bytes
    int aux;
    //fseek(Fd,0L,SEEK_END);
    Fd->seekg(1, std::ios::end);
    //aux = (int) ftell(Fd);
    aux = Fd->tellg();
    //fseek(Fd,0L,SEEK_SET);
    Fd->seekg(1,std::ios::beg);
    return aux;
}


