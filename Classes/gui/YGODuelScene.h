/*
 * YGODuelScene.h
 *
 *  Created on: 2014年2月3日
 *      Author: mabin
 */

#ifndef YGODUELSCENE_H_
#define YGODUELSCENE_H_

#include "CommonGui.h"
#include "YGODuelFieldLayer.h"
#include "YGOBackgroundLayer.h"
#include "YGODuelFieldFrame.h"

namespace ygo {

class YGODuelScene: public cocos2d::CCScene {
public:
	YGODuelScene();
	virtual ~YGODuelScene();
	virtual bool init();
	CREATE_FUNC(YGODuelScene)
private:
	YGODuelFieldLayer* m_pDuelField;
	YGODuelFieldFrame* m_pDuelFrame;
};

} /* namespace ygo */
#endif /* YGODUELSCENE_H_ */
