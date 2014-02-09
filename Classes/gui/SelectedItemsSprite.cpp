/*
 * SelectedItemsSprite.cpp
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#include "SelectedItemsSprite.h"
USING_NS_CC;
using namespace std;

namespace ygo {

SelectedItemsSprite::SelectedItemsSprite() {
	m_pItemArray = CCArray::create();
	m_pItemArray->retain();
}

SelectedItemsSprite::~SelectedItemsSprite() {
	m_pItemArray->release();
}

SelectedItemsSprite* SelectedItemsSprite::create(const char* name, CCSize size, vector<CCString *>* strs, int textSize) {
	SelectedItemsSprite* pobView = new SelectedItemsSprite();
	pobView->m_itemSize = size;
	pobView->m_textSize = textSize;
	if (pobView && pobView->initWithFile(name) && pobView->setUpdateList(strs)) {
		pobView->autorelease();
		return pobView;
	}
	CC_SAFE_DELETE(pobView);
	return NULL;
}

inline void SelectedItemsSprite::addItem(
		const char* str, int i) {
	CCLabelTTF* label = CCLabelTTF::create(str, "Arial", m_textSize);
	label->setColor(ccBLACK);
	label->setAnchorPoint(CCPointZero);
	label->setPosition(ccp (0, (i - 1) * label->getContentSize().height));
	label->setTag(i);
	this->addChild(label);
	m_pItemArray->addObject(label);
	setContentSize(CCSizeMake(m_itemSize.width, m_itemSize.height * (i + 1)));
}

bool SelectedItemsSprite::setUpdateList(vector<CCString*>* strs) {
	bool isRet = false;
	do {
		this->setCascadeOpacityEnabled(true);
		vector<CCString*>::iterator iter;
		int i = 0;
		for (iter = strs->begin(); iter != strs->end(); iter++, i++) {
//			CCLOG("list str = %d", (*iter)->getCString());
			addItem((*iter)->getCString(), i);
		}
		isRet = true;
	} while (0);
	return isRet;
}

void SelectedItemsSprite::onEnter() {
	CCScale9Sprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, kCCMenuHandlerPriority - 1, true);
}

void SelectedItemsSprite::onExit() {
	CCScale9Sprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool SelectedItemsSprite::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	CCLOG("SelectedBoxSprite::ccTouchBegan");
	bool bRet = false;
	if (this->isVisible()) { //注意要在列表框可视化的情况下再作处理

		if (containsTouchLocation(touch)) {
			this->setVisible(true);

			CCLog("Touchable Sprite Began");

			CCPoint point = convertTouchToNodeSpace(touch);
			CCObject* obj = NULL;
			CCARRAY_FOREACH(m_pItemArray, obj) {
				CCSprite* sprite = dynamic_cast<CCSprite*>(obj);
				if (sprite->boundingBox().containsPoint(point)) {
					//这里表示点击到某一个list

					CCLog("tag = %d",sprite->getTag());

					//发送选择的那一行的tag,并且消失列表框
					CCSprite* selectedSprite = (CCSprite*) this->getChildByTag(
							sprite->getTag());
					CCBlink* blink = CCBlink::create(0.2, 3);
					selectedSprite->runAction(
							CCSequence::create(blink,
									CCCallFuncO::create(this,
											callfuncO_selector(SelectedItemsSprite::didSelectCallBack),
											(CCObject*) selectedSprite), NULL));

					break;
				}
			}

			bRet = true;
		} else {
			CCFadeOut* fadeout = CCFadeOut::create(0.3);
			this->runAction(fadeout);
			this->runAction(
					CCSequence::create(fadeout,
							CCCallFunc::create(this,
									callfunc_selector(SelectedItemsSprite::didSelectCallBack_1)),
							NULL));
		}
	}

	return bRet;
}

void SelectedItemsSprite::ccTouchMoved(CCTouch* touch, CCEvent* event) {
}

void SelectedItemsSprite::ccTouchEnded(CCTouch* touch, CCEvent* event) {
}

CCRect SelectedItemsSprite::rect() {
	CCSize size = getContentSize();
	return CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height);
}

bool SelectedItemsSprite::containsTouchLocation(CCTouch* touch) {
	CCRect my = rect();
	CCPoint p = convertTouchToNodeSpaceAR(touch);
	return my.containsPoint(p);
}

void SelectedItemsSprite::didSelectCallBack(CCObject* obj) {
	CCSprite* spri = (CCSprite*) obj;
	CCNotificationCenter::sharedNotificationCenter()->postNotification(
			MyNotification, obj);

	CCFadeOut* fadeout = CCFadeOut::create(0.3);
	this->runAction(fadeout);
	this->runAction(
			CCSequence::create(fadeout,
					CCCallFunc::create(this,
							callfunc_selector(SelectedItemsSprite::didSelectCallBack_1)),
					NULL));
}

void SelectedItemsSprite::pushBackItem(const char* str) {
	addItem(str, m_pItemArray->count());
}

int SelectedItemsSprite::indexOfText(const char* str) {
	CCObject* obj = NULL;
	int i = 0;
	CCARRAY_FOREACH(m_pItemArray, obj) {
		if (!strcmp(dynamic_cast<CCLabelTTF*>(obj)->getString(), str)) {
			return i;
		}
		i++;
	}
	return -1;
}

void SelectedItemsSprite::didSelectCallBack_1() {
	this->setVisible(false);
}

} /* namespace ygo */
