#include "AdminProcesos.hpp"

void AdminProcesos::run(){
    this->archivo.montarZonaCompartida();
    this->distribuirCarga(this->archivo.getFileSize());

    // Crea 3 procesos y les asigna la carga de trabajo usando los indices como offsets iniciales y finales.
    for (int i = 0; i < 3; ++i) {
        if (fork() == 0) {
            if (i == 0) {
                ejecutarHijos(0, this->indices[0], this->archivo.getDireccion(), this->buzon);
            } else if (i == 1) {
                ejecutarHijos(this->indices[0], this->indices[1], this->archivo.getDireccion(), this->buzon);
            } else {
                ejecutarHijos(this->indices[1], this->indices[2], this->archivo.getDireccion(), this->buzon);
            }
            exit(0);
        }
    }

    int caracteresTotales = 0;
    int lineasTotales = 0;
    char buff[MSGMAX];

    for (int i = 0; i < 3; ++i) {
        wait(NULL);
        this->buzon.recibir(buff);
        string temp(buff);
        caracteresTotales += stoi(temp.substr(0, temp.find(',')));
        lineasTotales += stoi(temp.substr(temp.find(',')+1, string::npos));
    }
    // se suma 1 al las líneas totales por para el caso donde solo hay una línea
    this->imprimirResultados(caracteresTotales, ++lineasTotales);
}

void AdminProcesos::ejecutarHijos(int inicio, int final, char * archivo, Buzon & buzon){
    int resultado[] = {0,0};

    contarCaracteres(inicio, final, archivo, resultado);
    enviarResultados(resultado, buzon);
}

void AdminProcesos::distribuirCarga(int fileSize){
    // Se distribuye la carga dividiendo el tamaño del archivo entre la cantidad de procesos (3).

    int carga = fileSize/3;
    int sobrantes = fileSize % 3;

    this->indices[0] = carga;  // donde termina proceso 1
    this->indices[1] = (carga * 2) + sobrantes;  // donde termina proceso 2
    this->indices[2] = fileSize;  // donde termina proceso 3
}

void AdminProcesos::imprimirResultados(int caracteres, int lineas){
    cout << "El archivo contiene "<< caracteres << " y " << lineas << " lineas" << endl;
}

void AdminProcesos::contarCaracteres(int inicio, int final, char * archivo, int * resultado){
    for (int i = inicio; i < final; ++i) {  // recorre el archivo de acuerdo a su carga
        if (archivo[i] > (char) 32)  // si el caracter no es especial
            ++resultado[0];  // aumenta cantidad de caracteres

        if (archivo[i] == '\n' )
            ++resultado[1];  // aumenta cantidad de líneas
    }
}

void AdminProcesos::enviarResultados(int * resultado, Buzon & buzon) {
    string resultados = to_string(resultado[0]) + "," + to_string(resultado[1]);
    buzon.enviar(resultados.c_str());
}
