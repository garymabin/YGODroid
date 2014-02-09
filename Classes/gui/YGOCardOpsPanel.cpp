/*
 * YGOCardOpsPanel.cpp
 *
 *  Created on: 2014年2月7日
 *      Author: mabin
 */

#include "YGOCardOpsPanel.h"
using namespace std;

namespace ygo {

YGOCardOpsPanel::YGOCardOpsPanel() {
	// TODO Auto-generated constructor stub
	m_pItemArray = CCArray::create();
	m_pItemArray->retain();
	m_itemSize = CCSize(150, 50);
}

YGOCardOpsPanel::~YGOCardOpsPanel() {
	// TODO Auto-generated destructor stub
	m_pItemArray->release();
}

YGOCardOpsPanel* YGOCardOpsPanel::createWithItems(const char* file,
		vector<CCString*>* strs, int textSize) {
	YGOCardOpsPanel* popView = new YGOCardOpsPanel();
	popView->m_textSize = textSize;
	if (popView && popView->initWithFile(file)
			&& popView->setUpdateList(strs)) {
		popView->autorelease();
		return popView;
	}
	CC_SAFE_DELETE(popView);
	return NULL;
}

bool YGOCardOpsPanel::setUpdateList(std::vector<CCString*>* strs) {
	bool isRet = false;
	do {
		this->setCascadeOpacityEnabled(true);
		vector<CCString*>::iterator iter;
		int i = 0;
		for (iter = strs->begin(); iter != strs->end(); iter++, i++) {
			addItem((*iter)->getCString(), i);
		}
		isRet = true;
	} while (0);
	return isRet;
}


inline void YGOCardOpsPanel::addItem(
		const char* str, int i) {
	CCLabelTTF* label = CCLabelTTF::create(str, "Arial", m_textSize);
	label->setColor(ccBLACK);
	label->setAnchorPoint(CCPointZero);
	label->setPosition(ccp (0, i* label->getContentSize().height));
	label->setTag(i);
	this->addChild(label);
	m_pItemArray->addObject(label);
	setContentSize(CCSizeMake(m_itemSize.width, m_itemSize.height * (i + 1)));
}

void YGOCardOpsPanel::onEnter() {
	CCScale9Sprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, kCCMenuHandlerPriority - 1, true);
}

void YGOCardOpsPanel::onExit() {
	CCScale9Sprite::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool YGOCardOpsPanel::ccTouchBegan(CCTouch* touch, CCEvent* event) {
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

					CCLog("tag = %d", sprite->getTag());

					//发送选择的那一行的tag,并且消失列表框
					CCSprite* selectedSprite = (CCSprite*) this->getChildByTag(
							sprite->getTag());
					CCTintTo* tint = CCTintTo::create(0.2, (GLubyte)0, (GLubyte)0, (GLubyte)255);
					selectedSprite->runAction(
							CCSequence::create(tint,
									CCCallFuncO::create(this,
											callfuncO_selector(YGOCardOpsPanel::didSelectCallBack),
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
									callfunc_selector(YGOCardOpsPanel::didSelectCallBack_1)),
							NULL));
		}
	}

	return bRet;
}

void YGOCardOpsPanel::ccTouchMoved(CCTouch* touch, CCEvent* event) {
}

void YGOCardOpsPanel::ccTouchEnded(CCTouch* touch, CCEvent* event) {
}

CCRect YGOCardOpsPanel::rect() {
	CCSize size = getContentSize();
	return CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height);
}

bool YGOCardOpsPanel::containsTouchLocation(CCTouch* touch) {
	CCRect my = rect();
	CCPoint p = convertTouchToNodeSpaceAR(touch);
	return my.containsPoint(p);
}

void YGOCardOpsPanel::addItemSelectedListener(CCObject* target,
		SEL_CallFuncND callback) {
	if (target != m_pItemSelectedTarget) {
		m_pItemSelectedTarget == target;
		m_pFnItemSelected = callback;
	}
}

void YGOCardOpsPanel::didSelectCallBack(CCObject* obj) {
	CCLabelTTF* label = (CCLabelTTF*) obj;
	if (m_pItemSelectedTarget) {
		(m_pItemSelectedTarget->*m_pFnItemSelected)((CCNode*)obj,
				(void *) CCStringMake(label->getString()));
			}
	CCFadeOut* fadeout = CCFadeOut::create(0.3);
	this->runAction(fadeout);
	this->runAction(
			CCSequence::create(fadeout,
					CCCallFunc::create(this,
							callfunc_selector(YGOCardOpsPanel::didSelectCallBack_1)),
					NULL));
}

void YGOCardOpsPanel::didSelectCallBack_1() {
	this->setVisible(false);
}

} /* namespace ygo */
