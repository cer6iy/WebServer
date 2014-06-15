/*
В классе Server реализуется создание сокета и организуется его прослушиваение на определенном порту.
*/

#pragma once

#include "stdafx.h"
#include <winsock2.h>
#include <string>

using namespace std;

#define PORT 1111
#define REQUEST_SIZE 1024

class Server
{
private:	
	WORD sockVer;
	WSADATA wsaData;	
	SOCKET clientSock;
	int retVal;
	SOCKET servSock;
	string req;
	char* folder;
	int port;
	char* responce;
	void getFileContent(string);
	void sendResponce();
	void init();
	void closeClient();
	string parse();

public:
	Server(char* pathToFolder = "", int userPort = PORT);
	~Server();
	void waitClient();
	void processRequest();

/*
Классы исключений. Обрабатываются ошибки подключения и создания сокета.
*/
	class SocketErrorExeption { };
	class SocketListenErrorExeption: public SocketErrorExeption  { };
	class SocketCreateErrorExeption: public SocketErrorExeption { };
	class BindErrorExeption: public SocketErrorExeption  { };
	class ClientExeption { };
	class ClientAcceptExeption: public ClientExeption { };
	class ClientReceiptExeption: public ClientExeption { };
	class ClientSendExeption: public ClientExeption { };

};

