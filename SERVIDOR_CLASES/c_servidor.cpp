#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "c_servidor.h"
using namespace std;

	
/*CREACION DEL CONSTRUCTOR */	
servidor::servidor(int portNum,bool isExit,int bufsize)
	:portNum (portNum),isExit(isExit),bufsize(bufsize){}

/*INICIALIZAMOS A CIENTE CON LOS DATOS DE SU SOCKET*/	
void servidor::construir_cliente()
	{
		client = socket(AF_INET, SOCK_STREAM, 0);
		if (client < 0) 
		{
			cout << "\nError establecer coneccion con socket..." << endl;
			exit(1);
		}
		//verificamso  que la comunicacion haya sido correcta
		cout << "\n=> Socket servidor ha sido creado..." << endl;

	}
/*CONSTRUIMOS LA ESTRUCTURA QUE ALMACENARA LOS DATOS DE NUESTRO SOCKET*/	
void servidor::construir_structura()
	{
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);
		server_addr.sin_port = htons(portNum);
	}

int servidor::vinculo()
	{
		//Establecemos un vinculo entre nuestro servidor y cliente
		if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
		{
			cout << "=> Error al vincular el cinete y servidor..." << endl;
			return -1;
		}

	}

void servidor::espera_cliente()
	{
		size = sizeof(server_addr);
		cout << "=> Buscando clientes..." << endl;
		//Esperamos a que aparesca un cleinte

		listen(client, 1);
		//int clientCount = 1;		
	}

void servidor::aceptar()
	{
		server = accept(client,(struct sockaddr *)&server_addr,&size);
		if (server < 0) 
			cout << "=> Error al aceptar..." << endl;

	}
void servidor::inicio( char*buffer)
	{
		//Cliente inicia la conversacion
		cout << "Cliente: ";
		do {
		    recv(server,buffer,bufsize, 0);
		    cout << buffer << " ";
		    if (*buffer == '#') {
		        *buffer = '*';
		        isExit = true;
		    }
		} while (*buffer != '*');
		//para poder pasar mensajes al final de cada uno tiene que aprarecer '*'

	}
void servidor::chat( char*buffer )
	{
		do {
		    cout << "\nServidor:";
		    do {
		        cin >>buffer;
		        send(server, buffer, bufsize, 0);
		        if (*buffer == '#') {
		            send(server, buffer, bufsize, 0);
		            *buffer = '*';
		            isExit = true;
		        }
		    } while (*buffer != '*');
		//para el recojo del mensaje de cliente hacemos lo mismo
		    cout << "Client: ";
		    do {
		        recv(server, buffer,bufsize, 0);
		        cout << buffer << " ";
		        if (*buffer == '#') {
		            *buffer == '*';
		            isExit = true;
		        }
		    } while (*buffer != '*');
		} while (!isExit);

	}

void servidor::todo(char*buffer)
	{
		while(server > 0) 
		{
			strcpy(buffer, "=> Servidor conectado...\n");
			send(server, buffer, bufsize, 0);
			cout << "=> Connectado con el cliente #" <<"1" << ", listo para empezar..." << endl;
			cout << "\n=> Entrar # para finalizar coneccion\n" << endl;
			inicio(buffer);
			chat(buffer);
			//Terminamos la coneccion con #
			cout << "\n\n=> Coneccion terminada con IP " << inet_ntoa(server_addr.sin_addr);
			close(server);
			cout << "\nAdios..." << endl;
			isExit = false;
			exit(1);
		}

		close(client);
	}

