/*
 * YGOClientField.h
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#ifndef YGOCLIENTFIELD_H_
#define YGOCLIENTFIELD_H_
#include "YGOClientCard.h"
#include "cocos2d.h"

USING_NS_CC;

namespace ygo {

class YGOClientCard;

struct ChainInfo{
//	irr::core::vector3df chain_pos;
	YGOClientCard* chain_card;
	int code;
	int desc;
	int controler;
	int location;
	int sequence;
	bool solved;
};

class YGOClientField {
public:
	YGOClientField();
	virtual ~YGOClientField();
	std::vector<YGOClientCard*> deck[2];
	std::vector<YGOClientCard*> hand[2];
	std::vector<YGOClientCard*> mzone[2];
	std::vector<YGOClientCard*> szone[2];
	std::vector<YGOClientCard*> grave[2];
	std::vector<YGOClientCard*> remove[2];
	std::vector<YGOClientCard*> extra[2];
	std::set<YGOClientCard*> overlay_cards;
	std::vector<YGOClientCard*> summonable_cards;
	std::vector<YGOClientCard*> spsummonable_cards;
	std::vector<YGOClientCard*> msetable_cards;
	std::vector<YGOClientCard*> ssetable_cards;
	std::vector<YGOClientCard*> reposable_cards;
	std::vector<YGOClientCard*> activatable_cards;
	std::vector<YGOClientCard*> attackable_cards;
	std::vector<int> activatable_descs;
	std::vector<int> select_options;
	std::vector<ChainInfo> chains;

	size_t selected_option;
	YGOClientCard* attacker;
	YGOClientCard* attack_target;
	int disabled_field;
	int selectable_field;
	int selected_field;
	int select_min;
	int select_max;
	int select_sumval;
	int select_cancelable;
	int select_mode;
	bool select_ready;
	int announce_count;
	int select_counter_count;
	int select_counter_type;
	std::vector<YGOClientCard*> selectable_cards;
	std::vector<YGOClientCard*> selected_cards;
	std::set<YGOClientCard*> selectsum_cards;
	std::vector<YGOClientCard*> selectsum_all;
	std::vector<int> sort_list;
	bool grave_act;
	bool remove_act;
	bool deck_act;
	bool extra_act;
	bool chain_forced;
	ChainInfo current_chain;
	bool last_chain;
	bool deck_reversed;

	void Clear();
	void Initial(int player, int deckc, int extrac);
	YGOClientCard* GetCard(int controler, int location, int sequence, int sub_seq = 0);
	void AddCard(YGOClientCard* pcard, int controler, int location, int sequence);
	YGOClientCard* RemoveCard(int controler, int location, int sequence);
	void UpdateCard(int controler, int location, int sequence, char* data);
	void UpdateFieldCard(int controler, int location, char* data);
	void ClearCommandFlag();
	void ClearSelect();
	void ClearChainSelect();
	void ShowSelectCard(bool buttonok = false);
	void ReplaySwap();
	void RefreshAllCards();

	void GetChainLocation(int controler, int location, int sequence, CCPoint &point);
	void GetCardLocation(YGOClientCard* pcard, CCPoint &point1, CCPoint &point2, bool setTrans = false);
	void MoveCard(YGOClientCard* pcard, int frame);
	void FadeCard(YGOClientCard* pcard, int alpha, int frame);
	bool CheckSelectSum();
	bool check_min(std::set<YGOClientCard*>& left, std::set<YGOClientCard*>::iterator index, int min, int max);
	bool check_sel_sum_s(std::set<YGOClientCard*>& left, int index, int acc);
	void check_sel_sum_t(std::set<YGOClientCard*>& left, int acc);
	bool check_sum(std::set<YGOClientCard*>& testlist, std::set<YGOClientCard*>::iterator index, int acc, int count);

//	irr::gui::IGUIElement* panel;
	std::vector<int> ancard;
	int hovered_controler;
	int hovered_location;
	size_t hovered_sequence;
	int command_controler;
	int command_location;
	size_t command_sequence;
	YGOClientCard* hovered_card;
	YGOClientCard* clicked_card;
	YGOClientCard* command_card;
	YGOClientCard* highlighting_card;
	int list_command;
	wchar_t formatBuffer[2048];

	void GetHoverField(int x, int y);
	void ShowMenu(int flag, int x, int y);
};

} /* namespace ygo */
#endif /* YGOCLIENTFIELD_H_ */
