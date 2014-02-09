/*
 * YGODuelField.cpp
 *
 *  Created on: 2014年2月8日
 *      Author: mabin
 */

#include "YGODuelField.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

YGODuelField::YGODuelField() {
	// TODO Auto-generated constructor stub

}

YGODuelField::~YGODuelField() {
	// TODO Auto-generated destructor stub
}

bool YGODuelField::init() {
	bool bRet = false;
	do {
		if (!Widget::init()) {
			return false;
		}
		Layout * layer =
				dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile(
						"ygocore_duel_field.json"));
		layer->setPosition(CCPointZero);
		layer->setTouchEnabled(false);
		addChild(layer);
		m_pContent = dynamic_cast<Widget*>(layer->getChildByTag(
		DUEL_FIELD_IMAGE_DUEL_FIELD));
		CC_BREAK_IF(!layer);

		//初始化区域
		m_pExtra1 = dynamic_cast<Widget*>(m_pContent->getChildByTag(DUEL_FIELD_PANEL_EXTRA_1));
		CCCamera* camera = getCamera();
		float x = 0, y = 0, z = 0;
		camera->getCenterXYZ(&x, &y, &z);
		CCLOG("camera x =%f, y=%f, z=%f", x, y, z);
//	camera->setCenterXYZ(x, y + 0.0001, z + 0.0001);
//	camera->setEyeXYZ(x, y - 60, z + 110);
		bRet = true;
	} while (0);
	return bRet;
}

void YGODuelField::onEnter() {
	Layout::onEnter();
//	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void YGODuelField::onExit() {
	Layout::onExit();
//	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
}

bool YGODuelField::onTouchBegan(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	CCLOG("Duel Field touched in");
	bool bRet = true;
	if (bRet) {
		CCPoint point = convertToNodeSpace(pTouch->getLocation());
		CCLOG("Duel Field touched in: x = %f, y = %f", point.x, point.y);
		CCArray* pItemsArray = m_pContent->getChildren();
		CCObject* item = NULL;
		CCARRAY_FOREACH(pItemsArray, item) {
			Widget* widget = dynamic_cast<Widget*>(item);
			if (widget->hitTest(point)) {
				CCBlink* blink = CCBlink::create(2.0, 2);
				widget->runAction(blink);
			}
		}
	}
	return false;
}

void YGODuelField::onTouchMoved(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
}

void YGODuelField::onTouchEnded(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
}

void YGODuelField::onTouchCancelled(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
}
