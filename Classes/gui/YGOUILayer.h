/*
 * YGOUILayer.h
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#ifndef YGOUILAYER_H_
#define YGOUILAYER_H_

#include "CommonGui.h"
#include "DropDownList.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

class YGOUILayer: public cocos2d::CCLayer {
public:
	YGOUILayer();
	virtual ~YGOUILayer();
	virtual bool init();
	virtual void dropdownListCallback(CCObject* pSender);
	virtual void buttonCallback(CCObject* pSender, TouchEventType type);
protected:
	TouchGroup* m_pWidgetContainer;
	virtual void onEvent(int tag) = 0;
	virtual Label* addNewLabel(Widget* container, int tag, const char* key);
	virtual CCEditBox* addNewEditBox(Widget* container, int tag, const char* key);
	virtual DropDownList* addNewDropDownList(Widget* container, int tag, vector<CCString*> *strings);
	virtual CheckBox* addNewCheckBox(Widget* container, int tag);
	virtual Button* addNewButton(Widget* container, int tag, const char* key);
};

} /* namespace ygo */
#endif /* YGOUILAYER_H_ */
