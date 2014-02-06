/*
 * YGOCardDeckGrid.cpp
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#include "YGOCardDeckGrid.h"

USING_NS_CC;
using namespace gui;

namespace ygo {

YGOCardDeckGrid::YGOCardDeckGrid() :
		m_pCardFrame(NULL), m_pTouchedCell(NULL), m_startCellX(-1), m_startCellY(
				-1), m_bTouched(false), m_bDragged(false), m_rowHeight(0.0), m_rowWidth(
				0.0), m_margin(0.0), m_verticalRows(0), m_horizontalRows(0), m_pDataSource(
				NULL) {
}

YGOCardDeckGrid::~YGOCardDeckGrid() {
	// TODO Auto-generated destructor stub
	CC_SAFE_RELEASE_NULL(m_pDataSource);
	CC_SAFE_RELEASE_NULL(m_pCardFrame);
}

YGOCardDeckGrid* YGOCardDeckGrid::create(const cocos2d::CCSize& size) {
	YGOCardDeckGrid* p_grid = new YGOCardDeckGrid();
	p_grid->autorelease();
	p_grid->initWithSize(size);
	return p_grid;
}

void YGOCardDeckGrid::insertCellAtIndex(YGOCardCell* cell, unsigned int idx) {
//	this->addChild(cell);
	m_pDataSource->insertCellAtIndex(cell, idx);
	notifyDataSetChanged();
}

void YGOCardDeckGrid::pushBackCell(YGOCardCell* cell) {
//	this->addChild(cell);
	m_pDataSource->pushBackCell(cell);
	notifyDataSetChanged();
}

void YGOCardDeckGrid::removeCellAtIndex(unsigned int idx) {
//	YGOCardCell* pCell = m_pDataSource->getCards()->at(idx);
//	pCell->setVisible(false);
//	this->removeChild(pCell, false);
	m_pDataSource->removeCellAtIndex(idx);
	notifyDataSetChanged();
}

YGOCardCell* YGOCardDeckGrid::cellAtIndex(unsigned int idx) {
	return m_pDataSource->gridCellAtIndex(idx);
}

void YGOCardDeckGrid::doMeasure() {
	int count = m_pDataSource->numberOfCells();
	for (int i = 0; i < count; i++) {
		YGOCardCell* child = m_pDataSource->gridCellAtIndex(i);
		GridLayoutParameter* param = GridLayoutParameter::create();
		param->setCellX(i % m_horizontalRows);
		param->setCellY(i / m_horizontalRows);
		child->setLayoutParameter(param);
	}
}

bool YGOCardDeckGrid::initWithSize(CCSize size) {
	if (!Widget::init()) {
		return false;
	}
	_size = size;
	this->setAnchorPoint(CCPointZero);
	return true;
}

void YGOCardDeckGrid::doLayout() {
	int length = m_pDataSource->numberOfCells();
	float totalHeight = _size.height;
	float totalWidth = _size.width;
	for (int i = 0; i < length; i++) {
		Widget* child = m_pDataSource->gridCellAtIndex(i);
		GridLayoutParameter* param =
				dynamic_cast<GridLayoutParameter*>(child->getLayoutParameter(
						LAYOUT_PARAMETER_NONE));
		if (param) {
			int cellX = param->getCellX();
			int cellY = param->getCellY();
			if (m_pDataSource->numberOfCells() <= m_resizeMaxCells) {
				child->setPosition(
					ccp( (cellX * (m_rowWidth + 2 * m_margin) + 2 * m_margin),
							(totalHeight - (cellY + 1) * (m_rowHeight + 2 * m_margin))
					));
			} else {
				float newRowWidth = (totalWidth - 4 * m_margin)/m_horizontalRows;
				child->setPosition(
							ccp( (cellX * (newRowWidth) + 2 * m_margin),
									(totalHeight - (cellY + 1) * (m_rowHeight + 2 * m_margin))
							));
			}

		}
	}
}

bool YGOCardDeckGrid::onTouchBegan(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	bool bRet = Widget::onTouchBegan(pTouch, pEvent);
	if (bRet) {
		m_bTouched = true;
		CCPoint point1 = pTouch->getLocation();
		CCPoint point = this->convertToNodeSpace(point1);
		CCLOG("touchbegin point1.x = %f, point1.y = %f", point1.x, point1.y);
		CCLOG("touchbegin point.x = %f, point.y = %f, _size.height = %f",
				point.x, point.y, getContentSize().height);
		int cellX = point.x / ((m_rowWidth + 2 * m_margin));
		int cellY = (getContentSize().height - point.y)
				/ ((m_rowHeight + 2 * m_margin));
		CCLOG("touchbegin cellX = %d, cellY = %d", cellX, cellY);
		int idx = cellY * m_horizontalRows + cellX;
		CCLOG("touched idx = %d", idx);
		if (idx < 0 || idx >= m_pDataSource->numberOfCells()) {
			bRet = false;
			goto exit;
		}
		m_startCellX = cellX;
		m_startCellY = cellY;
		m_pTouchedCell = m_pDataSource->gridCellAtIndex(idx);
		addFrame();
		if (m_pChildTouchedTarget && m_pFnchldTouched) {
			(m_pChildTouchedTarget->*m_pFnchldTouched)(m_pTouchedCell);
		}
	}
	exit: return bRet;
}

void YGOCardDeckGrid::onTouchMoved(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchMoved(pTouch, pEvent);
	CCPoint point1 = pTouch->getLocation();
	CCPoint point = this->convertToNodeSpace(point1);
	CCLOG("moved point1.x = %f, point1.y = %f", point1.x, point1.y);
	if (m_bTouched && !m_bDragged) {
		int idx = m_startCellY * m_horizontalRows + m_startCellX;
		m_bDragged = true;
		removeFrame();
		CCLOG("moved idx = %d", idx);
		this->removeCellAtIndex(idx);
	}
	if (m_bTouched && m_bDragged) {
		renderCellAtCoordis(m_pTouchedCell, point);
	}
}

void YGOCardDeckGrid::onTouchEnded(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchEnded(pTouch, pEvent);
	CCPoint point1 = pTouch->getLocation();
	CCPoint point = this->convertToNodeSpace(point1);
	CCLOG("touchend point1.x = %f, point1.y = %f", point1.x, point1.y);
	CCLOG("touchend point.x = %f, point.y = %f", point.x, point.y);
	int cellX = point.x / ((m_rowWidth + 2 * m_margin));
	int cellY = (getContentSize().height - point.y)
			/ ((m_rowHeight + 2 * m_margin));

	if (!m_bDragged
			&& (cellX > m_horizontalRows || cellX < 0 || cellY < 0
					|| cellY > m_verticalRows)) {
		goto exit;
	}
	if (m_bTouched && m_bDragged) {
		if (cellX > m_horizontalRows || cellX < 0 || cellY < 0
				|| cellY > m_verticalRows) {
			this->pushBackCell(m_pTouchedCell);
		} else {
			int idx = m_startCellY * m_horizontalRows + m_startCellX;
			this->insertCellAtIndex(m_pTouchedCell, idx);
		}
	}
	exit: resetTouchPoints();
}

void YGOCardDeckGrid::onTouchCancelled(cocos2d::CCTouch* pTouch,
		cocos2d::CCEvent* pEvent) {
	Widget::onTouchCancelled(pTouch, pEvent);
	resetTouchPoints();
}

void YGOCardDeckGrid::notifyDataSetChanged() {
	setHorizontalRows();
	doMeasure();
	doLayout();
}

void YGOCardDeckGrid::setDataSource(YGOCardDeck* dataSource) {
	CCLOG("setDataSource");
	CC_ASSERT(dataSource);
	if (m_pDataSource) {
		m_pDataSource->release();
		this->removeAllChildren();
		this->removeAllNodes();
	}
	m_pDataSource = dataSource;
	m_pDataSource->retain();
	m_maxCells = m_pDataSource->getMaxCells();
	m_resizeMaxCells = m_pDataSource->verticalRows() * m_pDataSource->horizontalRows();
	m_rowHeight = m_pDataSource->cellSize().height;
	m_rowWidth = m_pDataSource->cellSize().width;
	m_margin = m_pDataSource->margin();
	m_verticalRows = m_pDataSource->verticalRows();
	setHorizontalRows();
	m_pCardFrame = YGOCardFrame::create(m_pDataSource->cellSize(), 3.0f);
	m_pCardFrame->retain();
	this->doMeasure();
	this->doLayout();
	int count = m_pDataSource->numberOfCells();
	for (int i = 0; i < count; i++) {
		this->addChild(m_pDataSource->gridCellAtIndex(i));
	}
	this->setTouchEnabled(true);
	this->setEnabled(true);
	this->setPosition(CCPointZero);
	this->addNode(m_pCardFrame);
	m_pCardFrame->setVisible(false);
}

inline void YGOCardDeckGrid::addFrame() {
	if (m_pTouchedCell != NULL) {
		CCPoint point = m_pTouchedCell->getPosition();
		CCLOG("orig point x = %f, y = %f", point.x, point.y);
		m_pCardFrame->setPosition(ccp (point.x - m_margin, point.y - m_margin));
		m_pCardFrame->setVisible(true);
		CCLOG("later point x = %f, y = %f", m_pCardFrame->getPositionX(),
				m_pCardFrame->getPositionY());
	}
}

inline void YGOCardDeckGrid::removeFrame() {
	if (m_pCardFrame->isVisible()) {
		m_pCardFrame->setVisible(false);
	}
}

inline void YGOCardDeckGrid::setHorizontalRows() {
	int currentSize = m_pDataSource->numberOfCells();
	m_horizontalRows = currentSize > m_resizeMaxCells ? (int)((float)(currentSize + m_verticalRows - 1)/(float)m_verticalRows)
			: m_pDataSource->horizontalRows();
}

void YGOCardDeckGrid::addChildTouchedObserver(CCObject* target, SEL_CallFuncO func) {
	if (m_pChildTouchedTarget != target) {
		m_pChildTouchedTarget = target;
		m_pFnchldTouched = func;
	}
}

void YGOCardDeckGrid::renderCellAtCoordis(YGOCardCell* child, CCPoint point) {
	if (child) {
		child->setPosition(point);
	}
}

} /* namespace ygo */
