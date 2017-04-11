#include <iostream>
using namespace std;

#include "example\SAXExpParser.h"

int main()
{
	SAXExpParser parser;
	parser.parse("string.xml");

	cout << endl << "name set: " << endl;
	for (int i = 0; i < parser.getSize(); i++)
	{
		cout << "name " << i + 1 << " = " << parser[i] << endl;
	}
	return 0;
}