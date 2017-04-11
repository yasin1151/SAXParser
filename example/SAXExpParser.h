/**
* name   : SAXExpParser.h
* auther : PengYao
* time	 : 2017/4/11
*/
#ifndef _SAXExpParser_H_
#define _SAXExpParser_H_

#include "../Utils/SAXParser.h"
#include <string>
#include <iostream>
using namespace std;


/**
* @class : SAXExpParser
* @brief : 继承自SAX解析窗口，重写父类三个方法
* @warning : 没有遵循单一职责原则，可以多写一个handler用于存储数据
*/
class SAXExpParser : public SAXDelegator
{
protected:
	vector<string> m_arrString;
public:
	/**
	* @brief : 翻译xml文件
	* @param fileName : xml文件地址
	*/
	bool parse(const char* fileName);

	/**
	* @brief : 重写基类的三个方法，用于解析每一个元素
	*/
	virtual void startElement(void* ctx, const char* name, const char** atts) override;
	virtual void endElement(void* ctx, const char* name) override;
	virtual void textHandler(void* ctx, const char* content, int len) override;

	/**
	* @brief : 获取翻译后的元素
	* @param pos : 数组下标 0 - n
	*/
	string operator [] (int pos);

	/**
	* @brief : 获取当前解析出来的元素个数
	*/
	int getSize() const;
};

#endif