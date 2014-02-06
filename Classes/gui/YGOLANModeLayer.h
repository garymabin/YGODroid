/*
 * YGOLANModeLayer.h
 *
 *  Created on: 2014年1月22日
 *      Author: mabin
 */

#ifndef YGOLANMODELAYER_H_
#define YGOLANMODELAYER_H_

#include "CommonGui.h"
#include "XMLParser.h"
#include "YGOMainScene.h"
#include "YGOCreateServerLayer.h"

namespace ygo {

class YGOLANModeLayer: public cocos2d::CCLayerColor {
public:
	YGOLANModeLayer();
	virtual ~YGOLANModeLayer();
	virtual bool init();
	void buttonLanModeCallback(CCObject* pSender,
			cocos2d::gui::TouchEventType type);
	CREATE_FUNC(YGOLANModeLayer)
	void onEvent(int tag);
private:
	cocos2d::gui::TouchGroup* m_pWidgetContainer;
};

} /* namespace ygo */
#endif /* YGOLANMODELAYER_H_ */
