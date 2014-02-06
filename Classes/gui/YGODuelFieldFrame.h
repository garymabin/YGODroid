/*
 * YGODuelFieldFrame.h
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#ifndef YGODUELFIELDFRAME_H_
#define YGODUELFIELDFRAME_H_

#include "CommonGui.h"
#include "YGODeckManager.h"
#include "YGOCardCell.h"
#include "YGOCardDeck.h"
#include "YGOHandCardList.h"
#include "YGOGameConfig.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

class YGODuelFieldFrame: public cocos2d::CCLayer {
public:
	YGODuelFieldFrame();
	virtual ~YGODuelFieldFrame();
	virtual bool init();
	CREATE_FUNC(YGODuelFieldFrame)
protected:
	TouchGroup* m_pWidgetContainer;
	YGODeckManager* m_pDeckMgr;
	std::vector<CCString*> m_pDeckNameList;
};

} /* namespace ygo */
#endif /* YGODUELFIELDFRAME_H_ */
