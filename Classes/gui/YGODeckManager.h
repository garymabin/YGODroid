/*
 * YGODeckManager.h
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#ifndef YGODECKMANAGER_H_
#define YGODECKMANAGER_H_

#include "cocos2d.h"
#include "YGOClientCard.h"
#include <unordered_map>
#include <vector>
#include "YGODataManager.h"
#include <dirent.h>

namespace ygo {

class LFList {
public:
	~LFList() {
		CC_SAFE_DELETE(content);
	}
	unsigned int hash;
	wchar_t listName[20];
	std::unordered_map<int, int>* content;
};

struct Deck {
	std::vector<code_pointer> main;
	std::vector<code_pointer> extra;
	std::vector<code_pointer> side;
	Deck() {
	}
	Deck(const Deck& ndeck) {
		main = ndeck.main;
		extra = ndeck.extra;
		side = ndeck.side;
	}
	void clear() {
		main.clear();
		extra.clear();
		side.clear();
	}
};

class YGODeckManager {
public:
	YGODeckManager();
	std::vector<LFList *> _lfList;
	static YGODeckManager* sharedDeckManager();

	void LoadLFList();
	wchar_t* GetLFListName(int lfhash);
	int CheckLFList(Deck& deck, int lfhash, bool allow_ocg, bool allow_tcg);
	void LoadDeck(Deck& deck, int* dbuf, int mainc, int sidec);
	bool LoadSide(Deck& deck, int* dbuf, int mainc, int sidec);
	bool LoadDeck(const char* file);
	bool SaveDeck(Deck& deck, const char* name);
	void RefreshDeckList(std::vector<cocos2d::CCString*>* deckList);
	Deck current_deck;
protected:
	YGODataManager* m_pDataManager;
};
} /* namespace ygo */
#endif /* YGODECKMANAGER_H_ */
