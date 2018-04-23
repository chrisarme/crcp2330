#include <iostream>
#include <fstream>
#include <bitset>
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
			string tempInstr;
			bool commentExists = false;
			int commentPosition;

			if (aLines[i].find("//") != string::npos)
			{
				commentExists = true;
				commentPosition = aLines[i].find("//");
			}

			if (aLines[i].at(0) == '@')
			{
				bool isAIntrNotLabel = true;

				tempInstr = "0";

				for (int d = 1; d < aLines[i].length(); d++)
				{
					if (!commentExists || d < commentPosition)
					{
						if (!isdigit(aLines[i].at(d)) && aLines[i].at(d) != ' ')
						{
							isAIntrNotLabel = false;
						}
					}
				}

				if (isAIntrNotLabel)
				{
					long int tempInstrDec;

					if (commentExists)
					{
						tempInstrDec = atol(aLines[i].substr(1, aLines[i].length() - (aLines[i].length() - commentPosition) - 1).c_str());
					}
					else
					{
						tempInstrDec = atol(aLines[i].substr(1, aLines[i].length() - 1).c_str());
					}

					tempInstr += std::bitset<15>(tempInstrDec).to_string();
				}


				bLines.push_back(tempInstr);
			}
			//else if (aLines[i].at(0) == 'D' || aLines[i].at(0) == 'A' || aLines[i].at(0) == 'M')
			else if (aLines[i].find('=') != string::npos || aLines[i].find(';') != string::npos)
			{
				tempInstr = "111";

				string compTemp;
				string destTemp;
				string jumpTemp;
				int equalSignPosition = aLines[i].find('=');
				int semiColonPosition = aLines[i].find(';');

				if (equalSignPosition != string::npos)
				{
					string tempSubString = aLines[i].substr(0, equalSignPosition);
					if (tempSubString.find('A') != string::npos)
					{
						destTemp += "1";
					}
					else
					{
						destTemp += "0";
					}

					if (tempSubString.find('D') != string::npos)
					{
						destTemp += "1";
					}
					else
					{
						destTemp += "0";
					}

					if (tempSubString.find('M') != string::npos)
					{
						destTemp += "1";
					}
					else
					{
						destTemp += "0";
					}
				}
				else
				{
					destTemp = "000";
				}

				if (semiColonPosition != string::npos)
				{
					string tempSubString = aLines[i].substr(semiColonPosition + 1, aLines[i].length());

					if (tempSubString == "JGT")
					{
						jumpTemp = "001";
					}
					else if (tempSubString == "JEQ")
					{
						jumpTemp = "010";
					}
					else if (tempSubString == "JGE")
					{
						jumpTemp = "011";
					}
					else if (tempSubString == "JLT")
					{
						jumpTemp = "100";
					}
					else if (tempSubString == "JNE")
					{
						jumpTemp = "101";
					}
					else if (tempSubString == "JLE")
					{
						jumpTemp = "110";
					}
					else if (tempSubString == "JMP")
					{
						jumpTemp = "111";
					}
				}
				else
				{
					jumpTemp = "000";
				}

				tempInstr += compTemp + destTemp + jumpTemp;

				bLines.push_back(tempInstr);
			}
		}

		//tempInstr = "";
	}

	for (int i = 0; i < bLines.size(); i++)
	{
		cout << bLines[i] << endl;
	}
}