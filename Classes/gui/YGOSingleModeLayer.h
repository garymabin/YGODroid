/*
 * YGOSingleModeLayer.h
 *
 *  Created on: 2014年1月22日
 *      Author: mabin
 */

#ifndef YGOSINGLEMODELAYER_H_
#define YGOSINGLEMODELAYER_H_

#include "cocos2d.h"

namespace ygo {

class YGOSingleModeLayer: public cocos2d::CCLayer {
public:
	YGOSingleModeLayer();
	virtual ~YGOSingleModeLayer();

	virtual bool init();
	CREATE_FUNC(YGOSingleModeLayer)
};

} /* namespace ygo */
#endif /* YGOSINGLEMODELAYER_H_ */
