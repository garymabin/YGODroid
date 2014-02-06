/*
 * YGOGameConfig.cpp
 *
 *  Created on: 2014年1月31日
 *      Author: mabin
 */

#include "YGOGameConfig.h"

USING_NS_CC;

namespace ygo {
static YGOGameConfig* s_gameConfig;

YGOGameConfig::~YGOGameConfig() {
	CCFileUtils::purgeFileUtils();
}

YGOGameConfig* YGOGameConfig::sharedGameConfig() {
	if (!s_gameConfig) {
		s_gameConfig = new YGOGameConfig();
		s_gameConfig->init();
	}
	return s_gameConfig;
}

void YGOGameConfig::init() {
	m_pfileUtils = CCFileUtils::sharedFileUtils();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string path = ::getExternalStorageDir();
	path.append("/ygocore/YGOPRO1032.1");
	CCLOG("new search path: %s", path.c_str());
	m_pfileUtils->addSearchPath(path.c_str());
#endif
	YGOImageManager* pImageManager = YGOImageManager::sharedImageManager();
	YGODataManager* pDataManager = YGODataManager::sharedDataManager();
	pDataManager->LoadDB("cards.cdb");
	pDataManager->LoadStrings("strings.conf");
	YGODeckManager* pDeckManager = YGODeckManager::sharedDeckManager();
	pDeckManager->LoadLFList();
	loadConfig();
}

YGOGameConfig::YGOGameConfig() {
}

void YGOGameConfig::loadConfig() {
	const char* path = m_pfileUtils->fullPathForFilename("system.conf").c_str();
	FILE* fp = fopen(path, "r");
	if (!fp)
		return;
	char linebuf[256];
	char strbuf[32];
	char valbuf[256];
	char tmp_str[256];
	m_commonConfig.antialias = 0;
	m_commonConfig.serverport = 7911;
	m_commonConfig.textfontsize = 12;
	m_commonConfig.nickname[0] = 0;
	m_commonConfig.gamename[0] = 0;
	m_commonConfig.lastdeck[0] = 0;
	m_commonConfig.numfont[0] = 0;
	m_commonConfig.textfont[0] = 0;
	m_commonConfig.lastip[0] = 0;
	m_commonConfig.lastport[0] = 0;
	m_commonConfig.roompass[0] = 0;
	fseek(fp, 0, SEEK_END);
	int fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	while (ftell(fp) < fsize) {
		fgets(linebuf, 250, fp);
		sscanf(linebuf, "%s = %s", strbuf, valbuf);
		if (!strcmp(strbuf, "antialias")) {
			m_commonConfig.antialias = atoi(valbuf);
		}/*else if (!strcmp(strbuf, "use_d3d")) {
			m_commonConfig.use_d3d = atoi(valbuf) > 0;
		} else if (!strcmp(strbuf, "errorlog")) {
			m_commonConfig. = atoi(valbuf);
		}*/ else if (!strcmp(strbuf, "nickname")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.nickname, 40);
		} else if (!strcmp(strbuf, "gamename")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.gamename, 40);
		} else if (!strcmp(strbuf, "lastdeck")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.lastdeck, 128);
		} /*else if (!strcmp(strbuf, "textfont")) {
			BufferIO::DecodeUTF8(valbuf, tmp_str);
			int textfontsize;
			sscanf(linebuf, "%s = %s %d", strbuf, valbuf, &textfontsize);
			m_commonConfig.textfontsize = textfontsize;
			strncpy(tmp_str, m_commonConfig.textfont, 512);
		} */else if (!strcmp(strbuf, "numfont")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.numfont, 512);
		} else if (!strcmp(strbuf, "serverport")) {
			m_commonConfig.serverport = atoi(valbuf);
		} else if (!strcmp(strbuf, "lastip")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.lastip, 40);
		} else if (!strcmp(strbuf, "lastport")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.lastport, 40);
		} else if (!strcmp(strbuf, "roompass")) {
//			BufferIO::DecodeUTF8(valbuf, tmp_str);
			strncpy(valbuf, m_commonConfig.roompass, 40);
		}
	}
	fclose(fp);
}

} /* namespace ygo */


