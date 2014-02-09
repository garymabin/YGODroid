/*
 * YGOHandCardList.cpp
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#include "YGOHandCardList.h"

namespace ygo {

YGOHandCardList::YGOHandCardList() {
	// TODO Auto-generated constructor stub
	resetTouchPoints();
}

YGOHandCardList::~YGOHandCardList() {
	// TODO Auto-generated destructor stub
	CC_SAFE_RELEASE_NULL(m_pDataSource);
}

bool YGOHandCardList::initWithSize(cocos2d::CCSize size) {
	if (!Widget::init()) {
		return false;
	}
	_size = size;
	return true;
}

YGOHandCardList* YGOHandCardList::create(const cocos2d::CCSize& size) {
	YGOHandCardList* p_list = new YGOHandCardList();
	p_list->autorelease();
	p_list->initWithSize(size);
	return p_list;
}

void YGOHandCardList::setDataSource(YGOCardDeck* dataSource) {
	m_pDataSource = dataSource;
	m_pDataSource->retain();
	m_resizeMaxCells = m_pDataSource->verticalRows() * m_pDataSource->horizontalRows();
	m_rowWidth = m_pDataSource->cellSize().width;
	m_rowHeight = m_pDataSource->cellSize().height;
	m_cells = m_pDataSource->numberOfCells();
	doMeasure();
	doLayout();
	for (int i = 0; i < m_cells; i++) {
		this->addChild(m_pDataSource->gridCellAtIndex(i));
	}
	setTouchEnabled(true);
	setEnabled(true);
	setAnchorPoint(CCPointZero);
}

void YGOHandCardList::doLayout() {
	int length = m_pDataSource->numberOfCells();
	float totalHeight = _size.height;
	float totalWidth = _size.width;
	float maxCardWidth = m_rowWidth * m_cells;
	for (int i = 0; i < length; i++) {
		Widget* child = m_pDataSource->gridCellAtIndex(i);
		GridLayoutParameter* param =
				dynamic_cast<GridLayoutParameter*>(child->getLayoutParameter(
						LAYOUT_PARAMETER_NONE));
		if (param) {
			int cellX = param->getCellX();
			int cellY = param->getCellY();
			if (m_cells <= m_resizeMaxCells) {
				child->setPosition(
						ccp( (cellX * (m_rowWidth + 2 * m_margin) + 2 * m_margin + (totalWidth - maxCardWidth)/2),
								(totalHeight - (cellY + 1) * (m_rowHeight + 2 * m_margin))
						));
					} else {
						float newRowWidth = (totalWidth - 4 * m_margin)/m_cells;
						child->setPosition(
								ccp( (cellX * (newRowWidth) + 2 * m_margin),
										(totalHeight - (cellY + 1) * (m_rowHeight + 2 * m_margin))
								));
					}

				}
			}
}

void YGOHandCardList::doMeasure() {
	int count = m_pDataSource->numberOfCells();
	for (int i = 0; i < count; i++) {
		YGOCardCell* child = m_pDataSource->gridCellAtIndex(i);
		GridLayoutParameter* param = GridLayoutParameter::create();
		param->setCellX(i);
		param->setCellY(0);
		child->setLayoutParameter(param);
	}
}

bool YGOHandCardList::onTouchBegan(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	bool bRet = Widget::onTouchBegan(pTouch, pEvent);
	CCPoint point1 = pTouch->getLocation();
	if (bRet) {
		m_bTouched = true;
		CCPoint point = this->convertToNodeSpace(point1);
		CCLOG("touchbegin point.x = %f, point.y = %f, _size.height = %f",
				point.x, point.y, getContentSize().height);
		int idx = (point.x - 2 * m_margin  - (_size.width - m_rowWidth * m_cells)/2) / ((m_rowWidth + 2 * m_margin));
		CCLOG("touched idx = %d", idx);
		if (idx < 0 || idx >= m_pDataSource->numberOfCells()) {
			bRet = false;
			goto exit;
		}
		m_startIndex = idx;
		m_pTouchedCell = m_pDataSource->gridCellAtIndex(idx);
		m_touchedCellScale = m_pTouchedCell->getScaleX();
		m_touchedCellZorder = m_pTouchedCell->getZOrder();
		m_touchedCellPosition = m_pTouchedCell->getPosition();
		doTouchAction();
		if (m_pChildTouchedTarget && m_pFnchldTouched) {
			(m_pChildTouchedTarget->*m_pFnchldTouched)(m_pTouchedCell);
		}
	}
	exit: return bRet;
}

void YGOHandCardList::onTouchMoved(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchMoved(pTouch, pEvent);
	CCPoint point1 = pTouch->getLocation();
	CCPoint point = this->convertToNodeSpace(point1);
	CCLOG("moved point1.x = %f, point1.y = %f", point1.x, point1.y);
	if (m_bTouched && !m_bDragged) {
		m_bDragged = true;
		m_startDraggedPointY = point.y;
		CCLOG("moved start with y distance = %f", m_startDraggedPointY);
		return;
	}
	m_draggedYDistance = point.y - m_startDraggedPointY;
	if (m_bTouched && m_bDragged && m_draggedYDistance > MOVE_TRIGER_THRESHOLD && !m_bDragTriggerd) {
		CCLOG("moved trigger with y distance = %f", point.y);
		if (m_pChildDraggedTarget && m_pFnchldDragged) {
			(m_pChildDraggedTarget->*m_pFnchldDragged)(m_pTouchedCell, (void *)&point1);
		}
		m_bDragTriggerd = true;
	}
}

void YGOHandCardList::onTouchEnded(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchEnded(pTouch, pEvent);
	cancelTouchAction();
	resetTouchPoints();
}

void YGOHandCardList::onTouchCancelled(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchCancelled(pTouch, pEvent);
	cancelTouchAction();
	resetTouchPoints();
}

void YGOHandCardList::addChildTouchedObserver(CCObject* target,
		SEL_CallFuncO func) {
	if (m_pChildTouchedTarget != target) {
		m_pChildTouchedTarget = target;
		m_pFnchldTouched = func;
	}
}

void YGOHandCardList::doTouchAction() {
	if (m_pTouchedCell) {
		m_pTouchedCell->showScaleBy(1.5);
//		m_pTouchedCell->setPosition( ccp(m_touchedCellPosition.x - m_pTouchedCell->getContentSize().width,
//				m_touchedCellPosition.y));
		m_pTouchedCell->setZOrder(65535);
	}
}

void YGOHandCardList::cancelTouchAction() {
	if (m_pTouchedCell) {
		m_pTouchedCell->showNormal();
//		m_pTouchedCell->setPosition(m_touchedCellPosition);
		m_pTouchedCell->setZOrder(m_touchedCellZorder);
	}
}

void YGOHandCardList::addChildDraggedObserver(CCObject* target,
		SEL_CallFuncND func) {
	if (m_pChildDraggedTarget != target) {
		m_pChildDraggedTarget = target;
		m_pFnchldDragged = func;
	}
}

} /* namespace ygo */
