/*
 * YGOCardCell.cpp
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#include "YGOCardCell.h"

USING_NS_CC;

namespace ygo {

YGOCardCell::YGOCardCell() :
		m_pSprite(NULL)/*, m_pRender(NULL)*/{
	// TODO Auto-generated constructor stub
	m_requestSize = CCSizeZero;
	m_pCoverTexture = YGOImageManager::sharedImageManager()->getCoverTexture();
	CC_SAFE_RETAIN(m_pCoverTexture);
}

YGOCardCell::~YGOCardCell() {
	// TODO Auto-generated destructor stub
	m_pSprite->release();
	CC_SAFE_RELEASE_NULL(m_pCoverTexture);
	CC_SAFE_RELEASE_NULL(m_pTexture);
}

bool YGOCardCell::initWithCard(code_pointer card, bool isThumbNail) {
	if (!Widget::init()) {
		return false;
	}
	m_pCard = card;
	m_isThumbnail = isThumbNail;
	if (m_isThumbnail) {
		m_pTexture = YGOImageManager::sharedImageManager()->getThumbImage(
				m_pCard->first);
	} else {
		m_pTexture = YGOImageManager::sharedImageManager()->getImage(
				m_pCard->first);
	}
	setAnchorPoint(ccp (0.5, 0.5));
	m_pTexture->retain();
	m_pSprite = CCSprite::createWithTexture(m_pTexture);
	m_pSprite->retain();
	CCSize size = m_pSprite->getContentSize();
	if (!m_requestSize.equals(CCSizeZero)) {
		m_pSprite->setScaleX(m_requestSize.width / size.width);
		m_pSprite->setScaleY(m_requestSize.height / size.height);
	} else {
		m_requestSize = size;
	}
	m_pRender = CCRenderTexture::create(m_requestSize.width, m_requestSize.height);
	m_pRender->setPosition(ccp(m_requestSize.width/2, m_requestSize.height/2));
	m_pRender->begin();
	m_pSprite->setPosition(ccp(m_requestSize.width/2, m_requestSize.height/2));
	m_pSprite->visit();
	m_pRender->end();
	m_pRender->removeChild(m_pSprite);
	this->addNode(m_pRender);
	return true;
}

YGOCardCell* YGOCardCell::create(code_pointer card, bool isThumbNail) {
	YGOCardCell* pCell = new YGOCardCell();
	if (pCell->initWithCard(card, isThumbNail)) {
		pCell->autorelease();
		return pCell;
	} else {
		CC_SAFE_DELETE(pCell);
	}
	return NULL;
}

void YGOCardCell::resetWithData(code_pointer card) {
	if (m_pCard == card) {
		return;
	}
	m_pCard = card;
	CC_SAFE_RELEASE_NULL(m_pTexture);
	if (m_isThumbnail) {
		m_pTexture = YGOImageManager::sharedImageManager()->getThumbImage(
				m_pCard->first);
	} else {
		m_pTexture = YGOImageManager::sharedImageManager()->getImage(m_pCard->first);
	}
	m_requestSize = m_pTexture->getContentSize();
	m_pRender->setContentSize(m_requestSize);
	m_pRender->setPosition(ccp(m_requestSize.width/2, m_requestSize.height/2));
	m_pSprite->setTexture(m_pTexture);
	m_pRender->beginWithClear(0,0,0,0);
	m_pSprite->setPosition( ccp(m_requestSize.width/2, m_requestSize.height/2));
	m_pSprite->visit();
	m_pRender->end();
}

bool YGOCardCell::initWithCard(code_pointer card, CCSize size,
		bool isThumbNail) {
	m_requestSize = size;
	return initWithCard(card, isThumbNail);
}

YGOCardCell* YGOCardCell::create(code_pointer card, CCSize size,
		bool isThumbNail) {
	YGOCardCell* pCell = new YGOCardCell();
	if (pCell->initWithCard(card, size, isThumbNail)) {
		pCell->autorelease();
		return pCell;
	} else {
		CC_SAFE_DELETE(pCell);
	}
	return NULL;
}

void YGOCardCell::showCover() {
	CCSize coverSize = m_pCoverTexture->getContentSize();
	CCLOG("m_requestSize.width = %f, coverSize.width = %f", m_requestSize.width, coverSize.width);
	float scaleFactorX = m_requestSize.width / coverSize.width;
	float scaleFactotY = m_requestSize.height / coverSize.height;

	m_pRender->setContentSize(CCSizeMake(m_requestSize.height, m_requestSize.width));
	m_pSprite->setTexture(m_pCoverTexture);
	m_pRender->beginWithClear(0,0,0,0);
//	m_pSprite->setScaleX(scaleFactorX);
//	m_pSprite->setScaleY(scaleFactotY);
	m_pSprite->setRotation(90);
	m_pSprite->setPosition(ccp(m_requestSize.height/2, m_requestSize.width/2));
	m_pSprite->visit();
	m_pRender->end();
	m_pSprite->setRotation(0);
}

void YGOCardCell::showNormal() {
	setContentSize(m_requestSize);
	removeNode(m_pRender);
	m_pRender = CCRenderTexture::create(m_requestSize.width, m_requestSize.height);
	m_pRender->setPosition(m_requestSize.width, m_requestSize.height);
	m_pRender->begin();
	m_pSprite->setTexture(m_pTexture);
	m_pSprite->setPosition(ccp(m_requestSize.width/2, m_requestSize.height/2));
	m_pSprite->visit();
	addNode(m_pRender);
	m_pRender->end();
}

void YGOCardCell::showScaleBy(float scaleBy) {
	float currentScale = m_pSprite->getScaleX();
	removeNode(m_pRender);
	setContentSize(CCSizeMake(m_requestSize.width * scaleBy, m_requestSize.height * scaleBy));
	m_pRender = CCRenderTexture::create(m_requestSize.width * scaleBy, m_requestSize.height * scaleBy);
	m_pRender->setPosition(m_requestSize.width * scaleBy / 2 , m_requestSize.height * scaleBy / 2);
	m_pRender->begin();
	m_pSprite->setTexture(m_pTexture);
	m_pSprite->setPosition(ccp(m_requestSize.width * scaleBy / 3*2, m_requestSize.height * scaleBy *2/3));
	m_pSprite->setScale(currentScale * scaleBy);
	m_pSprite->visit();
	m_pRender->end();
	addNode(m_pRender);
	m_pSprite->setScale(currentScale);
}

} /* namespace ygo */
