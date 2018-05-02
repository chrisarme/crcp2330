#include <iostream>
#include "Main.h"

using namespace std;

int main()
{
	parser = Parser();
	parser.getLinesFromFile("test.txt");
	parser.convertToBinary();

	system("PAUSE");
	return 0;
}