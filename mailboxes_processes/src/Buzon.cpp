#include "Buzon.hpp"

// Constructor de la clase.
Buzon::Buzon()
{
    // Crear el Buzón con msgget
    // 0666 es permisos de lectura y escritura para usuario, grupo y otros
    this->id = msgget((key_t) KEY, 0666 | IPC_CREAT);
    if (this->id == -1) {
        handle_error("buzon no creado");
    }
}

Buzon::~Buzon()
{
    this->destructor();
}

// Método encargado de eliminar el buzón.
void Buzon::destructor()
{
    struct msqid_ds str;
    // Eliminar el buzón con msgctl
    msgctl(this->id, IPC_RMID, 0);
}

// Método encargado de enviar un mensaje al buzón.
void Buzon::enviar(const char* mensaje)
{
    // Inicializar el contenido del mensaje con msgbuf
    struct msgbuf message;
    message.mtype = 1; 
    strcpy(message.mtext, mensaje);

    // Enviar el mensaje con msgsnd
    if (msgsnd(this->id, (void *) &message, MSGMAX, IPC_NOWAIT) == -1) {
        handle_error("mensaje no enviado");
    }
}

// Método encargado de recibir un mensaje.
void Buzon::recibir(char* mensaje)
{
    // Inicializar el contenido del mensaje con msgbuf
    struct msgbuf message;
    message.mtype = 1; 

    // Recibir el mensaje con msgrcv
    msgrcv(this->id, (void *) &message, MSGMAX, 0, 0);

    // Sacar el mensaje del buzón. Sugerencia: strcpy
    strcpy(mensaje, message.mtext);
}
