/*
 * YGODuelScene.cpp
 *
 *  Created on: 2014年2月3日
 *      Author: mabin
 */

#include "YGODuelScene.h"

USING_NS_CC;

namespace ygo {

YGODuelScene::YGODuelScene() {
	// TODO Auto-generated constructor stub
}

YGODuelScene::~YGODuelScene() {
	// TODO Auto-generated destructor stub
}

bool YGODuelScene::init() {
	if (!CCScene::init()) {
		return false;
	}
	YGOBackgroundLayer* layer1 = YGOBackgroundLayer::create();
//	m_pDuelField = YGODuelFieldLayer::create();
	m_pDuelFrame = YGODuelFieldFrame::create();
	this->addChild(layer1, 0);
//	this->addChild(m_pDuelField, 1);
	this->addChild(m_pDuelFrame, 2);

	return true;
}

} /* namespace ygo */
