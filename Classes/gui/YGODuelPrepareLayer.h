/*
 * YGODuelPrepareLayer.h
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#ifndef YGODUELPREPARELAYER_H_
#define YGODUELPREPARELAYER_H_

#include "CommonGui.h"
#include "YGODeckManager.h"
#include "DropDownList.h"
#include "YGOLANModeLayer.h"
#include "YGODuelScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;
using namespace std;

namespace ygo {

class YGODuelPrepareLayer: public cocos2d::CCLayerColor {
public:
	YGODuelPrepareLayer();
	virtual ~YGODuelPrepareLayer();
	virtual bool init();
	void dropdownListCallback(CCObject* pSender);
	void buttonCallback(CCObject* pSender, TouchEventType type);
	CREATE_FUNC(YGODuelPrepareLayer);
protected:
	TouchGroup* m_pWidgetContainer;
	void onEvent(int tag);
	Label* addNewLabel(Widget* container, int tag, const char* key);
	CCEditBox* addNewEditBox(Widget* container, int tag,
			const char* key = "");
	DropDownList* addNewDropDownList(Widget* container, int tag,
			vector<CCString*> *strings);
	CheckBox* addNewCheckBox(Widget* container, int tag);
	Button* addNewButton(Widget* container, int tag, const char* key = "");
	vector<CCString*> m_deckNameList;
	//开始
	CC_SYNTHESIZE_READONLY(Button *, m_pButtonStart, StartButton);
	//取消
	CC_SYNTHESIZE_READONLY(Button *, m_pButtonCancel, CancelButton);
private:
	YGODeckManager* m_pDeckMgr;
};

} /* namespace ygo */
#endif /* YGODUELPREPARELAYER_H_ */
