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

#define MOVE_TRIGER_THRESHOLD 30.0

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

	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void doTouchAction();
	void cancelTouchAction();

	void resetTouchPoints() {
		m_bTouched = false;
		m_bDragged = false;
		m_bDragTriggerd = false;
		m_startIndex = -1;
		m_pTouchedCell = NULL;
		m_draggedYDistance = 0.0;
		m_touchedCellScale = 1.0;
		m_startDraggedPointY = 0.0;
		m_touchedCellZorder = 0;
		m_touchedCellPosition = CCPointZero;
	}

	void addChildDraggedObserver(CCObject* target, SEL_CallFuncND func);
	void addChildTouchedObserver(CCObject* target, SEL_CallFuncO func);
protected:
	int m_cells;
	int m_resizeMaxCells;
	float m_rowWidth;
	float m_rowHeight;
	float m_margin;
	bool m_bTouched;
	bool m_bDragged;
	bool m_bDragTriggerd;
	int m_startIndex;
	float m_touchedCellScale;
	int m_touchedCellZorder;
	CCPoint m_touchedCellPosition;
	float m_startDraggedPointY;
	float m_draggedYDistance;
	YGOCardDeck* m_pDataSource;
	YGOCardCell* m_pTouchedCell;

	CCObject* m_pChildDraggedTarget;
	SEL_CallFuncND m_pFnchldDragged;

	CCObject* m_pChildTouchedTarget;
	SEL_CallFuncO m_pFnchldTouched;
};

} /* namespace ygo */
#endif /* YGOHANDCARDLIST_H_ */
