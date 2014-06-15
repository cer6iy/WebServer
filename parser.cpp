#include "stdafx.h"
#include "parser.h"

Parser::Parser(){
	fileName = "";
}

Parser::~Parser(){
	 fileName.clear();
}

string Parser::parse(string req){
	size_t st = 0;	// начало имени файла p+1
	size_t en = 0;	// конец имени файла

	st = req.find_first_of(" ", st);
	en = req.find_first_of(" ", st+1);
	fileName = req.substr(st+2, en-st-1);
	if (en-st==2){
		fileName = "index.html";
	}

	return fileName;
}
