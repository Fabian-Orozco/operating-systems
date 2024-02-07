#ifndef ADMINPROCESOS_H
#define ADMINPROCESOS_H

#include <string>
#include "Buzon.hpp"
#include "AdminMmap.hpp"
#include "sys/wait.h"

#include <iostream>
using namespace std;

class AdminProcesos {

  private:
    int indices[3] = {0,0,0};
    Buzon buzon;
    AdminMmap archivo;

  public:
    void run();
    void ejecutarHijos(int inicio, int final, char * archivo, Buzon & buzon);
    void distribuirCarga(int fileSize);
    void imprimirResultados(int caracteres, int lineas);
    void contarCaracteres(int inicio, int final, char * archivo, int * resultado);
    void enviarResultados(int * resultado, Buzon & buzon);
};
#endif // ADMINPROCESOS_H
