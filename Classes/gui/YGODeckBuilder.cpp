/*
 * YGODeckBuilder.cpp
 *
 *  Created on: 2014年1月30日
 *      Author: mabin
 */

#include "YGODeckBuilder.h"

USING_NS_CC;
using namespace gui;
using namespace extension;

namespace ygo {

YGODeckBuilder::YGODeckBuilder() {
	m_pDeckMgr = YGODeckManager::sharedDeckManager();
	m_pDataMgr = YGODataManager::sharedDataManager();
}

bool YGODeckBuilder::init() {
}

YGODeckBuilder::~YGODeckBuilder() {
	// TODO Auto-generated destructor stub
}

void YGODeckBuilder::FilterCards() {
	results.clear();
	int trycode = BufferIO::GetVal(filter_keyword);
	if (m_pDataMgr->GetData(trycode, 0)) {
		auto ptr = m_pDataMgr->GetCodePointer(trycode);
		results.push_back(ptr);
//			mainGame->scrFilter->setVisible(false);
//			mainGame->scrFilter->setPos(0);
		myswprintf(result_string, L"%d", results.size());
		return;
	}
	if (filter_keyword[0] == 0)
		filter_keyword = 0;
	auto strpointer = m_pDataMgr->_strings.begin();
	for (code_pointer ptr = m_pDataMgr->_datas.begin();
			ptr != m_pDataMgr->_datas.end(); ++ptr, ++strpointer) {
		const CardDataC& data = ptr->second;
		const CardString& text = strpointer->second;
		if (data.type & TYPE_TOKEN)
			continue;
		switch (filter_type) {
		case 1: {
			int type2 = data.type & 0xe03ef1;
			if (!(data.type & TYPE_MONSTER)
					|| (filter_type2 == 0x21 && type2 != 0x21)
					|| (data.type & filter_type2) != filter_type2)
				continue;
			if (filter_race && data.race != filter_race)
				continue;
			if (filter_attrib && data.attribute != filter_attrib)
				continue;
			if (filter_atktype) {
				if ((filter_atktype == 1 && data.attack != filter_atk)
						|| (filter_atktype == 2 && data.attack < filter_atk)
						|| (filter_atktype == 3 && data.attack <= filter_atk)
						|| (filter_atktype == 4
								&& (data.attack > filter_atk || data.attack < 0))
						|| (filter_atktype == 5
								&& (data.attack >= filter_atk || data.attack < 0))
						|| (filter_atktype == 6 && data.attack != -2))
					continue;
			}
			if (filter_deftype) {
				if ((filter_deftype == 1 && data.defence != filter_def)
						|| (filter_deftype == 2 && data.defence < filter_def)
						|| (filter_deftype == 3 && data.defence <= filter_def)
						|| (filter_deftype == 4
								&& (data.defence > filter_def
										|| data.defence < 0))
						|| (filter_deftype == 5
								&& (data.defence >= filter_def
										|| data.defence < 0))
						|| (filter_deftype == 6 && data.defence != -2))
					continue;
			}
			if (filter_lvtype) {
				if ((filter_lvtype == 1 && data.level != filter_lv)
						|| (filter_lvtype == 2 && data.level < filter_lv)
						|| (filter_lvtype == 3 && data.level <= filter_lv)
						|| (filter_lvtype == 4 && data.level > filter_lv)
						|| (filter_lvtype == 5 && data.level >= filter_lv))
					continue;
			}
			break;
		}
		case 2: {
			if (!(data.type & TYPE_SPELL))
				continue;
			if (filter_type2 && data.type != filter_type2)
				continue;
			break;
		}
		case 3: {
			if (!(data.type & TYPE_TRAP))
				continue;
			if (filter_type2 && data.type != filter_type2)
				continue;
			break;
		}
		}
		if (filter_effect && !(data.category & filter_effect))
			continue;
		if (filter_lm) {
			if (filter_lm <= 3
					&& (!filterList->count(ptr->first)
							|| (*filterList)[ptr->first] != filter_lm - 1))
				continue;
			if (filter_lm == 4 && data.ot != 1)
				continue;
			if (filter_lm == 5 && data.ot != 2)
				continue;
		}
		if (filter_keyword) {
			if (!wcsstr(text.name, filter_keyword) == 0
					&& wcsstr(text.text, filter_keyword) == 0)
				continue;
		}
		results.push_back(ptr);
	}
	myswprintf(result_string, L"%d", results.size());
//	if (results.size() > 7) {
//		mainGame->scrFilter->setVisible(true);
//		mainGame->scrFilter->setMax(results.size() - 7);
//		mainGame->scrFilter->setPos(0);
//	} else {
//		mainGame->scrFilter->setVisible(false);
//		mainGame->scrFilter->setPos(0);
//	}
	std::sort(results.begin(), results.end(), YGOClientCard::deck_sort_lv);
}

void YGODeckBuilder::setAtkFilter(const wchar_t* atk_str) {
	if (*atk_str == 0)
		filter_atktype = 0;
	else {
		if (*atk_str == '=') {
			filter_atktype = 1;
			filter_atk = BufferIO::GetVal(atk_str + 1);
		} else if (*atk_str >= '0' && *atk_str <= '9') {
			filter_atktype = 1;
			filter_atk = BufferIO::GetVal(atk_str);
		} else if (*atk_str == '>') {
			if (*(atk_str + 1) == '=') {
				filter_atktype = 2;
				filter_atk = BufferIO::GetVal(atk_str + 2);
			} else {
				filter_atktype = 3;
				filter_atk = BufferIO::GetVal(atk_str + 1);
			}
		} else if (*atk_str == '<') {
			if (*(atk_str + 1) == '=') {
				filter_atktype = 4;
				filter_atk = BufferIO::GetVal(atk_str + 2);
			} else {
				filter_atktype = 5;
				filter_atk = BufferIO::GetVal(atk_str + 1);
			}
		} else if (*atk_str == '?') {
			filter_atktype = 6;
		} else
			filter_atktype = 0;
	}
}

void YGODeckBuilder::setDefFilter(const wchar_t* def_str) {
	if (*def_str == 0)
		filter_deftype = 0;
	else {
		if (*def_str == '=') {
			filter_deftype = 1;
			filter_def = BufferIO::GetVal(def_str + 1);
		} else if (*def_str >= '0' && *def_str <= '9') {
			filter_deftype = 1;
			filter_def = BufferIO::GetVal(def_str);
		} else if (*def_str == '>') {
			if (*(def_str + 1) == '=') {
				filter_deftype = 2;
				filter_def = BufferIO::GetVal(def_str + 2);
			} else {
				filter_deftype = 3;
				filter_def = BufferIO::GetVal(def_str + 1);
			}
		} else if (*def_str == '<') {
			if (*(def_str + 1) == '=') {
				filter_deftype = 4;
				filter_def = BufferIO::GetVal(def_str + 2);
			} else {
				filter_deftype = 5;
				filter_def = BufferIO::GetVal(def_str + 1);
			}
		} else if (*def_str == '?') {
			filter_deftype = 6;
		} else
			filter_deftype = 0;
	}
}

void YGODeckBuilder::setLvFilter(const wchar_t* lv_str) {
	if (*lv_str == 0)
		filter_lvtype = 0;
	else {
		if (*lv_str == '=') {
			filter_lvtype = 1;
			filter_lv = BufferIO::GetVal(lv_str + 1);
		} else if (*lv_str >= '0' && *lv_str <= '9') {
			filter_lvtype = 1;
			filter_lv = BufferIO::GetVal(lv_str);
		} else if (*lv_str == '>') {
			if (*(lv_str + 1) == '=') {
				filter_lvtype = 2;
				filter_lv = BufferIO::GetVal(lv_str + 2);
			} else {
				filter_lvtype = 3;
				filter_lv = BufferIO::GetVal(lv_str + 1);
			}
		} else if (*lv_str == '<') {
			if (*(lv_str + 1) == '=') {
				filter_lvtype = 4;
				filter_lv = BufferIO::GetVal(lv_str + 2);
			} else {
				filter_lvtype = 5;
				filter_lv = BufferIO::GetVal(lv_str + 1);
			}
		} else
			filter_lvtype = 0;
	}
}

} /* namespace ygo */
