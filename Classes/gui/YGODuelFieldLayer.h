/*
 * YGODuelFieldLayer.h
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#ifndef YGODUELFIELDLAYER_H_
#define YGODUELFIELDLAYER_H_

#include "CommonGui.h"
#include "YGOImageManager.h"

namespace ygo {

class YGODuelFieldLayer: public cocos2d::CCLayer {
public:
	YGODuelFieldLayer();
	virtual ~YGODuelFieldLayer();
	virtual bool init();
	virtual void update(float delta);
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(YGODuelFieldLayer)
	float getCardFieldHeight() {
		return m_scale * CARD_FEILD_ORIG_HEIGHT;
	}
private:
	float m_z;
	CC_SYNTHESIZE_READONLY(float, m_scale, FieldScale);
};

} /* namespace ygo */
#endif /* YGODUELFIELDLAYER_H_ */
