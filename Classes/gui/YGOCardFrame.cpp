/*
 * YGOCardFrame.cpp
 *
 *  Created on: 2014年2月1日
 *      Author: mabin
 */

#include "YGOCardFrame.h"

namespace ygo {

YGOCardFrame::YGOCardFrame() {
	// TODO Auto-generated constructor stub

}

YGOCardFrame::~YGOCardFrame() {
	// TODO Auto-generated destructor stub
}

void YGOCardFrame::draw() {
	glLineWidth(mFrameSize);
	ccDrawColor4B(255, 255, 255, 255);
	CCPoint orgPoint = getPosition();
	ccDrawRect(ccp(orgPoint.x - mFrameSize, orgPoint.y - mFrameSize), ccp((orgPoint.x + mInternalSize.width + mFrameSize), (orgPoint.y + mInternalSize.height + mFrameSize)));
}

bool YGOCardFrame::initWithSize(CCSize internalSize, float frameSize) {
	if (!CCNode::init()) {
		return false;
	}
	setAnchorPoint(CCPointZero);
	setPosition(CCPointZero);
	mInternalSize = internalSize;
	mFrameSize = frameSize;
	return true;
}

YGOCardFrame* YGOCardFrame::create(CCSize internalSize, float frameSize) {
	YGOCardFrame* pFrame = new YGOCardFrame();
	pFrame->autorelease();
	if (pFrame->initWithSize(internalSize, frameSize)) {
		return pFrame;
	}
	return NULL;
}

} /* namespace ygo */
