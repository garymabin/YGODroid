/*
 * YGOImageManager.h
 *
 *  Created on: 2014年2月2日
 *      Author: mabin
 */

#ifndef YGOIMAGEMANAGER_H_
#define YGOIMAGEMANAGER_H_

#include "cocos2d.h"
USING_NS_CC;

#define IMAGE_COVER "textures/cover.jpg"
#define IMAGE_UNKNOWN "textures/unknown.jpg"
#define IMAGE_ACT "textures/act.png"
#define IMAGE_ATTACK "textures/attack.png"
#define IMAGE_CHAIN "textures/chain.png"
#define IMAGE_NEGATED "textures/negated.png"
#define IMAGE_NUMBER "textures/number.png"
#define IMAGE_LPBAR "textures/lp.png"
#define IMAGE_LPFRAME "textures/lpf.png"
#define IMAGE_MASK "textures/mask.png"
#define IMAGE_EQUIP "textures/equip.png"
#define IMAGE_TARGET "textures/target.png"
#define IMAGE_LIM "textures/lim.png"
#define IMAGE_HAND_0 "textures/f1.jpg"
#define IMAGE_HAND_1 "textures/f2.jpg"
#define IMAGE_HAND_2 "textures/f3.jpg"
#define IMAGE_BACKGROUND "textures/bg.jpg"
#define IMAGE_FIELD "textures/field.png"

namespace ygo {

class YGOImageManager {
public:
	YGOImageManager();
	~YGOImageManager();
	static YGOImageManager* sharedImageManager();
	CCTexture2D* getThumbImage(int code);
	CCTexture2D* getImage(int code);
protected:
	void init();
	CCTextureCache* m_pCache;
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageCover, CoverTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageUnknown, UnknownTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageAct, ActTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageAttack, AttackTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageChain, ChainTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageNegated, NegatedTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageNumber,NumberTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageLpBar, LpBarTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageLpFrame, LpFrameTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageMask, MaskTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageEquip, EquipTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageTarget, TargetTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageLim, LimTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageHand0, Hand0Texture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageHand1, Hand1Texture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageHand2, Hand2Texture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageBackground, BackgroundTexture);
	CC_SYNTHESIZE_READONLY(CCTexture2D *, m_pImageField, FieldTexture);
};

} /* namespace ygo */
#endif /* YGOIMAGEMANAGER_H_ */
