#include "analizadorlexico.h"
//Commented by Water :3
Pila asTokens;
string reservada="";
//Un constructor solito solitario..... o es un metodo vacio? ¯\_(ツ)_/¯
AnalizadorLexico::AnalizadorLexico()
{
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo scanner, recibe una cadena de la cual se analiza caracter por caracter
Pila AnalizadorLexico::scanner()
{
    string cadena=""; //se inicializa una cadena vacia
    string *resultado;

    char caracter;  //Variable caracter donde se guarda el caracter que se lee
    inicializaEstados();    //se inicializan los estados a 0
    i = inicioToken = 0;    // iniciotoken e i se inicializan en 0

    //Se permanece en el ciclo while si i es menor a la longitud de la cadena o estado de aceptacion es true
    while(i < (int)cadena.length() || estadoAceptacion()){
        //Con el switch nos movemos entre los casos dependiendo del valor del estadoActual
        switch (estadoActual) {
        //--------------------------- Casos para delimitadores ----------------------------------//
        case 0: caracter = leerCar(cadena);
            //si es delimitador entra al if y cambia el estado actual, de lo contrario va a fallo()
            if(esDelimitador(caracter))
                estadoActual = 1;
            else
                fallo();
            break;
        case 1: caracter = leerCar(cadena);
            //si es delimitador entra al if y se queda en el mismo estado actual, de lo contrario pasa al estado actual 2
            if(esDelimitador(caracter))
                estadoActual = 1;
            else
                estadoActual = 2;
            break;
            //Se llama al metodo retrocederCar
        case 2: retrocederCar();
            //a la variable resultado se le concatena "delimitador" y un salto de linea
            *resultado += "DELIMITADOR\n";
            //se vuelven a inicializar los estados
            inicializaEstados();
            //y establecemos iniciotoken en la posicion de i
            inicioToken = i;
            break;
        case 3: caracter = leerCar(cadena);
            //si el caracter es letra o "_" entonces entra al if, de lo contrario se va a fallo()
            if(esLetra(caracter) || caracter == '_'){
                //a la variable reservada se guardan y concatenan el caracter que es letra
                reservada += caracter;
                estadoActual = 4;
            }
            else{
                //si no solo establece que resrvada es cadena vacias
                reservada = "";
                fallo();
            }
            break;
        case 4: caracter = leerCar(cadena);
            //si el caracter es letra o es digito o es "_" entonces se queda en el mismo estado, de lo contrario se va al
            //siguiente estado estadoActual=5
            if(esLetra(caracter) || esDigito(caracter) || caracter == '_')
            {
                //a la variable reservada se guardan y concatenan el caracter que es letra
                reservada += caracter;
                //se queda en el mismo estado mientras el if de arriba se cumpla
                estadoActual = 4;
            }
            else
                estadoActual = 5;
            break;
            //se llama al metodo retrocederCar()
        case 5: retrocederCar();
            //llama al metodo esReservada, donde recibe la variable reservada
            if(esReservada(reservada)) //si es reservada entra al if, de lo contrario va al else
            {
                //en la variable resultado se guarda y concatena "palabra reservada" y un salto de linea
                *resultado += reservada;
                asTokens.insertapila(reservada);
                //se inicializan los estados
                inicializaEstados();
                //y establecemos iniciotoken en la posicion i
                inicioToken = i;
            } else {
                //en la variable resultado se guarda y concatena "identificador" y un salto de linea
                *resultado += "IDENTIFICADOR\n";
                asTokens.insertapila("ID");
                //se inicializan los estados
                inicializaEstados();
                //y establecemos iniciotoken en la posicion i
                inicioToken = i;
            }
            break;
            //---------------------------- Casos para Numeros ---------------------------------------//
        case 6: caracter = leerCar(cadena);
            //si es digito entra en el if, de lo contrario se va a fallo()
            if(esDigito(caracter))
                estadoActual = 7;
            else
                fallo();
            break;
        case 7: caracter = leerCar(cadena);
            //si es digito entra al if y permanece en el mismo estado
            if(esDigito(caracter))
                estadoActual = 7;
            //si en el mismo estado se encuentra antes o despues un "." entonces va al estado 9
            else if(caracter == '.')
                estadoActual = 9;
            else //si no es digito y no recibe "." entonces solo va al estado 8
                estadoActual = 8;
            break;
            //se llama al metodo retrocederCar();
        case 8: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "NUMERO ENTERO\n";
            asTokens.insertapila("NUM");
            //se inicializan los estados
            inicializaEstados();
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 9: caracter = leerCar(cadena);
            //si es digito entonces va al estado 9, de lo contrario va al estado 10
            if(esDigito(caracter))
                estadoActual = 9;
            else
                estadoActual = 10;
            break;
            //se llama al metodo retrocederCar();
        case 10: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "NUMERO REAL\n";
            //se inicializan los estados
            inicializaEstados();
            asTokens.insertapila("NUM");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 11: caracter = leerCar(cadena);
            //si caracter es igual a "=" entonces pasa al estado 12, de lo contrario pasa a fallo()
            if(caracter == '=')
            {
                estadoActual = 12;
                *resultado+="= \n";
                asTokens.insertapila("=");
            }
            else
                fallo();
            break;
            //----------------------------------- Operadores ----------------------------------------//
            //se lee el caracter y va al estado 13..... en realidad no se para que es este caso, solo pasa al caso siguiente
        case 12: caracter = leerCar(cadena);
            estadoActual = 13;
            break;
            //se llama al metodo retrocederCar();
        case 13: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "OPERADOR DE ASIGNACION\n";
            //se inicializan los estados
            inicializaEstados();
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 14: caracter = leerCar(cadena);
            //si el caracter leído es alguno de los operadores aritmeticos (+,-,*,/,%)
            //entonces va al estado 15, de lo contrario va a fallo()
            if(caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '%')
                estadoActual = 15;
            else
                fallo();
            break;
            //se vuelve a leer el caracter, y va al estado 16..... no se porque esta un caso de mas, pero bueno va al caso siguiente
        case 15: caracter = leerCar(cadena);
            estadoActual = 16;
            break;
            //se llama a retrocederCar();
        case 16: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            operador(caracter,*resultado);
            *resultado += "OPERADOR ARITMETICO\n";
            operador(caracter,*resultado);operador(caracter,*resultado);
            //se inicializan los estados
            inicializaEstados();
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 17: caracter = leerCar(cadena);
            //se compara si el caracter que se lee es igual a parentesis izq.
            if(caracter == '(')
                estadoActual = 18;
            else
                fallo();
            break;
            //se llama a retrocederCar();
        case 18: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "PARANTESIS I\n";
            //se inicializan los estados
            inicializaEstados();
            //inserta en pila el parentesis izquierdo como token
            asTokens.insertapila("(");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 19: caracter = leerCar(cadena);
            //si el caracter que se lee es igual a parentesis derecho, entra en el if
            if(caracter ==')')
                estadoActual = 20;
            else
                fallo();
            break;
            //Se llama a retrocederCar();
        case 20: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "PARANTESIS D\n";
            //se inicializan los estados
            inicializaEstados();
            //insertamos en la pila el parentesis derecho como token
            asTokens.insertapila(")");  //asTokens.insertapila("("); <-- Alguien se equivoco aca, puso parentesis izq en vez de derecho
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 21: caracter = leerCar(cadena);
            //Se compara si el caracter que se lee es igual a llave de apertura
            if(caracter =='{')
                estadoActual = 22;
            else
                fallo();
            break;
            //Se llama a retrocederCar();
        case 22: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "LLAVE I\n";
            //se inicializan los estados
            inicializaEstados();
            //se inserta en pila la llave de apertura
            asTokens.insertapila("{");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 23: caracter = leerCar(cadena);
            //se compara si el caracter que se toma es igual a llave de cerradura, sino entonces va a fallo
            if(caracter =='}')
                estadoActual = 24;
            else
                fallo();
            break;
            //Se llama a retrocederCar();
        case 24: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "LLAVE D\n";
            //se inicializan los estados
            inicializaEstados();
            //Se inserta en pila la llave de cerradura
            asTokens.insertapila("}");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 25: caracter = leerCar(cadena);
            //Aqui se compara para ver si el caracter que lee es igual a corchete izquierdo, de lo contrario va a fallo
            if(caracter =='[')
                estadoActual = 26;
            else
                fallo();
            break;
            //Se llama a retrocederCar();
        case 26: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "CORCHETE I \n";
            //se inicializan los estados
            inicializaEstados();
            //se inserta en pila el corchete izquierdo
            asTokens.insertapila("[");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
        case 27: caracter = leerCar(cadena);
            //Aqui se compara para ver si caracter es igual a corchete derecho
            if(caracter ==']')
                estadoActual = 28;
            else
                fallo();
            break;
            //Se llama a retrocederCar();
        case 28: retrocederCar();
            //en la variable resultado se guarda y concatena "numero entero" y un salto de linea
            *resultado += "CORCHETE D \n";
            //se inicializan los estados
            inicializaEstados();
            //se inserta en la pila como token a corchete derecho
            asTokens.insertapila("]");
            //y se establece iniciotoken en la posicion i
            inicioToken = i;
            break;
            //------------------------------- Fin de los casos -----------------------------------//
        case 29:
            //Aqui se comprueba si caracter es ";", con esto podemos verificar si ya termino la sentencia
            if(caracter==';')
            {
                //en la variable resultado se guarda y concatena "Fin" y un salto de linea
                *resultado += "$ FIN\n";
                //se incrementa i para salir del while
                i++;
                asTokens.insertapila("$");
                //y establecemos estadoActual = 30, igual para no mantener el while
                estadoActual=30;
            }
            break;
        }
    }
    setResultado(resultado);
    setCadena(cadena);
    return asTokens;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para leer el caracter (se necesita para cada caso)
char AnalizadorLexico::leerCar(string car)
{
    //variable para guardar el caracter actual de la cadena
    char carActual;
    //toma la posicion del caracter
    carActual=car.at(i);
    //se incrementa i
    i++;
    //y se retorna carActual
    return carActual;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para retroceder un caracter en la cadena
void AnalizadorLexico::retrocederCar()
{
    //Solo se decrementa la i para regresar un caracter en la cadena
    i--;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo parar inicializar los estados inicial y actual
void AnalizadorLexico::inicializaEstados()
{
    estadoInicial = estadoActual = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para saltar de un caso a otro caso (por ejemplo si no es delimitador pasa comprobar si es numero)
void AnalizadorLexico::fallo()
{
    //toma el estado inicial para moverse en el switch con los casos
    switch (estadoInicial) {
    case 0: estadoInicial = 3; i = inicioToken; break;
    case 3: estadoInicial = 6; i = inicioToken; break;
    case 6: estadoInicial = 11;i = inicioToken; break;
    case 11: estadoInicial = 14; i = inicioToken; break;
    case 14: estadoInicial = 17; i = inicioToken; break;
    case 17: estadoInicial = 18; i= inicioToken;break;
    case 19: estadoInicial = 20; i = inicioToken; break;
    case 21: estadoInicial = 22; i= inicioToken;break;
    case 23: estadoInicial = 24; i= inicioToken;break;
    case 25: estadoInicial = 26; i = inicioToken; break;
    case 26: estadoInicial = 28; i= inicioToken;break;
    }
    //guarda el valor de estado inicial en la variable estado actual
    estadoActual = estadoInicial;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para cuando se llegue a un estado de aceptacion
bool AnalizadorLexico::estadoAceptacion()
{
    //toma el estado actual y define si entra en estado de aceptacion, de ser asi regresa un true, de lo contrario (Default) regresa un false
    switch(estadoActual){
    //Todos estos cases son casos de aceptacion
    case 2:
    case 5:
    case 8:
    case 10:
    case 13:
    case 16:
    case 17:
    case 18:
    case 20:
    case 22:
    case 24:
    case 26:
    case 28:
        return true;
        //por defecto regresa un false, tiene que entrar si o si en uno de los casos
    default: return false;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para analizar si es delimitador o no el caracter que recibe
bool AnalizadorLexico::esDelimitador(char c)
{
    //retorna c solo si es igual a un salto de linea, a una tabulacion o a un espacio vacio
    return c == '\n' || c == '\t' || c == ' ';
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para analizar si es letra o no el caracter que recibe
bool AnalizadorLexico::esLetra(char c)
{
    //retorna c solo si c se encuentra en el rango de letras mayusculas o minusculas (se puede usar tambien el ASCII)
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para analizar si es digito o no el caracter que se recibe
bool AnalizadorLexico::esDigito(char c)
{
    //retorna c solo si se encuentra en el rango de numeros (del 0 al 9, tambien se puede usar ASCII...... pero la neta es mas facil
    //con los numeros normales xD)
    return c >= '0' && c <= '9';
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para analizar si es palabra reservada o no el caracter que se recibe
bool AnalizadorLexico::esReservada(string cadena)
{
    string res;
    int i = 0; //Variable int donde se inicializa en 0
    //ciclo while donde i debe ser menor o igual al tamaño de palabras
    while(i <= (int)sizeof(palabras)){
        //si la la cadena que recibe coincide con la posicion de la palabra entonces entra en el if
        if(cadena == palabras[i]){
            return true;
        }
        //Luego se incrementa i para movernos en el array palabras
        i++;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo que recibe el caracter a analizar y le asigna un valor a la variable res (en caso de aplicar)
void AnalizadorLexico::operador(char car,string res)
{
    switch(car) //Con el caracter que se recibe se va moviendo por los casos del switch, en caso de cumplir alguno entonces entra
        //en el switch y le da un un valor a la variable res, concatenandole el valor anterior de res
    {
    case '+':
        asTokens.insertapila("+");
        res+="+ \n";
        break;
    case '-':
        asTokens.insertapila("-");
        res+="- \n";
        break;
    case '/':
        asTokens.insertapila("/");
        res+="/ \n";
        break;
    case '*':
        asTokens.insertapila("*");
        res+="* \n";
        break;
    case '%':
        asTokens.insertapila("%");
        res+="% \n";
        break;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para establecer la variable cadena de esta clase con la variable cadena global
void AnalizadorLexico::setCadena(string cadena){
    this->cadena = cadena;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para obtener y retornar la cadena de esta clase
string AnalizadorLexico::getCadena(){
    return this->cadena;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para estblecer la variable resultado de esta clase con la variable resultado global
void AnalizadorLexico::setResultado(string *resultado){
    this->resultado = resultado;
}

//-------------------------------------------------------------------------------------------------------------------------------//

//Metodo para obtener y retornar el resultado de esta clase
string *AnalizadorLexico::getResultado(){
    return this->resultado;
}

//-------------------------------------------------------------------------------------------------------------------------------//

void AnalizadorLexico::mostrar(){

    puts("\nTOKENS RECONOCIDOS : ");
    Pila copia = scanner();
    while(!copia.stck->empty())  //,Ren++)
    {
        puts(copia.tope().c_str());
        puts("\n");
        copia.eliminapila();
    }
}

//-------------------------------------------------------------------------------------------------------------------------------//
