/*
 * YGODuelFieldLayer.cpp
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#include "YGODuelFieldLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

YGODuelFieldLayer::YGODuelFieldLayer() {
	// TODO Auto-generated constructor stub
	m_z = 0.0;
	m_scale = 1.0;

}

YGODuelFieldLayer::~YGODuelFieldLayer() {
	// TODO Auto-generated destructor stub
}

bool YGODuelFieldLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCTexture2D* pTexture =
			YGOImageManager::sharedImageManager()->getFieldTexture();
	CCSprite* pSprite = CCSprite::createWithTexture(pTexture);
	CCSize size = pSprite->getContentSize();
	m_scale = visibleSize.height / size.height;
	pSprite->setScale(m_scale);
	CCLOG("size width =%f, height=%f", size.width, size.height);
	pSprite->setPosition(ccp(visibleSize.width - size.width + origin.x - 180, visibleSize.height/2 + origin.y));
//	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	this->addChild(pSprite, 1);
	CCCamera* camera = getCamera();
	float x=0, y=0, z=0;
	camera->getEyeXYZ(&x, &y, &z);
	CCLOG("camera x =%f, y=%f, z=%f", x, y, z);
	camera->setEyeXYZ(0, y -60, z + 120);
	return true;
}

void YGODuelFieldLayer::update(float delta) {
	m_z +=  delta * 100;
	CCCamera* camera = getCamera();
	camera->setEyeXYZ(0, 0, m_z);
}

void YGODuelFieldLayer::onEnter() {
	CCLayer::onEnter();
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection3D);
}

void YGODuelFieldLayer::onExit() {
	CCLayer::onExit();
	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D);
}

} /* namespace ygo */
