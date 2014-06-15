
#pragma once

#include "stdafx.h"
#include <string>

using namespace std;


class Filer
{
private:
	string fileContent;
public:
	Filer();
	~Filer();
	string getFileContent(string);
};
