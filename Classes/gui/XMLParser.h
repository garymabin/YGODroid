/*
 * XmlParser.h
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <string>
#include "cocos2d.h"

class XMLParser: public cocos2d::CCObject, public cocos2d::CCSAXDelegator {
public:
	XMLParser();
	virtual ~XMLParser();

	static XMLParser* sharedXMLParser();
	static XMLParser* parseWithFile(const char *xmlFileName);
	static XMLParser* parseWithString(const char *content);

	// 从本地xml文件读取
	bool initWithFile(const char *xmlFileName);
	// 从字符中读取，可用于读取网络中的xml数据
	bool initWithString(const char *content);
	/**
	 *对应xml标签开始,如：<string name="alex">, name为string，atts为string的属性，如["name","alex"] */
	virtual void startElement(void *ctx, const char *name, const char **atts);
	/**
	 *对应xml标签结束,如：</string>
	 */
	virtual void endElement(void *ctx, const char *name);
	/**
	 *对应xml标签文本,如：<string name="alex">Alex Zhou</string>的Alex Zhou
	 */
	virtual void textHandler(void *ctx, const char *s, int len);
	cocos2d::CCString* getString(const char *key);
private:
	std::string m_key;
	std::string startXMLElement;
	std::string endXMLElement;
};

#endif /* XMLPARSER_H_ */
