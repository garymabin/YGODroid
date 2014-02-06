/*
 * YGOClientField.cpp
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#include "YGOClientField.h"

namespace ygo {

YGOClientField::YGOClientField() {
//	panel = 0;
	hovered_card = 0;
	clicked_card = 0;
	highlighting_card = 0;
	deck_act = false;
	grave_act = false;
	remove_act = false;
	extra_act = false;
	deck_reversed = false;
	for (int p = 0; p < 2; ++p) {
		for (int i = 0; i < 5; ++i)
			mzone[p].push_back(0);
		for (int i = 0; i < 6; ++i)
			szone[p].push_back(0);
	}
}

YGOClientField::~YGOClientField() {
	// TODO Auto-generated destructor stub
}

void YGOClientField::Clear() {
	for (int i = 0; i < 2; ++i) {
		for (auto cit = deck[i].begin(); cit != deck[i].end(); ++cit)
			delete *cit;
		deck[i].clear();
		for (auto cit = hand[i].begin(); cit != hand[i].end(); ++cit)
			delete *cit;
		hand[i].clear();
		for (auto cit = mzone[i].begin(); cit != mzone[i].end(); ++cit) {
			if (*cit)
				delete *cit;
			*cit = 0;
		}
		for (auto cit = szone[i].begin(); cit != szone[i].end(); ++cit) {
			if (*cit)
				delete *cit;
			*cit = 0;
		}
		for (auto cit = grave[i].begin(); cit != grave[i].end(); ++cit)
			delete *cit;
		grave[i].clear();
		for (auto cit = remove[i].begin(); cit != remove[i].end(); ++cit)
			delete *cit;
		remove[i].clear();
		for (auto cit = extra[i].begin(); cit != extra[i].end(); ++cit)
			delete *cit;
		extra[i].clear();
	}
	for (auto sit = overlay_cards.begin(); sit != overlay_cards.end(); ++sit)
		delete *sit;
	overlay_cards.clear();
	chains.clear();
	disabled_field = 0;
	deck_act = false;
	grave_act = false;
	remove_act = false;
	extra_act = false;
	deck_reversed = false;
}

void YGOClientField::Initial(int player, int deckc, int extrac) {
}

void YGOClientField::UpdateCard(int controler, int location, int sequence,
		char* data) {
}

void YGOClientField::UpdateFieldCard(int controler, int location, char* data) {
}

void YGOClientField::ClearCommandFlag() {
}

void YGOClientField::ClearSelect() {
}

void YGOClientField::ClearChainSelect() {
}

void YGOClientField::ShowSelectCard(bool buttonok) {
}

void YGOClientField::ReplaySwap() {
}

void YGOClientField::RefreshAllCards() {
}

void YGOClientField::GetChainLocation(int controler, int location, int sequence,
		CCPoint& point) {
}

bool YGOClientField::CheckSelectSum() {
}

void YGOClientField::GetHoverField(int x, int y) {
}

YGOClientCard* YGOClientField::GetCard(int controler, int location,
		int sequence, int sub_seq) {
}

void YGOClientField::AddCard(YGOClientCard* pcard, int controler, int location,
		int sequence) {
}

YGOClientCard* YGOClientField::RemoveCard(int controler, int location,
		int sequence) {
}

void YGOClientField::MoveCard(YGOClientCard* pcard, int frame) {
}

void YGOClientField::FadeCard(YGOClientCard* pcard, int alpha, int frame) {
}

bool YGOClientField::check_min(std::set<YGOClientCard*>& left,
		std::set<YGOClientCard*>::iterator index, int min, int max) {
}

bool YGOClientField::check_sel_sum_s(std::set<YGOClientCard*>& left, int index,
		int acc) {
}

void YGOClientField::check_sel_sum_t(std::set<YGOClientCard*>& left, int acc) {
}

bool YGOClientField::check_sum(std::set<YGOClientCard*>& testlist,
		std::set<YGOClientCard*>::iterator index, int acc, int count) {
}

void YGOClientField::ShowMenu(int flag, int x, int y) {
}

} /* namespace ygo */
