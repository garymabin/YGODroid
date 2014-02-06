/*
 * YGOCreateServerLayer.h
 *
 *  Created on: 2014年2月3日
 *      Author: mabin
 */

#ifndef YGOCREATESERVERLAYER_H_
#define YGOCREATESERVERLAYER_H_

#include "CommonGui.h"
#include "DropDownList.h"
#include "YGOLANModeLayer.h"
#include "../network/netserver.h"
#include "YGODuelPrepareLayer.h"

USING_NS_CC;
using namespace gui;
using namespace extension;
using namespace std;

namespace ygo {

class YGOCreateServerLayer: public cocos2d::CCLayerColor {
public:
	YGOCreateServerLayer();
	virtual ~YGOCreateServerLayer();
	virtual bool init();
	void dropdownListCallback(CCObject* pSender);
	void buttonCallback(CCObject* pSender, TouchEventType type);
	CREATE_FUNC(YGOCreateServerLayer)
protected:
	TouchGroup* m_pWidgetContainer;
	void onEvent(int tag);
	Label* addNewLabel(Widget* container, int tag, const char* key);
	CCEditBox* addNewEditBox(Widget* container, int tag, const char* key);
	DropDownList* addNewDropDownList(Widget* container, int tag, vector<CCString*> *strings);
	CheckBox* addNewCheckBox(Widget* container, int tag);
	Button* addNewButton(Widget* container, int tag, const char* key);
	vector<CCString*>* m_pLimitListData;
	vector<CCString*>* m_pCardAllowedData;
	vector<CCString*>* m_pDuelModeData;
	//禁限卡表
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListLimit, LimitList);
	//卡片允许
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListCardAllowed, CardAllowedList);
	//决斗模式
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListDuelMode, DuelModeList);
	//每回合时间
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxTimeLimit, TimeLimitEditBox);
	//初始LP
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxInitLp, LifePointsEditBox);
	//初始手牌数
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxInitCards, InitCardsEditBox);
	//每回合抽卡
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxDrawCard, DrawCardEditBox);
	//主机名称
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxHostName, HostNameEditBox);
	//主机密码
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxPassword, PasswordEditBox);
	//允许启动效果优先权
	CC_SYNTHESIZE_READONLY(CheckBox *, m_pCheckBoxCEP, CEPEditBox);
	//不检查卡组
	CC_SYNTHESIZE_READONLY(CheckBox *, m_pCheckBoxIgnoreCheck, IgnoreCheckEditBox);
	//开局不洗卡组
	CC_SYNTHESIZE_READONLY(CheckBox *, m_pCheckBoxIgnoreShuffle, IgnoreShuffleEditBox);
	//确定
	CC_SYNTHESIZE_READONLY(Button *, m_pButtonConfirm, ConfirmButton);
	//取消
	CC_SYNTHESIZE_READONLY(Button *, m_pButtonCancel, CancelButton);

};

} /* namespace ygo */
#endif /* YGOCREATESERVERLAYER_H_ */
