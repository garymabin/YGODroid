/*
 * YGODeckEditLayer.h
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#ifndef YGODECKEDITLAYER_H_
#define YGODECKEDITLAYER_H_

#include "CommonGui.h"
#include "YGOMainScene.h"
#include "YGOCardDeckGrid.h"
#include "YGOCardCell.h"
#include "YGOCardDeck.h"
#include "XMLParser.h"
#include "DropDownList.h"
#include "YGODeckManager.h"
#include "YGOGameConfig.h"
#include "YGOClientCard.h"
#include "../ocgcore/card.h"
#include "YGODeckBuilder.h"

USING_NS_CC;
using namespace gui;
using namespace extension;
using namespace std;

namespace ygo {

class YGODeckEditLayer: public cocos2d::CCLayerColor {
public:
	YGODeckEditLayer();
	virtual ~YGODeckEditLayer();
	virtual bool init();
	CREATE_FUNC(YGODeckEditLayer);
	void buttonDeckEditCallback(CCObject* pSender, TouchEventType type);
	void dropdownListDeckEditCallback(CCObject* pSender);
	void gridcellSelectedDeckEditCallback(CCObject* pSender);
protected:
	virtual void onEvent(int tag);
private:
	YGODeckManager* m_pDeckMgr;
	TouchGroup* m_pWidgetContainer;
	YGOCardDeckGrid* m_pMainDeckGrid;
	YGOCardDeckGrid* m_pExtraDeckGrid;
	YGOCardDeckGrid* m_pSideDeckGrid;

	//卡片大图
	YGOCardCell* m_pCardDetail;
	//禁限卡表
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListLimitDetail, LimitDetailList);
	//卡组列表
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListDeckDetail, DecksDetailList);
	//卡组列表（数据源）
	std::vector<CCString*> m_pDeckNameList;
	//另存为(编辑框)
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxSaveAs, SaveAsEditBox);
	//另存为
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonSaveAs, SaveAsButton);
	//保存
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonSave, SaveButton);
	//退出编辑
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonQuit, QuitEditButton);
	//打乱
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonShuffle, ShuffleButton);
	//排序
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonSort, SortButton);
	//清空
	CC_SYNTHESIZE_READONLY(Button*, m_pButtonClean, CleanButton);
	//种类
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListCateFilter, CategoryFilterList);
	//种类详细
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListCateDetailFilter, CategoryDetailFilterList);
	//属性
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListPropertyFilter, PropertyFilterList);
	//种族
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListRaceFilter, RaceFilterList);
	//星数/等级
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxStarFilter, StarFilterEditBox);
	//禁限
	CC_SYNTHESIZE_READONLY(DropDownList *, m_pListCardLimitFilter, CardLimitFilterList);
	//攻击
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxAtkFilter, AtkFilterEditBox);
	//防御
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxDefFilter, DefFilterEditBox);
	//关键字
	CC_SYNTHESIZE_READONLY(CCEditBox *, m_pEditBoxKeywordFilter, KeywordFilterEditBox);
	//效果
	CC_SYNTHESIZE_READONLY(Button *, m_pButtonEffectsFilter, EffectsFilterButton);
	//重新搜索
	CC_SYNTHESIZE_READONLY(Button *, m_pSearchButton, SearchButton);
};

} /* namespace ygo */
#endif /* YGODECKEDITLAYER_H_ */
