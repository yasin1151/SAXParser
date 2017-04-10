#ifndef _SAXParser_H_
#define _SAXParser_H_


/*
	基于cocos2dx的CCSAXParser和tinyxml2
	被我从cocos2dx中抽离出来并进行了一些修改

*/
#include "tinyxml2.h"
#include "yfile.h"
#include "tinyxml2.h"
#include <string>
#include <vector>



/*
	@class : SAXDelegator
	@brief : SAX解析窗口
*/
class SAXDelegator
{
public:
	virtual ~SAXDelegator(){}

	/**
		@brief : XmlSaxHander会将当前行的属性开头<>部分的信息传入
		@param ctx : 当前SAXParser实例
		@param name : 当前的元素名
		@param atts : 开头部分的所有属性和值
	*/
	virtual void startElement(void *ctx, const char *name, const char **atts) = 0;

	/**
		@brief : XmlSaxHander会将当前行的末尾部分</>的名字传入
		@param ctx : 当前SAXParser实例
		@param name : 结尾的元素名
	*/
	virtual void endElement(void *ctx, const char *name) = 0;

	/**
		@brief : XmlSaxHander会将当前行的内部文字传入,
				如果文字被内部子元素中断，则会在解析完子元素后进行再次传入

				<string>
					hello
					<stringChild>
					</stringChild>
					world
				</stirng>

		@param ctx : 当前SAXParser实例
		@param s : 文字字符串
		@param len : 文字的长度
	*/
	virtual void textHandler(void *ctx, const char *s, int len) = 0;
};


class SAXParser
{
protected:
	SAXDelegator*		_delegator;
public:

	SAXParser() :_delegator(nullptr) {}

	~SAXParser() {}


	bool init(const char *encoding);
	/**
	* @js NA
	* @lua NA
	*/
	bool parse(const char* xmlData, size_t dataLength);
	/**
	* @js NA
	* @lua NA
	*/
	bool parse(const std::string& filename);
	/**
	* @js NA
	* @lua NA
	*/
	void setDelegator(SAXDelegator* delegator);
	/**
	* @js NA
	* @lua NA
	*/
	static void startElement(void *ctx, const unsigned char*name, const unsigned char**atts);
	/**
	* @js NA
	* @lua NA
	*/
	static void endElement(void *ctx, const unsigned char*name);
	/**
	* @js NA
	* @lua NA
	*/
	static void textHandler(void *ctx, const unsigned char*name, int len);
};


#endif