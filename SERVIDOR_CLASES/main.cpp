#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_servidor.h"

int main ()
{
	char buffer[1024];
	//servidor(int portNum,bool isExit,int bufsize)
	servidor primero;
	primero.construir_cliente();
	primero.construir_structura();
	primero.vinculo();
	primero.espera_cliente();
	primero.aceptar();
	primero.todo(buffer);

	return 0;
}
