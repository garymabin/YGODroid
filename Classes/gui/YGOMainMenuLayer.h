/*
 * YGOMainMenuLayer.h
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#ifndef YGOMAINMENULAYER_H_
#define YGOMAINMENULAYER_H_

#include "cocos2d.h"
#include "YGOMainScene.h"
#include "CCMenuItemImageFont.h"
#include "XMLParser.h"

namespace ygo {

class YGOMainMenuLayer: public cocos2d::CCLayerColor {
public:
	YGOMainMenuLayer();
	virtual ~YGOMainMenuLayer();
	virtual bool init();
	CREATE_FUNC(YGOMainMenuLayer)
};

} /* namespace ygo */
#endif /* YGOMAINMENULAYER_H_ */
