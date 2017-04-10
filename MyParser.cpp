#include "MyParser.h"

void MyParser::parse(const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	SAXParser parser;
	parser.setDelegator(this);
	parser.parse(fileName);
}

void MyParser::startElement(void* ctx, const char* name, const char** atts)
{
	cout << "start name : " << name << endl;
	if (atts && *atts)
	{
		cout << "atts[0] :" << atts[0] << endl;
		cout << "atts[1] :" << atts[1] << endl;
	}
}

void MyParser::endElement(void* ctx, const char* name)
{
	cout << "end name : " << name << endl;
}

void MyParser::textHandler(void* ctx, const char* s, int len)
{
	cout << "text : " << s << endl;
}

std::string MyParser::gbk2utf(const std::string& str)
{
	std::wstring wszBuf = [=]()
	{
		//将string装换成wstring
		setlocale(LC_ALL, "chs");
		const char* szSource = str.c_str();
		size_t uSize = str.size() + 1;
		wchar_t* wszDest = new wchar_t[uSize];
		wmemset(wszDest, 0, uSize);
		mbstowcs(wszDest, szSource, uSize);
		std::wstring result = wszDest;
		delete[] wszDest;
		setlocale(LC_ALL, "C");
		return result;
	}();

	int iAsciSize = WideCharToMultiByte(CP_UTF8, 0, wszBuf.c_str(), wszBuf.size(), NULL, 0, NULL, NULL);
	if (ERROR_NO_UNICODE_TRANSLATION == iAsciSize || 0 == iAsciSize)
	{
		return std::string();
	}

	char* szRetStr = new char[iAsciSize];
	int iConveRet = WideCharToMultiByte(CP_UTF8, 0, wszBuf.c_str(), wszBuf.size(), szRetStr, iAsciSize, NULL, NULL);
	if (iConveRet != iAsciSize)
	{
		return std::string();
	}

	std::string szBuf = "";
	szBuf.append(szRetStr, iAsciSize);

	delete[] szRetStr;
	return szBuf;
}

std::string MyParser::utf2gbk(const std::string& str)
{
	std::wstring wszBuf = [=]()
	{
		//将string装换成wstring
		setlocale(LC_ALL, "chs");
		const char* szSource = str.c_str();
		size_t uSize = str.size() + 1;
		wchar_t* wszDest = new wchar_t[uSize];
		wmemset(wszDest, 0, uSize);
		mbstowcs(wszDest, szSource, uSize);
		std::wstring result = wszDest;
		delete[] wszDest;
		setlocale(LC_ALL, "C");
		return result;
	}();

	int iAsciSize = WideCharToMultiByte(CP_ACP, 0, wszBuf.c_str(), wszBuf.size(), NULL, 0, NULL, NULL);
	if (ERROR_NO_UNICODE_TRANSLATION == iAsciSize || 0 == iAsciSize)
	{
		return std::string();
	}

	char* szRetStr = new char[iAsciSize];
	int iConveRet = WideCharToMultiByte(CP_ACP, 0, wszBuf.c_str(), wszBuf.size(), szRetStr, iAsciSize, NULL, NULL);
	if (iConveRet != iAsciSize)
	{
		return std::string();
	}

	std::string szBuf = "";
	szBuf.append(szRetStr, iAsciSize);

	delete[] szRetStr;
	return szBuf;
}
