#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Parser
{
private:
	string fileName;
public:
	Parser();
	~Parser();
	string parse(string);
};
