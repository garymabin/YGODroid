/*
 * YGOGameConfig.h
 *
 *  Created on: 2014年1月31日
 *      Author: mabin
 */

#ifndef YGOGAMECONFIG_H_
#define YGOGAMECONFIG_H_

#include "cocos2d.h"
#include "bufferio.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../jni/ygodroid/CommonJni.h"
#endif
#include "YGODeckManager.h"
#include "YGOImageManager.h"

USING_NS_CC;

namespace ygo {

struct Config {
//	bool use_d3d;
	unsigned short antialias;
	unsigned short serverport;
	unsigned char textfontsize;
	char lastip[40];
	char lastport[20];
	char nickname[40];
	char gamename[40];
	char lastdeck[128];
	char textfont[512];
	char numfont[512];
	char roompass[40];
};

struct DuelInfo {
	bool isStarted;
	bool isReplay;
	bool isReplaySkiping;
	bool isFirst;
	bool isTag;
	bool isSingleMode;
	bool is_shuffling;
	bool tag_player[2];
	int lp[2];
	int turn;
	short curMsg;
	wchar_t hostname[20];
	wchar_t clientname[20];
	wchar_t hostname_tag[20];
	wchar_t clientname_tag[20];
	wchar_t strLP[2][16];
	wchar_t strTurn[8];
	wchar_t* vic_string;
	unsigned char player_type;
	unsigned char time_player;
	unsigned short time_limit;
	unsigned short time_left[2];
};

class YGOGameConfig {
public:
	YGOGameConfig();
	virtual ~YGOGameConfig();
	static YGOGameConfig* sharedGameConfig();
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(Config, m_commonConfig, CommonConfig);
	CC_SYNTHESIZE_READONLY(CCFileUtils*, m_pfileUtils, FiltUtils);
	DuelInfo m_duelInfo;
protected:
	void init();
	void loadConfig();
};

} /* namespace ygo */
#endif /* YGOGAMECONFIG_H_ */
