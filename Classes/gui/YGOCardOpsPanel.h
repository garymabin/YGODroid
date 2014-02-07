/*
 * YGOCardOpsPanel.h
 *
 *  Created on: 2014年2月7日
 *      Author: mabin
 */

#ifndef YGOCARDOPSPANEL_H_
#define YGOCARDOPSPANEL_H_

#include "CommonGui.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

class YGOCardOpsPanel: public Widget {
public:
	YGOCardOpsPanel();
	virtual ~YGOCardOpsPanel();
	static YGOCardOpsPanel* createWithPosition(CCPoint point, CCArray* items);
protected:
	CCRenderTexture* m_render;

};

} /* namespace ygo */
#endif /* YGOCARDOPSPANEL_H_ */
