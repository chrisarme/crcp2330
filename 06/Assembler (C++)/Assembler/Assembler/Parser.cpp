#include <iostream>
#include <fstream>
#include "Parser.h"

Parser::Parser()
{
	// nothing yet
}

void Parser::getLinesFromFile(string path)
{
	ifstream openFile;
	
	openFile.open(path);

	if (openFile.fail())
	{
		cout << "Oh No!" << endl;
		exit(1);
	}
	else
	{
		while (getline(openFile, aLineTemp))
		{
			aLines.push_back(aLineTemp);
		}
	}

	openFile.close();
	openFile.clear();

	/*for (int i = 0; i < aLines.size(); i++)
	{
		cout << aLines[i] << endl;
	}*/
}

void Parser::convertToBinary()
{
	for (int i = 0; i < aLines.size(); i++)
	{
		if (aLines[i].size() > 0)
		{
			if (aLines[i].at(0) == 'D' || aLines[i].at(0) == 'A' || aLines[i].at(0) == 'M')
			{
				bLines.push_back("111");
			}
		}
	}

	for (int i = 0; i < bLines.size(); i++)
	{
		cout << bLines[i] << endl;
	}
}