/*
 * YGODeckBuilder.h
 *
 *  Created on: 2014年1月30日
 *      Author: mabin
 */

#ifndef YGODECKBUILDER_H_
#define YGODECKBUILDER_H_

#include "CommonGui.h"
#include "YGOClientCard.h"
#include <unordered_map>
#include "YGODeckManager.h"
#include "YGOMainMenuLayer.h"
#include "YGOGameConfig.h"

USING_NS_CC;

namespace ygo {

class YGODeckBuilder : public CCObject{
public:
	YGODeckBuilder();
	virtual ~YGODeckBuilder();
	void FilterCards();
	virtual bool init();
	CREATE_FUNC(YGODeckBuilder);

	CC_SYNTHESIZE(long long, filter_effect, FilterEffect);
//	long long filter_effect;
	CC_SYNTHESIZE(unsigned int, filter_type, FilterType);
	CC_SYNTHESIZE(unsigned int, filter_type2, FilterType2);
	CC_SYNTHESIZE(unsigned int, filter_attrib, FilterAttrib);
	CC_SYNTHESIZE(unsigned int, filter_race, FilterRace);
	CC_SYNTHESIZE(wchar_t*, filter_keyword, FilterKeyword);
	CC_SYNTHESIZE(int, filter_lm, FilterLm);

	void setAtkFilter(const wchar_t* atk_str);
	void setDefFilter(const wchar_t* def_str);
	void setLvFilter(const wchar_t* lv_str);
protected:
	unsigned int filter_atktype;
	int filter_atk;
	unsigned int filter_deftype;
	int filter_def;
	unsigned int filter_lvtype;
	unsigned int filter_lv;


//	unsigned int filter_type;
//	unsigned int filter_type2;
//	unsigned int filter_attrib;
//	unsigned int filter_race;
//	int filter_lm;

	int hovered_code;
	int hovered_pos;
	int hovered_seq;
	int click_pos;
	bool is_draging;
	int dragx;
	int dragy;
	size_t pre_mainc;
	size_t pre_extrac;
	size_t pre_sidec;
	code_pointer draging_pointer;

	std::unordered_map<int, int>* filterList;
	std::vector<code_pointer> results;
	wchar_t result_string[8];
private:
	YGODeckManager* m_pDeckMgr;
	YGODataManager* m_pDataMgr;
};

} /* namespace ygo */
#endif /* YGODECKBUILDER_H_ */
