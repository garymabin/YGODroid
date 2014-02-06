/*
 * YGOMain Scene.h
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#ifndef YGOMAINSCENE_H_
#define YGOMAINSCENE_H_

#include "CommonGui.h"
#include "YGOBackgroundLayer.h"
#include "YGOMainMenuLayer.h"
#include "YGOReplayModeLayer.h"
#include "YGOSingleModeLayer.h"
#include "YGOLANModeLayer.h"
#include "YGODeckEditLayer.h"

namespace ygo {

class YGOMainScene: public cocos2d::CCScene {
public:
	YGOMainScene();
	virtual ~YGOMainScene();
	static cocos2d::CCScene* scene();
	void menuLANModeCallback(CCObject* pSender);
	void menuSingleModeCallback(CCObject* pSender);
	void menuReplayModeCallback(CCObject* pSender);
	void menuDeckEditModeCallback(CCObject* pSender);
	void menuQuitCallback(CCObject* pSender);
	virtual bool init();
	CREATE_FUNC(YGOMainScene)
};

}  // namespace ygo



#endif /* YGOMAINSCENE_H_ */
