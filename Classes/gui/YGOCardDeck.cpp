/*
 * YGOCardDeck.cpp
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#include "YGOCardDeck.h"

USING_NS_CC;
using namespace std;
using namespace extension;

namespace ygo {

YGOCardDeck::YGOCardDeck() :
		m_pCardCells(NULL), m_horizontalRows(0), m_verticalRows(0) {
	// TODO Auto-generated constructor stub
	mRequestCellSize = CCSizeZero;
}

YGOCardDeck::~YGOCardDeck() {
	// TODO Auto-generated destructor stub
	if (m_pCardCells) {
		vector<YGOCardCell *>::iterator iter;
		for (iter = m_pCardCells->begin(); iter != m_pCardCells->end(); iter++) {
			CC_SAFE_RELEASE_NULL(*iter);
		}
		delete m_pCardCells;
	}
}

bool YGOCardDeck::initWithCards(vector<code_pointer>* cards, int hRows,
		int vRows, int maxCells, bool isThumbnail) {
	m_pCards = cards;
	m_pCardCells = new vector<YGOCardCell *>();
	vector<code_pointer>::iterator iter;
	for (iter = cards->begin(); iter != cards->end(); iter++) {
		YGOCardCell* pCell = YGOCardCell::create(*iter, mRequestCellSize, isThumbnail);
		pCell->retain();
		m_pCardCells->push_back(pCell);
	}
	m_horizontalRows = hRows;
	m_verticalRows = vRows;
	m_maxCells = maxCells;
	return true;
}

float YGOCardDeck::margin() {
	return 3.0;
}

void YGOCardDeck::removeCellAtIndex(unsigned int idx) {
	m_pCardCells->erase(m_pCardCells->begin() + idx);
	m_pCards->erase(m_pCards->begin() + idx);
}

YGOCardDeck* YGOCardDeck::create(std::vector<code_pointer>* cards, int hRows,
		int vRows, int maxCells, CCSize size, bool isThumbnail) {
	YGOCardDeck* p_deck = new YGOCardDeck();
	p_deck->autorelease();
	p_deck->mRequestCellSize = size;
	p_deck->initWithCards(cards, hRows, vRows, maxCells, isThumbnail);
	return p_deck;
}

CCSize YGOCardDeck::cellSize() {
	return mRequestCellSize;
}

unsigned int YGOCardDeck::horizontalRows() {
	return m_horizontalRows;
}

unsigned int YGOCardDeck::verticalRows() {
	return m_verticalRows;
}

} /* namespace ygo */
