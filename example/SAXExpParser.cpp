#include "SAXExpParser.h"

bool SAXExpParser::parse(const char* fileName)
{
	if (!fileName)
	{
		return false;
	}

	SAXParser parser;
	parser.setDelegator(this);
	parser.init("UTF-8");			//毫无意义的语句 = =
	return parser.parse(fileName);
}

void SAXExpParser::startElement(void* ctx, const char* name, const char** atts)
{
	cout << "startElement : " << endl << " name : " << name << endl;
	if (0 == strcmp(name, "string"))
	{
		while (atts && *atts)
		{
			cout << " atts[0] : " << atts[0] << " atts[1] : " << atts[1] << endl;
			if (0 == strcmp(atts[0], "name"))
			{
				m_arrString.push_back(atts[1]);
			}
			atts += 2;
		}
	}
}

void SAXExpParser::endElement(void* ctx, const char* name)
{
	cout << "endElement : " << endl << " name : " << name << endl;
}

void SAXExpParser::textHandler(void* ctx, const char* content, int len)
{
	cout << "textHandler : " << endl << " content : " << content << endl;
}

string SAXExpParser::operator[](int pos)
{
	return m_arrString[pos];
}

int SAXExpParser::getSize() const
{
	return m_arrString.size();
}
