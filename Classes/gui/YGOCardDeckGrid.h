/*
 * YGOCardDeckGrid.h
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#ifndef YGOCARDDECKGRID_H_
#define YGOCARDDECKGRID_H_

#include "CommonGui.h"
#include "YGOCardDeck.h"
#include "YGOCardFrame.h"

namespace ygo {

class YGOCardDeckGrid: public cocos2d::gui::Widget {
public:
	YGOCardDeckGrid();
	virtual ~YGOCardDeckGrid();
	virtual bool initWithSize(cocos2d::CCSize size);
	static YGOCardDeckGrid* create(const cocos2d::CCSize &size);
	/**
	 * Inserts a new cell at a given index
	 *
	 * @param cell card cell to insert
	 * @param idx location to insert
	 */
	void insertCellAtIndex(YGOCardCell* cell, unsigned int idx);

	/**
	 * Inserts a new cell at last index, will be more efficient than #insertCellAtIndex
	 *
	 * @param cell card cell to insert
	 */
	void pushBackCell(YGOCardCell* cell);

	/**
	 * Removes a cell at a given index
	 *
	 * @param idx index to find a cell
	 */
	void removeCellAtIndex(unsigned int idx);

	/**
	 * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
	 *
	 * @param idx index
	 * @return a cell at a given index
	 */
	YGOCardCell *cellAtIndex(unsigned int idx);

	void setDataSource(YGOCardDeck* dataSource);

	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void onTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void doLayout();
	virtual void doMeasure();
	virtual void notifyDataSetChanged();
	void addChildTouchedObserver(CCObject* target, SEL_CallFuncO func);

protected:
	float m_rowHeight;
	float m_rowWidth;
	int m_verticalRows;
	int m_horizontalRows;
	float m_margin;
	bool m_bTouched;
	bool m_bDragged;
	YGOCardCell* m_pTouchedCell;
	int m_startCellX;
	int m_startCellY;
	int m_maxCells;
	int m_resizeMaxCells;
	YGOCardDeck* m_pDataSource;
	YGOCardFrame* m_pCardFrame;

	CCObject* m_pChildTouchedTarget;
	SEL_CallFuncO m_pFnchldTouched;

	inline void resetTouchPoints() {
		m_bTouched = false;
		m_bDragged = false;
		m_startCellX = -1;
		m_startCellY = -1;
		m_pTouchedCell = NULL;
	}
	void setHorizontalRows();
	void addFrame();
	void removeFrame();
	void renderCellAtCoordis(YGOCardCell* child, cocos2d::CCPoint point);
};

} /* namespace ygo */
#endif /* YGOCARDDECKGRID_H_ */
