#ifndef _MyParser_H_
#define _MyParser_H_

#include "CCSAXParser.h"
#include "yUtils.h"
#include <iostream>
#include <windows.h>
using namespace std;

class MyParser : public SAXDelegator
{
public:
	void parse(const char* fileName);

	virtual void startElement(void* ctx, const char* name, const char** atts) override;
	virtual void endElement(void* ctx, const char* name) override;
	virtual void textHandler(void* ctx, const char* s, int len) override;

	std::string gbk2utf(const std::string& str);
	std::string utf2gbk(const std::string& str);
};

#endif