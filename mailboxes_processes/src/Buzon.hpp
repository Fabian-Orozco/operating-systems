#ifndef BUZON_HPP
#define BUZON_HPP

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Constante que almacena el de carné.
#define KEY 0xB95690

// Tamaño máximo del mensaje en bytes.
#define MSGMAX 128

// Se encarga de imprimir los errores de la misma manera.
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

// Clase encargada de compartir mensajes entre procesos.
class Buzon{
public:
   Buzon();
   void destructor();
   void enviar(const char* mensaje);
   void recibir(char* mensaje);
   ~Buzon();

protected:
   int id;
	
   // Estructura que almacena el contenido de los mensajes.   
   struct msgbuf{
      // Basado en: https://tldp.org/LDP/lpg/node30.html
      long mtype; // Tipo del mensaje, representado por un número positivo.
      char mtext[MSGMAX];  // Contenido del mensaje como tal.
   };
};

#endif // BUZON_HPP
