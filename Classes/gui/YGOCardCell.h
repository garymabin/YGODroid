/*
 * YGOCardCell.h
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#ifndef YGOCARDCELL_H_
#define YGOCARDCELL_H_

#include "CommonGui.h"
#include <GLES2/gl2.h>
#include "YGOClientCard.h"
#include "YGOImageManager.h"

namespace ygo {

class GridLayoutParameter: public cocos2d::gui::LayoutParameter {
public:
	GridLayoutParameter(): m_cellX(0), m_cellY(0) {
	}
	virtual ~GridLayoutParameter() {
	}
	virtual bool init() {
		return true;
	}
	CREATE_FUNC(GridLayoutParameter);
	CC_SYNTHESIZE(int, m_cellX, CellX);
	CC_SYNTHESIZE(int, m_cellY, CellY);
};

class YGOCardCell: public cocos2d::gui::Widget {
public:
	YGOCardCell();
	virtual ~YGOCardCell();
	virtual bool initWithCard(code_pointer card, bool isThumbNail = true);
	virtual bool initWithCard(code_pointer card, CCSize size, bool isThumbNail = true);
	static YGOCardCell* create(code_pointer card, bool isThumbNail = true);
	static YGOCardCell* create(code_pointer card, CCSize size, bool isThumbNail = true);
	void resetWithData(code_pointer card);
	void showCover();
	void showNormal();
	void showScaleBy(float scaleBy);
protected:
	bool m_bIsThumbnail;
	float m_scaleX;
	float m_scaleY;
	CCTexture2D* m_pCoverTexture;
	CCTexture2D* m_pTexture;
	CC_SYNTHESIZE_READONLY(CCSize, m_requestSize, RequestSize);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*, m_pSprite, Sprite);
//	CC_SYNTHESIZE_READONLY(cocos2d::CCRenderTexture*, m_pRender, Render);
	CC_SYNTHESIZE_READONLY(code_pointer, m_pCard, Card);
};

} /* namespace ygo */
#endif /* YGOCARDCELL_H_ */
