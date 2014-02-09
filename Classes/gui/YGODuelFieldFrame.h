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
#include "YGOHandCardList.h"
#include "YGOGameConfig.h"
#include "CCMenuItemImageFont.h"
#include "YGOCardOpsPanel.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

class YGOMainScene;

class YGODuelFieldFrame: public cocos2d::CCLayer {
public:
	YGODuelFieldFrame();
	virtual ~YGODuelFieldFrame();
	virtual bool init();
	void cardInHandDraggedCallBack(CCObject* pSender, void* param);
	void widgetTouchedCallBack(CCObject* pSender);
	void menuItemCallback(CCObject* pSender, void * param);
	Button* addNewButton(Widget* container, int tag, const char* key);
	void buttonCallback(CCObject* pSender, TouchEventType type);
	void onEvent(int tag);
	CREATE_FUNC(YGODuelFieldFrame)
protected:
	TouchGroup* m_pWidgetContainer;
	YGODeckManager* m_pDeckMgr;
	std::vector<CCString*> m_pDeckNameList;
	YGOCardOpsPanel* m_pCardOpsPanel;
	CC_SYNTHESIZE_READONLY(Button*, m_pSurranderButton, SurranderButton);
};

} /* namespace ygo */
#endif /* YGODUELFIELDFRAME_H_ */
