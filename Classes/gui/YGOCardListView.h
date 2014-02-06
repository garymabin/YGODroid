/*
 * YGOCardListView.h
 *
 *  Created on: 2014年1月30日
 *      Author: mabin
 */

#ifndef YGOCARDLISTVIEW_H_
#define YGOCARDLISTVIEW_H_

#include "cocos-ext.h"
#include "cocos2d.h"

namespace ygo {

class YGOCardListView: public cocos2d::gui::ListView {
public:
	YGOCardListView();
	virtual ~YGOCardListView();
};

} /* namespace ygo */
#endif /* YGOCARDLISTVIEW_H_ */
