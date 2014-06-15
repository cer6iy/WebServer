
#include "stdafx.h"
#include "server.h"
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <fstream>


using namespace std;


void Server::init(){
	sockVer = MAKEWORD(2,2);

	WSAStartup(sockVer, &wsaData);

	// Инициируем сокет

	servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(servSock == INVALID_SOCKET)
	{
		WSACleanup();
		throw SocketCreateErrorExeption();
	}
	SOCKADDR_IN sin;
	sin.sin_family = PF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr = INADDR_ANY;

	retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
	if(retVal == SOCKET_ERROR)
	{
		WSACleanup();
		throw BindErrorExeption();
	}

	// Пытаемся начать слушать сокет

	retVal = listen(servSock, 10);
	if(retVal == SOCKET_ERROR)
	{
		WSACleanup();
		throw SocketListenErrorExeption();
	}
}


Server::Server(char* pathToFolder, int userPort){

	folder = pathToFolder;
	port = userPort;
	init();
}


Server::~Server(){
	//Закрываем сокет
	closesocket(servSock);

	WSACleanup();
}

void Server::closeClient(){
	closesocket(clientSock);
}

void Server::waitClient(){

	char szReq[REQUEST_SIZE] ={'\0'}; 

	clientSock = accept(servSock, NULL, NULL);

	if(clientSock == INVALID_SOCKET)
	{
		WSACleanup();
		throw ClientAcceptExeption();
	}

	retVal = recv(clientSock, szReq, REQUEST_SIZE, 0);
	if(retVal == SOCKET_ERROR)
	{
		throw ClientReceiptExeption();
	}

	req = szReq;
}


void Server::sendResponce(){

	printf("Отправка данных клиенту...\n");
	retVal = send(clientSock, responce, strlen(responce), 0);

	if(retVal == SOCKET_ERROR)
	{
		throw ClientSendExeption();
	}

	printf("Отправлено %d байт\n", retVal);

}

string Server::parse(){
	string fileName;
	size_t st = 0;	// начало имени файла p+1
	size_t en = 0;	// конец имени файла

	if (req == ""){
		cout << "===============================================================\n\n";
		cout << "Получен пустой запрос.\n";			
		cout << "===============================================================\n\n";
	} else {

		cout << "===============================================================\n\n";
		cout << "Получен запрос.\n";

		st = req.find_first_of(" ", st);
		en = req.find_first_of(" ", st+1);
		fileName = req.substr(st+2, en-st-1);
		if (en-st==2){
			fileName = "index.html";
		}

	}
	return fileName;
}


void Server::getFileContent(string fName){

	struct stat fStat;

	stat(fName.c_str(), &fStat);
	int fSize = fStat.st_size; 
	if (fSize > 0){
		string path = folder;
		if (folder != ""){
			path+="/";
		}
		path+=fName;
		cout << "Поиск файла " << fName << " ...\n";

		FILE *sourceFile = fopen(path.c_str(), "r");
		if (sourceFile != NULL){
			cout << "Файл найден" << "\n";
		} else {
			sourceFile = fopen("files/404.html", "r");
			cout << "Ошибка 404: файл не найден" << "\n";
		}

		responce = new char[fSize];

		size_t size = fread(responce, sizeof(char), fSize, sourceFile);

		responce[fSize-1]='\0';
		fclose(sourceFile);
	}
}


void Server::processRequest(){
	string file = parse();
	getFileContent(file);
	sendResponce();
	closeClient();

}

