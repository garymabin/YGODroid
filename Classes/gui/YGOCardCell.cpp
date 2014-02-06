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
}

YGOCardCell::~YGOCardCell() {
	// TODO Auto-generated destructor stub
	m_pSprite->release();
}

bool YGOCardCell::initWithCard(code_pointer card, bool isThumbNail) {
	if (!Widget::init()) {
		return false;
	}
	m_pCard = card;
	CCTexture2D* pTexture = NULL;
	m_isThumbnail = isThumbNail;
	if (m_isThumbnail) {
		pTexture = YGOImageManager::sharedImageManager()->getThumbImage(
				m_pCard->first);
	} else {
		pTexture = YGOImageManager::sharedImageManager()->getImage(
				m_pCard->first);
	}
	m_pSprite = CCSprite::createWithTexture(pTexture);
	m_pSprite->retain();
	CCSize size = m_pSprite->getContentSize();
	if (!m_requestSize.equals(CCSizeZero)) {
		m_pSprite->setScaleX(m_requestSize.width / size.width);
		m_pSprite->setScaleY(m_requestSize.height / size.height);
	} else {
		m_requestSize = size;
	}
	this->setAnchorPoint(CCPointZero);
	this->setAnchorPoint(CCPointZero);
	m_pSprite->setAnchorPoint(CCPointZero);
	m_pSprite->setPosition(CCPointZero);
	this->addNode(m_pSprite);
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
	CCTexture2D* image = m_pSprite->getTexture();
	if (m_isThumbnail) {
		image = YGOImageManager::sharedImageManager()->getThumbImage(
				m_pCard->first);
	} else {
		image = YGOImageManager::sharedImageManager()->getImage(m_pCard->first);
	}
	m_pSprite->setTexture(image);
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

} /* namespace ygo */
