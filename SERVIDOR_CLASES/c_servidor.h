
#ifndef C_SERVIDOR_H
#define C_SERVIDOR_H
using namespace std;

class servidor
{	
	
	public:
	/*INICIALIZACION DE VARIABLES*/
		int client, server;
		int portNum ;// Este puerto lo utilizaremos par el cliente y servidor
		bool isExit ;//variable para saber si la conversacion termino
		int bufsize;//TAmaño de los datos de entrada
	/*CREACION DEL CONSTRUCTOR */	
		servidor(int =1500,bool =false,int =1024);
	/*CREACION DE DATOS DESPUES DEL CONSTRUCTOR*/		
		char buffer[1024];//Guardamos como datos de entrada
		struct sockaddr_in server_addr;//estructura que almacenara los datos para poder comunicarnos 
    	socklen_t size;

	/*INICIALIZAMOS A CIENTE CON LOS DATOS DE SU SOCKET*/	
   		void construir_cliente();	
		void construir_structura();
		int vinculo();
		void espera_cliente();
		void aceptar();
		void inicio( char*buffer);
		void chat(char*buffer);
		void todo(char*buffer);
};
#endif
