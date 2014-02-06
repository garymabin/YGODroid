/*
 * YGOHandCardList.h
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#ifndef YGOHANDCARDLIST_H_
#define YGOHANDCARDLIST_H_

#include "cocos2d.h"
#include "YGOCardDeck.h"
#include "YGOCardCell.h"
USING_NS_CC;
using namespace gui;

namespace ygo {

class YGOHandCardList: public cocos2d::gui::Widget {
public:
	YGOHandCardList();
	virtual ~YGOHandCardList();
	virtual bool initWithSize(cocos2d::CCSize size);
	static YGOHandCardList* create(const cocos2d::CCSize &size);
	void setDataSource(YGOCardDeck* dataSource);
	virtual void doLayout();
	virtual void doMeasure();
protected:
	int m_cells;
	int m_resizeMaxCells;
	float m_rowWidth;
	float m_rowHeight;
	float m_margin;
	YGOCardDeck* m_pDataSource;
	YGOCardCell* m_pTouchedCell;
};

} /* namespace ygo */
#endif /* YGOHANDCARDLIST_H_ */
