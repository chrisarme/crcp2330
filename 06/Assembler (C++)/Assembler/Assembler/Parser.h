#pragma once

#include <string>
#include <vector>
using namespace std;

class Parser
{
private:
	string aLineTemp;
	vector<string> aLines;
	vector<string> bLines;
public:
	Parser();
	void getLinesFromFile(string path);
	void convertToBinary();
};