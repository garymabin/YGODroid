/*
 * XmlParser.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#include "XMLParser.h"

using namespace cocos2d;
using namespace std;

// 空格
const static int SPACE = 32;
// 换行
const static int NEXTLINE = 10;
// tab 横向制表符
const static int TAB = 9;

static XMLParser* s_StringParser = NULL;
static CCDictionary* s_pDictionary = NULL;

XMLParser::XMLParser() {
}

XMLParser::~XMLParser() {
}

XMLParser* XMLParser::sharedXMLParser() {
	if (!s_StringParser) {
		s_StringParser = XMLParser::parseWithFile("values-zh-rCN/strings.xml");
	}
	return s_StringParser;
}

XMLParser* XMLParser::parseWithFile(const char *xmlFileName) {
	XMLParser *pXMLParser = new XMLParser();
	if (pXMLParser->initWithFile(xmlFileName)) {
		pXMLParser->autorelease();
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithFile(const char *xmlFileName) {
	s_pDictionary = new CCDictionary();
	CCSAXParser _parser;
	_parser.setDelegator(this);
	std::string fullPath =
			CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
	return _parser.parse(fullPath.c_str());
}

XMLParser* XMLParser::parseWithString(const char *content) {
	XMLParser *pXMLParser = new XMLParser();
	if (pXMLParser->initWithString(content)) {
		pXMLParser->autorelease();
		return pXMLParser;
	}
	CC_SAFE_DELETE(pXMLParser);
	return NULL;
}

bool XMLParser::initWithString(const char *content) {
	s_pDictionary = new CCDictionary();
	CCSAXParser _parse;
	_parse.setDelegator(this);
	return _parse.parse(content, strlen(content));
}

void XMLParser::startElement(void *ctx, const char *name, const char **atts) {
	startXMLElement = (char *) name;
	CCLog("start=%s", startXMLElement.c_str());
	if (startXMLElement == "string") {
		while (atts && *atts) {
			const char *attsKey = *atts;
			if (0 == strcmp(attsKey, "name")) {
				++atts;
				const char *attsValue = *atts;
				m_key = attsValue;
				break;
			}
			++atts;
		}
	}
}

void XMLParser::endElement(void *ctx, const char *name) {
	endXMLElement = (char *) name;
	CCLog("end=%s", endXMLElement.c_str());
}

void XMLParser::textHandler(void *ctx, const char *s, int len) {
	string value((char *) s, 0, len);
//是否全是非正常字符
	bool noValue = true;
	for (int i = 0; i < len; ++i) {
		if (s[i] != SPACE && s[i] != NEXTLINE && s[i] != TAB) {
			noValue = false;
			break;
		}
	}
	if (noValue)
		return;
	CCString *pString = CCString::create(value);
	CCLog("key=%s value=%s", m_key.c_str(), pString->getCString());
	s_pDictionary->setObject(pString, m_key);
}

CCString* XMLParser::getString(const char *key) {
	string strKey(key);
	return (CCString *) s_pDictionary->objectForKey(strKey);
}
