#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "c_cliente.h"
using namespace std;
	/*CREACION DEL CONSTRUCTOR */	
	Cliente::Cliente(const char*ip,int portNum,bool isExit ,int bufsize )
	  	:ip(ip),portNum(portNum),isExit(isExit),bufsize(bufsize){}
	void Cliente::inicializar()
	{

		 client= socket(AF_INET, SOCK_STREAM, 0);
		
		if (client < 0) 
		{
		    cout << "\n Error estableciendo el socket..." << endl;
		    exit(1);
		}
		cout << "\n=> El socket del cliente ha sido creado" << endl;
		
	 }
	/*INICIALIZAMOS A CIENTE CON LOS DATOS DE SU SOCKET*/	 
	void Cliente::confir()
	{
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(portNum);
			inet_pton(AF_INET, ip, &server_addr.sin_addr);

		if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
		    cout << "=> Coneccion con el servidor... " << inet_ntoa(server_addr.sin_addr) << " with port number: " << portNum << endl;
		cout << "=> Esperando confirmacion del servidor" << endl; //line 40
		recv(client, buffer, bufsize, 0);
		cout << "=> Coneccion confirmada eres libre de seguir...";

		cout << "\n\n=> Introduce # para terminar conexion\n" << endl;
    }
   /*CONSTRUIMOS LA ESTRUCTURA QUE ALMACENARA LOS DATOS DE NUESTRO SOCKET*/ 
	void Cliente::loop()
	{
		bool isExit;
		do {
			cout << "Cliente: ";
			do {
				cin >> buffer;
				send(client, buffer, bufsize, 0);
				if (*buffer == '#') {
					send(client, buffer, bufsize, 0);
					*buffer = '*';
					isExit = true;
				}
			} while (*buffer != 42);

			cout << "Servidor: ";
			do {
				recv(client, buffer, bufsize, 0);
				cout << buffer << " ";
				if (*buffer == '#') {
					*buffer = '*';
					isExit = true;
				}

			} while (*buffer != 42);
			cout << endl;

		} while (!isExit);
	}
	void Cliente::finall()
	{
		cout << "\n=> Connection terminated.\nGoodbye...\n";

		close(client);
	}
