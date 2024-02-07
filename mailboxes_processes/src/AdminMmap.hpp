#ifndef ADMINMMAP_HPP
#define ADMINMMAP_HPP

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
using namespace std;

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

class AdminMmap {

  public:
    AdminMmap(char * nombreArchivo = (char *) "../lorem.txt");
    void montarZonaCompartida();
    void desmontarZonaCompartida();
    char * getDireccion();
    off_t getFileSize();

  private:
    char * nombreArchivo = (char*) "lorem.txt";
    char * direccion = nullptr;
    int fileDescriptor = 0;
    struct stat buffer;
    size_t length = 0;
    off_t offset = 0;
};
#endif // ADMINMMAP_HPP
