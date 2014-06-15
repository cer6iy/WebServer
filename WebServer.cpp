// WebServer.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include <time.h>
#include "server.h"

using namespace std;



int main(int argc, char* argv[])
{
	setlocale(0,"RUS");


	char* path = NULL;
	string req;
	string fileName;
	string responce;

	if (argc== 1){
		printf("===============================================================\n\n");
		printf("Сервер будет запущен c параметрами по умолчанию.\nВ качестве корневой папки будет установлена текущая.\nЧтобы сменить,  укажите путь к папке:\n");
		printf("[<путь_к_папке>]\n\n");		
		printf("===============================================================\n");
		_getch();
		system("CLS");
	} else {
		path = argv[1];
	}

	Server MyServer;

	while (true){

		MyServer.waitClient();

		// вывод текущего времени
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		char* format = "%I:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		cout << "" << buffer << "\n";

		MyServer.processRequest();

		cout << "===============================================================\n\n\n\n";
		responce.clear();
	}

	return 0;
}

