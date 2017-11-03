#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_cliente.h"

int main ()
{
	//ip defecto "127.0.0.1"
	char buffer[1024];
	const char*ip="127.0.0.1";
	Cliente segundo(ip);
	segundo.inicializar();
	segundo.confir();
	segundo.loop();
	segundo.finall();
	return 0;
}
