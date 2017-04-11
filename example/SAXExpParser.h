#ifndef _SAXExpParser_H_
#define _SAXExpParser_H_

#include "../Utils/SAXParser.h"
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class SAXExpParser : public SAXDelegator
{

protected:
	unordered_map<string, string> m_map;
	vector<string> m_arrString;
public:
	bool parse(const char* fileName);
	virtual void startElement(void* ctx, const char* name, const char** atts) override;
	virtual void endElement(void* ctx, const char* name) override;
	virtual void textHandler(void* ctx, const char* content, int len) override;
	string operator [] (int pos);
	int getSize() const;
};

#endif