#include "AdminMmap.hpp"

// incluir ruta relativa del archivo si se cambia
AdminMmap::AdminMmap(char * nombreArchivo){
    this->nombreArchivo = nombreArchivo;
}

void AdminMmap::montarZonaCompartida(){
    // abre el archivo
    this->fileDescriptor = open(this->nombreArchivo, O_RDONLY);\
    if (this->fileDescriptor == -1)
        handle_error("no se pudo abrir el archivo");

    if (fstat(this->fileDescriptor, &this->buffer) == -1)
        handle_error("no se pudo cargar el archivo en buffer");

    // se crea la direccion en memoria compartida con mmap
    this->direccion = (char*) mmap(NULL, buffer.st_size, PROT_READ, MAP_SHARED, fileDescriptor, 0);

    if (direccion == MAP_FAILED)
        handle_error("no se pudo crear la memoria compartida");
}

void AdminMmap::desmontarZonaCompartida(){
    munmap(direccion, buffer.st_size);
    close(fileDescriptor);
    cout << "La zona compartida ha sido desmontada" << endl;
}

off_t AdminMmap::getFileSize() {
    return this->buffer.st_size;
}

char * AdminMmap::getDireccion() {
    return this->direccion;
}
