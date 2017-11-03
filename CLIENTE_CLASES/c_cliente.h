
#ifndef C_CLIENTE_H
#define C_CLIENTE_H

using namespace std;
class Cliente
{
  public:
	  int portNum;
	  int client;
	  int bufsize;
	  char* buffer;
	  bool isExit;
	  const char* ip;
	  struct sockaddr_in server_addr;
	  Cliente(const char*ip,int =1500,bool =false,int =1024);
	  void inicializar();
	  void confir();
	  void loop();
	  void finall();
	  
};

#endif
