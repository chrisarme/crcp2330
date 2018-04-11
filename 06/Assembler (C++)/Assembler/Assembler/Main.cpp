#include <iostream>
#include "Main.h"

using namespace std;

int main()
{
	parser.getLinesFromFile("test.txt");
	parser.convertToBinary();

	system("PAUSE");
	return 0;
}