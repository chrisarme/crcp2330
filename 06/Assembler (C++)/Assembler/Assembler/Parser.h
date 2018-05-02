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
	vector<string> labelsAndPredefined[2];
public:
	Parser();
	void getLinesFromFile(string path);
	void convertToBinary();
};