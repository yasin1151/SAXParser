#ifndef _SAXParser_H_
#define _SAXParser_H_


/*
	基于cocos2dx的CCSAXParser和tinyxml2
	被我从cocos2dx中抽离出来并进行了一些修改

*/
#include "tinyxml2.h"
#include "yfile.h"
#include <string>
#include <vector>



/*
* @class : SAXDelegator
* @brief : SAX解析窗口
*/
class SAXDelegator
{
public:
	virtual ~SAXDelegator(){}

	/**
	* @brief : XmlSaxHander会将当前行的属性开头<>部分的信息传入
	* @param ctx : 当前SAXParser实例
	* @param name : 当前的元素名
	* @param atts : 开头部分的所有属性和值
	*/
	virtual void startElement(void *ctx, const char *name, const char **atts) = 0;

	/**
	* @brief : XmlSaxHander会将当前行的末尾部分</>的名字传入
	* @param ctx : 当前SAXParser实例
	* @param name : 结尾的元素名
	*/
	virtual void endElement(void *ctx, const char *name) = 0;

	/**
	* @brief : XmlSaxHander会将当前行的内部文字传入,
	*	       如果文字被内部子元素中断，则会在解析完子元素后进行再次传入
	*
	*	<string>hello<stringChild></stringChild>world</stirng>
	*
	* @param ctx : 当前SAXParser实例
	* @param s : 文字字符串
	* @param len : 文字的长度
	*/
	virtual void textHandler(void *ctx, const char *content, int len) = 0;
};

/*
* @class : SAXParser
* @brief : 承担解析的职责
*/
class SAXParser
{
protected:
	SAXDelegator*		_delegator;
public:

	SAXParser();

	~SAXParser();

	/**
	*@brief : 进行一些初始化工作
	*@param encoding : 编码格式
	*/
	bool init(const char * encoding);

	/**
	* @brief : 对xml数据进行翻译
	* @param xmlData : xml字符串
	* @param dataLength : 字符串长度
	*/
	bool parse(const char* xmlData, size_t dataLength);

	/**
	* @brief : 对xml文件进行翻译，
	*		   最后调用parse(const char*, size_t)
	* @param fileName : 文件名
	*/
	bool parse(const std::string& fileName);

	/**
	* @brief : 设置SAX解析窗口
	* @param delegator : SAX解析窗口
	*/
	void setDelegator(SAXDelegator* delegator);

	/**
	* @brief : 由XmlSaxHander调用，
	*		   最后调用SAXDelegator的startElement()
	* @param ctx: SAXParser实例
	* @param name : 当前解析的元素名
	* @param atts : 当前元素的所有属性
	*/
	static void startElement(void* ctx, const unsigned char* name, const unsigned char** atts);

	/**
	* @brief : 由XmlSaxHander调用，
	*		   最后调用SAXDelegator的endElement()
	* @param ctx : SAXParser实例
	* @param name : 当前解析的元素名
	*/
	static void endElement(void* ctx, const unsigned char* name);

	/**
	* @brief : 由XmlSaxHander调用，
	*		   最后调用SAXDelegator的textHandler()
	* @param ctx : SAXParser实例
	* @param context : 当前元素的内容
	* @param len : 内容的长度
	*/
	static void textHandler(void* ctx, const unsigned char* content, int len);
};


/*
* @class : XmlSaxHandler
* @brief : 继承自XMLVisitorm，用来转发给SAXParser
*/
class XmlSaxHander : public tinyxml2::XMLVisitor
{
protected:
	SAXParser*		_ccsaxParserImp;
public:

	XmlSaxHander() :_ccsaxParserImp(nullptr){};

	virtual bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute) override;

	virtual bool VisitExit(const tinyxml2::XMLElement& element) override;

	virtual bool Visit(const tinyxml2::XMLText& text) override;

	virtual bool Visit(const tinyxml2::XMLUnknown&) override 
	{ 
		return true; 
	}

	void setSAXParserImp(SAXParser* parser)
	{
		_ccsaxParserImp = parser;
	}
};

#endif