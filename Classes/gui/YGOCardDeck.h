/*
 * YGOCardDeck.h
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#ifndef YGOCARDDECK_H_
#define YGOCARDDECK_H_

#include "CommonGui.h"
#include "YGOCardCell.h"

namespace ygo {

/**
 * Data source that governs card grid backend data.
 * @lua NA
 */
class YGOCardDeckSource {
public:
	virtual ~YGOCardDeckSource() {
	}

	/**
	 * cell height for a given table.
	 *
	 * @param table table to hold the instances of Class
	 * @return cell size
	 */
	virtual cocos2d::CCSize cellSize() = 0;

	/**
	 * horizontal row counts.
	 *
	 * @return rows in horizontal direction;
	 */
	virtual unsigned int horizontalRows() = 0;

	/**
	 * horizontal & vertical margin.
	 *
	 * @return margin in horizontal&vertical direction;
	 */
	virtual float margin() = 0;

	/**
	 * vertical row counts.
	 *
	 * @return rows in vertical direction;
	 */
	virtual unsigned int verticalRows() = 0;

	/**
	 * a cell instance at a given index
	 *
	 * @return cell found at idx
	 */
	virtual YGOCardCell* gridCellAtIndex(unsigned int idx) = 0;

	/**
	 * remove a cell instance at a given index
	 *
	 * @return cell removed at idx
	 */
	virtual void removeCellAtIndex(unsigned int idx) = 0;

	/**
	 * insert a cell instance at a given index
	 *
	 * @return cell found at idx
	 */
	virtual void insertCellAtIndex(ygo::YGOCardCell* cell, unsigned int idx) = 0;

	/**
	 * insert a cell instance at last position
	 *
	 * @return new cell to push back
	 */
	virtual void pushBackCell(ygo::YGOCardCell* cell) = 0;

	/**
	 * Returns total number of cells.
	 *
	 */
	virtual unsigned int numberOfCells() = 0;

};

class YGOCardDeck: public YGOCardDeckSource, public cocos2d::CCObject {
public:
	YGOCardDeck();
	virtual ~YGOCardDeck();
	virtual bool initWithCards(std::vector<code_pointer>* cards,
			int hRows, int vRows, int maxCells, bool isThumbnail);
	/**
	 * cell height for a given table.
	 *
	 * @param table table to hold the instances of Class
	 * @return cell size
	 */
	virtual cocos2d::CCSize cellSize();

	/**
	 * horizontal row counts.
	 *
	 * @return rows in horizontal direction;
	 */
	virtual unsigned int horizontalRows();

	/**
	 * vertical row counts.
	 *
	 * @return rows in vertical direction;
	 */
	virtual unsigned int verticalRows();

	/**
	 * horizontal & vertical margin.
	 *
	 * @return margin in horizontal&vertical direction;
	 */
	virtual float margin();

	/**
	 * a cell instance at a given index
	 *
	 * @return cell found at idx
	 */
	virtual ygo::YGOCardCell* gridCellAtIndex(unsigned int idx) {
		return m_pCardCells->at(idx);
	}

	/**
	 * remove a cell instance at a given index
	 *
	 */
	virtual void removeCellAtIndex(unsigned int idx);

	/**
	 * insert a cell instance at a given index
	 *
	 * @return cell found at idx
	 */
	virtual void insertCellAtIndex(ygo::YGOCardCell* cell,  unsigned int idx) {
		m_pCardCells->insert(m_pCardCells->begin() + idx, cell);
		m_pCards->insert(m_pCards->begin() + idx, cell->getCard());
	}

	/**
	 * insert a cell instance at last position
	 *
	 * @return new cell to push back
	 */
	virtual void pushBackCell(ygo::YGOCardCell* cell) {
		m_pCardCells->push_back(cell);
		m_pCards->push_back(cell->getCard());
	}

	/**
	 * Returns total number of cells.
	 *
	 */
	virtual unsigned int numberOfCells() {
		return m_pCardCells->size();
	}

	static YGOCardDeck* create(std::vector<code_pointer>* pCards,
				int hRows, int vRows, int maxCells, CCSize mSize, bool isThumbnail = true);

	CC_SYNTHESIZE_READONLY(std::vector<ygo::YGOCardCell *>*, m_pCardCells, CardCells);
	CC_SYNTHESIZE_READONLY(std::vector<code_pointer>*, m_pCards, Cards);
private:
	int m_verticalRows;
	int m_horizontalRows;
	CCSize mRequestCellSize;
	CC_SYNTHESIZE_READONLY(int, m_maxCells, MaxCells);
};

} /* namespace ygo */
#endif /* YGOCARDDECK_H_ */
