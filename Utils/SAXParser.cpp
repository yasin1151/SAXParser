#include "SAXParser.h"

bool XmlSaxHander::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute)
{
	std::vector<const char*> attsVector;
	for (const tinyxml2::XMLAttribute* attrib = firstAttribute; attrib; attrib = attrib->Next())
	{
		attsVector.push_back(attrib->Name());
		attsVector.push_back(attrib->Value());
	}

	attsVector.push_back(nullptr);

	SAXParser::startElement(_ccsaxParserImp,
		reinterpret_cast<const unsigned char *>(element.Value()),
		reinterpret_cast<const unsigned char **>(&attsVector[0]));
	return true;
}

bool XmlSaxHander::VisitExit(const tinyxml2::XMLElement& element)
{
	SAXParser::endElement(_ccsaxParserImp,
		reinterpret_cast<const unsigned char *>(element.Value()));
	return true;
}

bool XmlSaxHander::Visit(const tinyxml2::XMLText& text)
{
	SAXParser::textHandler(_ccsaxParserImp,
		reinterpret_cast<const unsigned char *>(text.Value()),
		static_cast<int>(strlen(text.Value())));
	return true;
}

SAXParser::SAXParser()
	:_delegator(nullptr)
{

}

SAXParser::~SAXParser()
{

}

bool SAXParser::init(const char* encoding)
{

	return true;
}

bool SAXParser::parse(const char* xmlData, size_t dataLength)
{
	tinyxml2::XMLDocument tinyDoc;
	tinyDoc.Parse(xmlData, dataLength);
	XmlSaxHander printer;
	printer.setSAXParserImp(this);

	return tinyDoc.Accept(&printer);
}

bool SAXParser::parse(const std::string& filename)
{
	bool ret = false;

	if (!filename.empty())
	{
		yUtils::CFile fileHandler;
		if (!fileHandler.load(filename.c_str(), "r"))
		{
			return false;
		}

		int size = fileHandler.getSize();
		char* buf = new char[size + 1];
		memset(buf, 0, size + 1);
		fileHandler.read(buf, size);

		//key
		ret = this->parse(buf, size);

		delete[] buf;
		buf = nullptr;
	}

	/*Data data = FileUtils::getInstance()->getDataFromFile(filename);
	if (!data.isNull())
	{

	ret = parse((const char*)data.getBytes(), data.getSize());
	}
	*/
	return ret;
}

void SAXParser::startElement(void* ctx, const unsigned char* name, const unsigned char** atts)
{
	static_cast<SAXParser*>(ctx)->_delegator->startElement(ctx, (char*)name, reinterpret_cast<const char**>(atts));
}

void SAXParser::endElement(void* ctx, const unsigned char* name)
{
	static_cast<SAXParser*>(ctx)->_delegator->endElement(ctx, (char*)name);
}

void SAXParser::textHandler(void* ctx, const unsigned char* content, int len)
{
	static_cast<SAXParser*>(ctx)->_delegator->textHandler(ctx, (char*)content, len);
}

void SAXParser::setDelegator(SAXDelegator* delegator)
{
	_delegator = delegator;
}


