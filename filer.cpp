#include "stdafx.h"
#include "filer.h"
#include <iostream>
#include <string>

Filer::Filer(){
	fileContent.clear();		
}

Filer::~Filer(){
	fileContent.clear();
}

string Filer::getFileContent(string fName){
	fileContent.clear();

	char ch;

	FILE *sourceFile = fopen(fName.c_str(), "r");
	if (sourceFile != NULL){
		cout << "���� ������" << "\n";
	} else {
		sourceFile = fopen("files/404.html", "r");
		cout << "������ 404: ���� �� ������" << "\n";
	}

	while((ch = getc(sourceFile)) != EOF){ //fread
		fileContent+=ch;
	}

	fclose(sourceFile);

	return fileContent;
}
