/*
 * YGOClientCard.cpp
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#include "YGOClientCard.h"

namespace ygo {

} /* namespace ygo */

ygo::YGOClientCard::YGOClientCard() {
	curAlpha = 255;
	dAlpha = 0;
	aniFrame = 0;
	is_moving = false;
	is_fading = false;
	is_hovered = false;
	is_selectable = false;
	is_selected = false;
	is_showequip = false;
	is_showtarget = false;
	is_highlighting = false;
	is_disabled = false;
	is_reversed = false;
	cmdFlag = 0;
	code = 0;
	type = 0;
	alias = 0;
	level = 0;
	rank = 0;
	race = 0;
	attribute = 0;
	attack = 0;
	defence = 0;
	base_attack = 0;
	base_defence = 0;
	cHint = 0;
	chValue = 0;
	atkstring[0] = 0;
	defstring[0] = 0;
	lvstring[0] = 0;
	overlayTarget = 0;
	equipTarget = 0;
}

void ygo::YGOClientCard::SetCode(int code) {
}

void ygo::YGOClientCard::UpdateInfo(char* buf) {
}

void ygo::YGOClientCard::ClearTarget() {
}

bool ygo::YGOClientCard::client_card_sort(YGOClientCard* c1,
		YGOClientCard* c2) {
	int32 cp1 =
			c1->overlayTarget ? c1->overlayTarget->controler : c1->controler;
	int32 cp2 =
			c2->overlayTarget ? c2->overlayTarget->controler : c2->controler;
	if (cp1 != cp2)
		return cp1 < cp2;
	if (c1->location != c2->location)
		return c1->location < c2->location;
	if (c1->location & LOCATION_OVERLAY)
		if (c1->overlayTarget != c2->overlayTarget)
			return c1->overlayTarget->sequence < c2->overlayTarget->sequence;
		else
			return c1->sequence < c2->sequence;
	else {
		if (c1->location & 0x71)
			return c1->sequence > c2->sequence;
		else
			return c1->sequence < c2->sequence;
	}
}

bool ygo::YGOClientCard::deck_sort_lv(code_pointer p1, code_pointer p2) {
	if ((p1->second.type & 0x7) != (p2->second.type & 0x7))
		return (p1->second.type & 0x7) < (p2->second.type & 0x7);
	if ((p1->second.type & 0x7) == 1) {
		int type1 =
				(p1->second.type & 0x8020c0) ?
						(p1->second.type & 0x8020c1) : (p1->second.type & 0x31);
		int type2 =
				(p2->second.type & 0x8020c0) ?
						(p2->second.type & 0x8020c1) : (p2->second.type & 0x31);
		if (type1 != type2)
			return type1 < type2;
		if (p1->second.level != p2->second.level)
			return p1->second.level > p2->second.level;
		if (p1->second.attack != p2->second.attack)
			return p1->second.attack > p2->second.attack;
		if (p1->second.defence != p2->second.defence)
			return p1->second.defence > p2->second.defence;
		else
			return p1->first < p2->first;
	}
	if ((p1->second.type & 0xfffffff8) != (p2->second.type & 0xfffffff8))
		return (p1->second.type & 0xfffffff8) < (p2->second.type & 0xfffffff8);
	return p1->first < p2->first;
}
