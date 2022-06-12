#include "archivos.h"
#include <iostream>
#include "string"

//Commented by Water :p
using namespace std;

Archivos::Archivos(){

}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para generar el archivo, donde se recibe el identificador de X archivo
void Archivos::generarArchivo(){
    char caracter;// Variable caracter para guardar un char
    char nombreChar[100]; // buffer array para guardar simplemente info
    string nombre;

    //Se puede usar tambien puts("Nombre del Archivo a GENERAR (sin extension): ");
    //usamos printf
    printf("Nombre del Archivo a GENERAR (sin extension): ");
    //gets(Nombre); //<--- ERROR CON ESTE METODO
    //usar gets ya no es recomendado ya que esta funcion no reconoce si quiera el tamaño de la cadena que se la va a pasar
    //gets solo lee los datos de entrada hasta el final, ocasionado problemas en caso de tener un array declarado con cierto tamaño
    //e ingresamos mas caracteres de los que se puede almacenar en dicho array.... esta fuera de onda igual que puts jejej
    cin>>nombre; // Se usa un cin para tomar y almacenar el nombre del archivo

    //La funcion sprintf la usamos para escribir en la salida que se genera
    //En este caso al nombre del archivo se le concatena el tipo de formato que sera el archivo, el cual es .dat
    sprintf(nombreChar,"%s.dat",nombre.c_str());
    //la funcion open recibe como parametros el nombre del archivo con extension (en este caso nombre.dat) y recibe
    //tambien las banderas del tipo modo de entrada/salida del archivo (in,out,binary,ate,app,trunc)
    std::fstream fd(nombreChar, ios_base::in);
    //Si al abrir el archivo es nulo entonces entra en el if
    if(fd.is_open()){
        cout<<"NO SE PUEDE ABRIR EL ARCHIVO: "<<nombreChar <<endl;
        //Imprime que no hay archivo para abrir y cierra el programa
        exit(-1);
    }
    puts("Teclea el archivo : ");
    printf("Teclea @ para terminar el archivo \n");

    //LA INFO ESTA EN EL BUFFERs
    do{
        //cin.get toma lo que se escribe y lo guarda en la variable caracter
        caracter = cin.get();
        //cin>>car;
        if(caracter == '\n'){
            caracter = '\n';
            printf("\n");
        }
        if(caracter == 0)  //NULL
            caracter = cin.get();
        //Se pide que caracter sea diferente de "@", de esta manera
        if(caracter != '@')        //27 && car != 8)
            //escribe todo lo que guardo en buffer y lo guarda
            fd << caracter;
    //El ciclo se mantiene mientas caracter sea diferente de "@"
    }while(caracter != '@');
    //Se cierra el identificador del archivo
    fd.close();

}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para abrir archivo
void Archivos::abrirArchivo()
{
    char nombreChar[100];   // buffer array para guardar simplemente info
    //char nombre[100];
    string nombre = "";

    //Se pregunta el nombre del archivo a abrir, luego se toma y guarda el nombre el la variable nombre
    printf("\n\n Nombre del Archivo a ABRIR(sin extension): ");
    cin>>nombre;
    //cin.get();  //ELIMINAR EL ENTER
    //cin.getline(nombre,100,'\n');

    //La funcion sprintf la usamos para escribir en la salida que se genera
    //En este caso al nombre del archivo se le concatena el tipo de formato que sera el archivo, el cual es .dat
    sprintf(nombreChar,"%s.dat", nombre.c_str());  //,'\0');
    //se vuelve a usar la funcion open con el identificador Fd
    Fd.open(nombreChar, fstream::binary|fstream::out|fstream::in|fstream::trunc);

    //Si al abrir el archivo es nulo entonces entra en el if
    if(!Fd.is_open()){
        printf("NO SE PUEDE ABRIR EL ARCHIVO");
        //Imprime que no hay archivo para abrir y cierra el programa
        exit(-1);
    }
    else{
        printf("EL ARCHIVO SE ENCUENTRA ABIERTO \n");
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo que retorna el tamaño en bytes del archivo
int Archivos::bytesArchivo(){
    int aux;    //variable aux donde se guardara y retornara el tamaño en bytes
    //fseek(Fd,0L,SEEK_END);
    //funcion seekg sirve para movernos a una posicion que usaremos (toma como parametros la cantidad de espacios a saltar
    //y desde que punto)
    Fd.seekg(1, std::ios::end);
    //aux = (int) ftell(Fd);
    //con tellg() se ve la posicion para ver cual es su tamaño y lo guardamos en la variable aux
    aux = Fd.tellg();
    //fseek(Fd,0L,SEEK_SET);
    Fd.seekg(1,std::ios::beg);
    return aux;
}

void Archivos::cerrarArchivo(){
    Fd.close();
}


