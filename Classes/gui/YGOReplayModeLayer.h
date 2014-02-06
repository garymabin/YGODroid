/*
 * YGOReplayModeLayer.h
 *
 *  Created on: 2014年1月22日
 *      Author: mabin
 */

#ifndef YGOREPLAYMODELAYER_H_
#define YGOREPLAYMODELAYER_H_

#include "cocos2d.h"

namespace ygo {

class YGOReplayModeLayer: public cocos2d::CCLayer {
public:
	virtual ~YGOReplayModeLayer();
	YGOReplayModeLayer();
	virtual bool init();

	CREATE_FUNC(YGOReplayModeLayer)
};

} /* namespace ygo */
#endif /* YGOREPLAYMODELAYER_H_ */
