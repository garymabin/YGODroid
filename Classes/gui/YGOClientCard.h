/*
 * YGOClientCard.h
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#ifndef YGOCLIENTCARD_H_
#define YGOCLIENTCARD_H_

#include "config.h"
#include <vector>
#include <set>
#include <unordered_map>

namespace ygo {
struct CardData {
	unsigned int code;
	unsigned int alias;
	unsigned int setcode;
	unsigned int type;
	unsigned int level;
	unsigned int attribute;
	unsigned int race;
	int attack;
	int defence;
};
struct CardDataC {
	unsigned int code;
	unsigned int alias;
	unsigned int setcode;
	unsigned int type;
	unsigned int level;
	unsigned int attribute;
	unsigned int race;
	int attack;
	int defence;
	unsigned int ot;
	unsigned int category;
};
struct CardString {
	wchar_t* name;
	wchar_t* text;
	wchar_t* desc[16];
};
typedef std::unordered_map<unsigned int, CardDataC>::iterator code_pointer;

class YGOClientCard {
public:
//	irr::video::ITexture* curTexture;
//	irr::core::matrix4 mTransform;
//	irr::core::vector3df curPos;
//	irr::core::vector3df curRot;
//	irr::core::vector3df dPos;
//	irr::core::vector3df dRot;
	uint32 curAlpha;
	uint32 dAlpha;
	uint32 aniFrame;
	bool is_moving;
	bool is_fading;
	bool is_hovered;
	bool is_selectable;
	bool is_selected;
	bool is_showequip;
	bool is_showtarget;
	bool is_highlighting;
	bool is_reversed;
	uint32 code;
	uint32 alias;
	uint32 type;
	uint32 level;
	uint32 rank;
	uint32 attribute;
	uint32 race;
	int32 attack;
	int32 defence;
	int32 base_attack;
	int32 base_defence;
	uint32 reason;
	uint32 select_seq;
	uint8 owner;
	uint8 controler;
	uint8 location;
	uint8 sequence;
	uint8 position;
	uint8 is_disabled;
	uint8 is_public;
	uint8 cHint;
	uint32 chValue;
	uint32 opParam;
	uint32 symbol;
	uint32 cmdFlag;
	YGOClientCard* overlayTarget;
	std::vector<YGOClientCard*> overlayed;
	YGOClientCard* equipTarget;
	std::set<YGOClientCard*> equipped;
	std::set<YGOClientCard*> cardTarget;
	std::set<YGOClientCard*> ownerTarget;
	std::map<int, int> counters;
	std::map<int, int> desc_hints;
	wchar_t atkstring[16];
	wchar_t defstring[16];
	wchar_t lvstring[16];

	YGOClientCard();
	void SetCode(int code);
	void UpdateInfo(char* buf);
	void ClearTarget();
	static bool client_card_sort(YGOClientCard* c1, YGOClientCard* c2);
	static bool deck_sort_lv(code_pointer p1, code_pointer p2);
};

} /* namespace ygo */
#endif /* YGOCLIENTCARD_H_ */
