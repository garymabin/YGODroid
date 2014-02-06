/*
 * YGOImageManager.cpp
 *
 *  Created on: 2014年2月2日
 *      Author: mabin
 */

#include "YGOImageManager.h"

USING_NS_CC;

namespace ygo {

static YGOImageManager* s_pImageManager = NULL;

YGOImageManager::YGOImageManager() {
	m_pCache = CCTextureCache::sharedTextureCache();
}

YGOImageManager::~YGOImageManager() {
	m_pImageCover->release();
	m_pImageUnknown->release();
	m_pImageAct->release();
	m_pImageAttack->release();
	m_pImageChain->release();
	m_pImageNegated->release();
	m_pImageNumber->release();
	m_pImageLpBar->release();
	m_pImageLpFrame->release();
	m_pImageMask->release();
	m_pImageEquip->release();
	m_pImageTarget->release();
	m_pImageLim->release();
	m_pImageHand0->release();
	m_pImageHand1->release();
	m_pImageHand2->release();
	m_pImageBackground->release();
	m_pImageField->release();
}

YGOImageManager* YGOImageManager::sharedImageManager() {
	if (!s_pImageManager) {
		s_pImageManager = new YGOImageManager();
		s_pImageManager->init();
	}
	return s_pImageManager;
}

CCTexture2D* YGOImageManager::getThumbImage(int code) {
	if (code == 0)
		return m_pImageUnknown;
	char file[256];
	sprintf(file, "pics/thumbnail/%d.jpg", code);
	CCTexture2D* img = m_pCache->addImage(file);
	if (img == NULL) {
		return m_pImageUnknown;
	} else {
		return img;
	}
}

CCTexture2D* YGOImageManager::getImage(int code) {
	if (code == 0)
		return m_pImageUnknown;
	char file[256];
	sprintf(file, "pics/%d.jpg", code);
	CCTexture2D* img = m_pCache->addImage(file);
	if (img == NULL) {
		return m_pImageUnknown;
	} else {
		return img;
	}
}

void YGOImageManager::init() {
	m_pImageCover = m_pCache->addImage(IMAGE_COVER);
	CC_SAFE_RETAIN(m_pImageCover);
	m_pImageUnknown= m_pCache->addImage(IMAGE_UNKNOWN);
	CC_SAFE_RETAIN(m_pImageUnknown);
	m_pImageAct = m_pCache->addImage(IMAGE_ACT);
	CC_SAFE_RETAIN(m_pImageAct);
	m_pImageAttack = m_pCache->addImage(IMAGE_ATTACK);
	CC_SAFE_RETAIN(m_pImageAttack);
	m_pImageChain = m_pCache->addImage(IMAGE_CHAIN);
	CC_SAFE_RETAIN(m_pImageChain);
	m_pImageNegated = m_pCache->addImage(IMAGE_NEGATED);
	CC_SAFE_RETAIN(m_pImageNegated);
	m_pImageNumber = m_pCache->addImage(IMAGE_NUMBER);
	CC_SAFE_RETAIN(m_pImageNumber);
	m_pImageLpBar = m_pCache->addImage(IMAGE_LPBAR);
	CC_SAFE_RETAIN(m_pImageLpBar);
	m_pImageLpFrame = m_pCache->addImage(IMAGE_LPFRAME);
	CC_SAFE_RETAIN(m_pImageLpFrame);
	m_pImageMask = m_pCache->addImage(IMAGE_MASK);
	CC_SAFE_RETAIN(m_pImageMask);
	m_pImageEquip = m_pCache->addImage(IMAGE_EQUIP);
	CC_SAFE_RETAIN(m_pImageEquip);
	m_pImageTarget = m_pCache->addImage(IMAGE_TARGET);
	CC_SAFE_RETAIN(m_pImageTarget);
	m_pImageLim = m_pCache->addImage(IMAGE_LIM);
	CC_SAFE_RETAIN(m_pImageLim);
	m_pImageHand0 = m_pCache->addImage(IMAGE_HAND_0);
	CC_SAFE_RETAIN(m_pImageHand0);
	m_pImageHand1 = m_pCache->addImage(IMAGE_HAND_1);
	CC_SAFE_RETAIN(m_pImageHand1);
	m_pImageHand2 = m_pCache->addImage(IMAGE_HAND_2);
	CC_SAFE_RETAIN(m_pImageHand2);
	m_pImageBackground = m_pCache->addImage(IMAGE_BACKGROUND);
	CC_SAFE_RETAIN(m_pImageBackground);
	m_pImageField = m_pCache->addImage(IMAGE_FIELD);
	CC_SAFE_RETAIN(m_pImageField);
}

} /* namespace ygo */
