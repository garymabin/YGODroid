/*
 * YGOUILayer.cpp
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#include "YGOUILayer.h"

namespace ygo {

YGOUILayer::YGOUILayer() {
	// TODO Auto-generated constructor stub

}

YGOUILayer::~YGOUILayer() {
	m_pWidgetContainer->clear();
	m_pWidgetContainer->release();
}

bool YGOUILayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pWidgetContainer = TouchGroup::create();
	m_pWidgetContainer->retain();
	CCSize mainPanelSize = m_pWidgetContainer->getContentSize();
	m_pWidgetContainer->setPosition(
			ccp((visibleSize.width - mainPanelSize.width)/2, (visibleSize.height - mainPanelSize.height)/2));
	this->addChild(m_pWidgetContainer);
	return true;
}

void YGOUILayer::dropdownListCallback(CCObject* pSender) {
	onEvent(dynamic_cast<DropDownList*>(pSender)->getTag());
}

void YGOUILayer::buttonCallback(CCObject* pSender, TouchEventType type) {
	static bool button_pressed = false;
	switch (type) {
	case TOUCH_EVENT_BEGAN:
		CCLOG("TOUCH_EVENT_BEGAN, pressed = %d", button_pressed);
	case TOUCH_EVENT_MOVED:
		CCLOG("TOUCH_EVENT_MOVED, pressed = %d", button_pressed);
		button_pressed = true;
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("TOUCH_EVENT_ENDED, pressed = %d", button_pressed);
		if (button_pressed) {
			onEvent(dynamic_cast<Button*>(pSender)->getTag());
			button_pressed = false;
		}
		break;
	case TOUCH_EVENT_CANCELED:
		CCLOG("TOUCH_EVENT_CANCELED, pressed = %d", button_pressed);
		button_pressed = false;
		break;
	}
}

Label* YGOUILayer::addNewLabel(Widget* container, int tag,
		const char* key) {
	std::string tempStr =
			XMLParser::sharedXMLParser()->getString(key)->getCString();
	Label* pLabel = dynamic_cast<Label*>(container->getChildByTag(tag));
	pLabel->setText(tempStr);
	return pLabel;
}

CCEditBox* YGOUILayer::addNewEditBox(Widget* container, int tag,
		const char* key) {
	const char* tempStr =
			XMLParser::sharedXMLParser()->getString(key)->getCString();
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(
			tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	CCEditBox* pEditBox = CCEditBox::create(pInnerContainer->getContentSize(),
			CCScale9Sprite::create("1.png"));
	pEditBox->setFont("fonts/arial.ttf", 28);
	pEditBox->setPlaceHolder(tempStr);
	pEditBox->setPlaceholderFontColor(ccBLACK);
	pEditBox->setPlaceholderFontSize(28);
	pEditBox->setReturnType(kKeyboardReturnTypeDone);
	pEditBox->setPosition(ccp(innerSize.width/2, innerSize.height/2));
	pEditBox->setTag(tag);
	pInnerContainer->addNode(pEditBox);
	return pEditBox;
}

DropDownList* YGOUILayer::addNewDropDownList(Widget* container, int tag,
		vector<CCString*>* strings) {
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(
			tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	DropDownList* pDrowdownList = DropDownList::create(
			(*strings->begin())->getCString(), strings, innerSize, 30);
	pDrowdownList->addClickObserver(this,
			callfuncO_selector(YGOUILayer::dropdownListCallback));
	pDrowdownList->setPosition(ccp(innerSize.width/2, innerSize.height/2));
	pDrowdownList->setTag(tag);
	pInnerContainer->addNode(pDrowdownList);
	return pDrowdownList;
}

CheckBox* YGOUILayer::addNewCheckBox(Widget* container, int tag) {
	CheckBox* pCheckBox = dynamic_cast<CheckBox*>(container->getChildByTag(tag));
	pCheckBox->setEnabled(true);
	pCheckBox->setTouchEnabled(true);
	return pCheckBox;
}

Button* YGOUILayer::addNewButton(Widget* container, int tag,
		const char* key) {
	std::string tempStr =
			XMLParser::sharedXMLParser()->getString(key)->getCString();
	Button* pButton = dynamic_cast<Button*>(container->getChildByTag(tag));
	pButton->setTitleText(tempStr);
	pButton->setScale9Enabled(true);
	pButton->setTouchEnabled(true);
	pButton->setPressedActionEnabled(true);
	return pButton;
}

} /* namespace ygo */
