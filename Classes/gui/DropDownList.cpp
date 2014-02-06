/*
 * DropDownList.cpp
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#include "DropDownList.h"
USING_NS_CC;
using namespace std;
using namespace extension;

namespace ygo {

DropDownList::DropDownList() :
		m_pLabel(NULL) {
}

DropDownList::~DropDownList() {
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,
			MyNotification);
	m_pDropDownListItem->release();
	m_pLabel->release();
}

DropDownList* DropDownList::create(const char* title,
		vector<CCString*>* strs, CCSize size, int textSize) {
	return DropDownList::create("1.png",
			"1.png", title, strs, size, textSize);
}

DropDownList* DropDownList::create(const char * defaultFn,
		const char * pressedFn, const char * title, vector<CCString*>* strs,
		CCSize size, int textSize) {
	DropDownList* ddlSprite = new DropDownList();
	if (ddlSprite && ddlSprite->init(defaultFn, pressedFn, title, strs, size, textSize)) {
		ddlSprite->autorelease();
		return ddlSprite;
	}
	CC_SAFE_DELETE(ddlSprite);
	return NULL;
}

bool DropDownList::init(const char * defaultFn, const char * pressedFn,
		const char * title, vector<CCString*>* strs, CCSize size, int textSize) {
	if (!CCSprite::init()) {
		return false;
	}
	do {
		setContentSize(size);
		CCScale9Sprite* defaultSprite = CCScale9Sprite::create(defaultFn);
		defaultSprite->setContentSize(size);
		CCScale9Sprite* pressedSprite = CCScale9Sprite::create(pressedFn);
		pressedSprite->setContentSize(size);
		CCMenuItemSprite* itemImage = CCMenuItemSprite::create((CCNode*)defaultSprite, (CCNode*)pressedSprite, this, menu_selector(DropDownList::dropDownListCallBack));
		itemImage->setTag(1);
		CCMenu* menu = CCMenu::create(itemImage, NULL);
		menu->setPosition(size.width/2, size.height/2);
		this->addChild(menu);
		m_pLabel = CCLabelTTF::create(title, "Arial", textSize);
		m_pLabel->retain();
		m_pLabel->setColor(ccBLACK);
		m_pLabel->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(m_pLabel);
//		bRet = this->initWithLabelAndBackgroundSprite(label, defaultSprite);
//		this->setBackgroundSpriteForState(pressedSprite,
//				CCControlStateHighlighted);
//
//		this->addTargetWithActionForControlEvent(this,
//				cccontrol_selector(DropDownList::dropDownListCallBack),
//				CCControlEventTouchDown);

		m_pDropDownListItem = SelectedBoxSprite::create(
				"list_item_bg.png", size, strs, textSize);
		m_pDropDownListItem->retain();
		m_pDropDownListItem->setAnchorPoint( ccp(0.5, 0.5));
		m_pDropDownListItem->setPosition(size.width/2, 0 - strs->size() * size.height / 2.0f);
		this->addChild(m_pDropDownListItem, 0);
		m_pDropDownListItem->setVisible(false);

	} while (0);
	return true;
}

void DropDownList::dropDownListCallBack(CCObject* pObject,
		CCControlEvent event) {
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(DropDownList::myNotificationFunc),
			MyNotification, NULL);
	if (!m_pDropDownListItem->isVisible()) {
		m_pDropDownListItem->setVisible(true);
		CCFadeIn* fadeIn = CCFadeIn::create(0.3);
		m_pDropDownListItem->runAction(fadeIn);
	}
}

void DropDownList::addClickObserver(CCObject* target, SEL_CallFuncO func) {
	m_pTarget = target;
	m_pFnClicked = func;
}

void DropDownList::myNotificationFunc(CCObject* obj) {
	CCLabelTTF* pLabel = dynamic_cast<CCLabelTTF*>(obj);
	//	CCString* string = CCString::createWithData((unsigned char const *)(str), strlen(str));
	if (strcmp(m_pLabel->getString(), pLabel->getString())) {
		m_pLabel->setString(pLabel->getString());
		if (m_pTarget) {
			(m_pTarget->*m_pFnClicked)(this);
		}
	}
}

} /* namespace ygo */
