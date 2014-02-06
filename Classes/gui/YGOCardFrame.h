/*
 * YGOCardFrame.h
 *
 *  Created on: 2014年2月1日
 *      Author: mabin
 */

#ifndef YGOCARDFRAME_H_
#define YGOCARDFRAME_H_

#include "cocos2d.h"

USING_NS_CC;

namespace ygo {

class YGOCardFrame: public cocos2d::CCNode {
public:
	YGOCardFrame();
	virtual ~YGOCardFrame();
	virtual void draw();
	virtual bool initWithSize(CCSize internalSize, float frameSize);
	static YGOCardFrame* create(CCSize internalSize, float frameSize);
private:
	CCSize mInternalSize;
	float mFrameSize;
};

} /* namespace ygo */
#endif /* YGOCARDFRAME_H_ */
