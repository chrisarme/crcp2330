#include <iostream>
#include <fstream>
#include <bitset>
#include "Parser.h"

using namespace std;

Parser::Parser()
{
	for (int i = 0; i < 16; i++)
	{
		string tempString = "R" + i;
		string tempAddressString = bitset<15>(i).to_string();

		labelsAndPredefined[0].push_back(tempString);
		labelsAndPredefined[1].push_back(tempAddressString);
	}

	labelsAndPredefined[0].push_back("SCREEN");
	labelsAndPredefined[1].push_back(bitset<15>(16384).to_string());

	labelsAndPredefined[0].push_back("KBD");
	labelsAndPredefined[1].push_back(bitset<15>(24576).to_string());

	labelsAndPredefined[0].push_back("SP");
	labelsAndPredefined[1].push_back(bitset<15>(0).to_string());

	labelsAndPredefined[0].push_back("LCL");
	labelsAndPredefined[1].push_back(bitset<15>(1).to_string());

	labelsAndPredefined[0].push_back("ARG");
	labelsAndPredefined[1].push_back(bitset<15>(2).to_string());

	labelsAndPredefined[0].push_back("THIS");
	labelsAndPredefined[1].push_back(bitset<15>(3).to_string());

	labelsAndPredefined[0].push_back("THAT");
	labelsAndPredefined[1].push_back(bitset<15>(4).to_string());

	labelsAndPredefined[0].push_back("WRITE");
	labelsAndPredefined[1].push_back(bitset<15>(18).to_string());

	labelsAndPredefined[0].push_back("END");
	labelsAndPredefined[1].push_back(bitset<15>(22).to_string());

	labelsAndPredefined[0].push_back("i");
	labelsAndPredefined[1].push_back(bitset<15>(16).to_string());

	labelsAndPredefined[0].push_back("sum");
	labelsAndPredefined[1].push_back(bitset<15>(17).to_string());
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
			string aLine;
			for (int i = 0; i < aLineTemp.length(); i++)
			{
				if (aLineTemp[i] != ' ')
				{
					aLine += aLineTemp[i];
				}
			}

			aLines.push_back(aLine);
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
	int currentNewLabelAddress = 16;
	for (int i = 0; i < aLines.size(); i++)
	{
		if (aLines[i].front() == '(' && aLines[i].back() == ')')
		{
			//int tempInstrDec = atol(aLines[i].substr(1, aLines[i].length() - 2).c_str());
			for (int j = 0; j < labelsAndPredefined[0].size(); j++)
			{
				if (labelsAndPredefined[0][j] == aLines[i].substr(1, aLines[i].length() - 2))
				{
					string tempAddressString = std::bitset<15>(currentNewLabelAddress).to_string();

					labelsAndPredefined[0].push_back(aLines[i].substr(1, aLines[i].length() - 2));
					labelsAndPredefined[1].push_back(tempAddressString);

					currentNewLabelAddress++;
				}
			}
		}
	}

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

			else if (aLines[i].at(0) == '@')
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
				else
				{
					for (int a = 0; a < labelsAndPredefined[0].size(); a++)
					{
						if (commentExists)
						{
							if (aLines[i].substr(1, aLines[i].length() - (aLines[i].length() - commentPosition) - 1) == labelsAndPredefined[0][i])
							{
								//
							}
						}
						else
						{
							if (aLines[i].substr(1, aLines[i].length() - (aLines[i].length()) - 1) == labelsAndPredefined[0][i])
							{

							}
						}
					}
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

				// comp
				string compTempSubString;

				if (equalSignPosition != string::npos)
				{
					compTempSubString = aLines[i].substr(equalSignPosition + 1, aLines[i].length());
				}
				else if (semiColonPosition != string::npos)
				{
					compTempSubString = aLines[i].substr(0, semiColonPosition);
				}

				// Find if a = 0 or 1
				if (compTempSubString.find("M") != string::npos)
				{
					compTemp = "1";
				}
				else
				{
					compTemp = "0";
				}

				if (compTempSubString == "0")
				{
					compTemp += "101010";
				}
				else if (compTempSubString == "-1")
				{
					compTemp += "111010";
				}
				else if (compTempSubString == "1")
				{
					compTemp += "111111";
				}
				else if (compTempSubString == "D")
				{
					compTemp += "001100";
				}
				else if (compTempSubString == "A" || compTempSubString == "M")
				{
					compTemp += "110000";
				}
				else if (compTempSubString == "!D")
				{
					compTemp += "001101";
				}
				else if (compTempSubString == "!A" || compTempSubString == "!M")
				{
					compTemp += "110001";
				}
				else if (compTempSubString == "-D")
				{
					compTemp += "001111";
				}
				else if (compTempSubString == "-A" || compTempSubString == "-M")
				{
					compTemp += "110011";
				}
				else if (compTempSubString == "D+1")
				{
					compTemp += "011111";
				}
				else if (compTempSubString == "A+1" || compTempSubString == "M+1")
				{
					compTemp += "110111";
				}
				else if (compTempSubString == "D-1")
				{
					compTemp += "001110";
				}
				else if (compTempSubString == "A-1" || compTempSubString == "M-1")
				{
					compTemp += "110010";
				}
				else if (compTempSubString == "D+A" || compTempSubString == "D+M")
				{
					compTemp += "000010";
				}
				else if (compTempSubString == "D-A" || compTempSubString == "D-M")
				{
					compTemp += "010011";
				}
				else if (compTempSubString == "A-D" || compTempSubString == "M-D")
				{
					compTemp += "000111";
				}
				else if (compTempSubString == "D&A" || compTempSubString == "D&M")
				{
					compTemp += "000000";
				}
				else if (compTempSubString == "D|A" || compTempSubString == "D|M")
				{
					compTemp += "010101";
				}

				// dest
				if (equalSignPosition != string::npos)
				{
					string tempEqSubString = aLines[i].substr(0, equalSignPosition);
					if (tempEqSubString.find('A') != string::npos)
					{
						destTemp += "1";
					}
					else
					{
						destTemp += "0";
					}

					if (tempEqSubString.find('D') != string::npos)
					{
						destTemp += "1";
					}
					else
					{
						destTemp += "0";
					}

					if (tempEqSubString.find('M') != string::npos)
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

				// jump
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