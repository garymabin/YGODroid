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
	this->setAnchorPoint(CCPointZero);
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

} /* namespace ygo */
