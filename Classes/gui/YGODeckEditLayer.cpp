/*
 * YGODeckEditLayer.cpp
 *
 *  Created on: 2014年1月26日
 *      Author: mabin
 */

#include "YGODeckEditLayer.h"

USING_NS_CC;
using namespace gui;
using namespace extension;
using namespace std;

namespace ygo {

YGODeckEditLayer::YGODeckEditLayer() :
		m_pMainDeckGrid(NULL), m_pExtraDeckGrid(NULL), m_pSideDeckGrid(NULL), m_pWidgetContainer(
				NULL) {
	// TODO Auto-generated constructor stub
	m_pDeckMgr = YGODeckManager::sharedDeckManager();

}

YGODeckEditLayer::~YGODeckEditLayer() {
	// TODO Auto-generated destructor stub
	m_pWidgetContainer->clear();
	m_pWidgetContainer->release();
}

void YGODeckEditLayer::dropdownListDeckEditCallback(CCObject* pSender) {
	onEvent(dynamic_cast<CCSprite*>(pSender)->getTag());
}

bool YGODeckEditLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(153, 153, 153, 77))) {
		return false;
	}
	//数据初始化
	m_pDeckMgr->RefreshDeckList(&m_pDeckNameList);
	CCLOG("first deck name = %s", (*m_pDeckNameList.begin())->getCString());
	Config config = YGOGameConfig::sharedGameConfig()->getCommonConfig();
	m_pDeckMgr->LoadDeck(
			config.lastdeck[0] == '\0' ?
					(*m_pDeckNameList.begin())->getCString() : config.lastdeck);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pWidgetContainer = TouchGroup::create();
	m_pWidgetContainer->retain();
	Widget* pPanel = GUIReader::shareReader()->widgetFromJsonFile(
			"ygocore_deck_edit.json");
	CCSize mainPanelSize = pPanel->getContentSize();
	pPanel->setScaleX(visibleSize.width/mainPanelSize.width);
	pPanel->setScaleY(visibleSize.height/mainPanelSize.height);
	m_pWidgetContainer->addWidget(pPanel);
	CCLOG("current touch priority is %d", m_pWidgetContainer->getTouchPriority());
	//初始化UI控件
	//主卡组
	Widget* pMainDeckWidget = dynamic_cast<Widget *>(pPanel->getChildByTag(
			DECK_EDIT_PANEL_MAIN_DECK));
	YGOCardDeck* pMainDeck = YGOCardDeck::create(&m_pDeckMgr->current_deck.main,
			10, 4, 60, CCSizeMake(44, 64));
	CCSize tempSize = pMainDeckWidget->getContentSize();
	m_pMainDeckGrid = YGOCardDeckGrid::create(tempSize);
	m_pMainDeckGrid->setPosition(CCPointZero);
	pMainDeckWidget->addChild(m_pMainDeckGrid);
	m_pMainDeckGrid->setDataSource(pMainDeck);
	m_pMainDeckGrid->addChildTouchedObserver(this, callfuncO_selector(YGODeckEditLayer::gridcellSelectedDeckEditCallback));

	//卡片大图
	Widget* pCardDetailWidget = dynamic_cast<Widget *>(pPanel->getChildByTag(
				DECK_EDIT_PANEL_CARD_DETAIL));
	m_pCardDetail = YGOCardCell::create(*(m_pDeckMgr->current_deck.main.begin()), false);
	m_pCardDetail->setPosition(CCPointZero);
	pCardDetailWidget->addChild(m_pCardDetail);

	//额外卡组
	Widget* pExtraDeckWidget = dynamic_cast<Widget *>(pPanel->getChildByTag(
			DECK_EDIT_PANEL_EXTRA_DECK));
	YGOCardDeck* pExtraDeck = YGOCardDeck::create(
			&m_pDeckMgr->current_deck.extra, 10, 1, 15, CCSizeMake(44, 64));
	tempSize = pExtraDeckWidget->getContentSize();
	m_pExtraDeckGrid = YGOCardDeckGrid::create(tempSize);
	m_pExtraDeckGrid->setPosition(CCPointZero);
	pExtraDeckWidget->addChild(m_pExtraDeckGrid);
	m_pExtraDeckGrid->setDataSource(pExtraDeck);
	m_pExtraDeckGrid->addChildTouchedObserver(this, callfuncO_selector(YGODeckEditLayer::gridcellSelectedDeckEditCallback));

	//副卡组
	Widget* pSideDeckWidget = dynamic_cast<Widget *>(pPanel->getChildByTag(
			DECK_EDIT_PANEL_SIDE_DECK));
	YGOCardDeck* pSideDeck = YGOCardDeck::create(&m_pDeckMgr->current_deck.side,
			10, 1, 15, CCSizeMake(44, 64));
	tempSize = pSideDeckWidget->getContentSize();
	m_pSideDeckGrid = YGOCardDeckGrid::create(tempSize);
	m_pSideDeckGrid->setPosition(CCPointZero);
	pSideDeckWidget->addChild(m_pSideDeckGrid);
	m_pSideDeckGrid->setDataSource(pSideDeck);
	m_pSideDeckGrid->addChildTouchedObserver(this, callfuncO_selector(YGODeckEditLayer::gridcellSelectedDeckEditCallback));

	//卡组相关区域
	Widget* pDeckRelatePanel = dynamic_cast<Widget *>(pPanel->getChildByTag(
			DECK_EDIT_DECK_RELATE_PANEL));

	//禁限卡表
	Label* pLimitListLabel =
			dynamic_cast<Label *>(pDeckRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_LIMIT_LIST));
	string tempStr =
			::XMLParser::sharedXMLParser()->getString("limit_list")->getCString();
	pLimitListLabel->setText(tempStr);
	Widget* pLimitListPanel =
			dynamic_cast<Widget *>(pDeckRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_LIMIT_DETAIL));
	vector<CCString*> liststrs;
	liststrs.push_back(CCString::createWithFormat("%s", "2013.9"));
	liststrs.push_back(CCString::createWithFormat("%s", "2013.3"));
	liststrs.push_back(CCString::createWithFormat("%s", "2012.9"));
	liststrs.push_back(CCString::createWithFormat("%s", "2012.3"));
	tempSize = pLimitListPanel->getContentSize();
	m_pListLimitDetail = DropDownList::create((*liststrs.begin())->getCString(),
			&liststrs, tempSize, 20);
	m_pListLimitDetail->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListLimitDetail->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListLimitDetail->setTag(DECK_EDIT_LABEL_LIMIT_LIST);
	pLimitListPanel->addNode(m_pListLimitDetail);

	//卡组列表
	Label* pDeckListLabel =
			dynamic_cast<Label *>(pDeckRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_DECK_LIST));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("deck_list")->getCString();
	pDeckListLabel->setText(tempStr);
	Widget* pDeckListPanel =
			dynamic_cast<Widget *>(pDeckRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_DECK_DETAIL));
	tempSize = pDeckListPanel->getContentSize();
	m_pListDeckDetail = DropDownList::create(
			(*m_pDeckNameList.begin())->getCString(), &m_pDeckNameList,
			tempSize, 20);
	m_pListDeckDetail->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListDeckDetail->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListDeckDetail->setTag(DECK_EDIT_PANEL_DECK_DETAIL);
	pDeckListPanel->addNode(m_pListDeckDetail);

	//保存&另存为
	Widget* pSaveAsPanel =
			dynamic_cast<Widget *>(pDeckRelatePanel->getChildByTag(
					DECK_EDIT_TEXT_FIELD_SAVE_AS));
	tempSize = pSaveAsPanel->getContentSize();
	tempStr =
			::XMLParser::sharedXMLParser()->getString("save_as")->getCString();
	m_pEditBoxSaveAs = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	m_pEditBoxSaveAs->setFont("fonts/arial.ttf", 20);
	m_pEditBoxSaveAs->setPlaceHolder(tempStr.c_str());
	m_pEditBoxSaveAs->setPlaceholderFontColor(ccBLACK);
	m_pEditBoxSaveAs->setPlaceholderFontSize(20);
	m_pEditBoxSaveAs->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBoxSaveAs->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pEditBoxSaveAs->setTag(DECK_EDIT_TEXT_FIELD_SAVE_AS);
	pSaveAsPanel->addNode(m_pEditBoxSaveAs);

	m_pButtonSaveAs = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_SAVE_AS));
	m_pButtonSaveAs->setTitleText(tempStr);
	m_pButtonSaveAs->setScale9Enabled(true);
	m_pButtonSaveAs->setPressedActionEnabled(true);
	m_pButtonSaveAs->setTouchEnabled(true);
	m_pButtonSaveAs->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	tempStr = ::XMLParser::sharedXMLParser()->getString("save")->getCString();

	m_pButtonSave = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_SAVE));
	m_pButtonSave->setTitleText(tempStr);
	m_pButtonSave->setScale9Enabled(true);
	m_pButtonSave->setPressedActionEnabled(true);
	m_pButtonSave->setTouchEnabled(true);
	m_pButtonSave->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));

	tempStr =
			::XMLParser::sharedXMLParser()->getString("quit_edit")->getCString();
	m_pButtonQuit = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_QUIT));
	m_pButtonQuit->setTitleText(tempStr);
	m_pButtonQuit->setScale9Enabled(true);
	m_pButtonQuit->setPressedActionEnabled(true);
	m_pButtonQuit->setTouchEnabled(true);
	m_pButtonQuit->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("shuffle_deck")->getCString();
	m_pButtonShuffle = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_SHUFFLE_DECK));
	m_pButtonShuffle->setTitleText(tempStr);
	m_pButtonShuffle->setScale9Enabled(true);
	m_pButtonShuffle->setPressedActionEnabled(true);
	m_pButtonShuffle->setTouchEnabled(true);
	m_pButtonShuffle->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("sort_deck")->getCString();
	m_pButtonSort = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_SORT_DECK));
	m_pButtonSort->setTitleText(tempStr);
	m_pButtonSort->setScale9Enabled(true);
	m_pButtonSort->setPressedActionEnabled(true);
	m_pButtonSort->setTouchEnabled(true);
	m_pButtonSort->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("clean_deck")->getCString();
	m_pButtonClean = dynamic_cast<Button *>(pDeckRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_CLEAN_DECK));
	m_pButtonClean->setTitleText(tempStr);
	m_pButtonClean->setScale9Enabled(true);
	m_pButtonClean->setPressedActionEnabled(true);
	m_pButtonClean->setTouchEnabled(true);
	m_pButtonClean->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	//卡片相关区域
	Widget* pFilterRelatePanel = dynamic_cast<Widget *>(pPanel->getChildByTag(
			DECK_EDIT_CARD_RELATE_PANEL));

	//种类
	Label* pCardCateLabel =
			dynamic_cast<Label *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_FILTER_CARD_CATEGORY));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("category")->getCString();
	pCardCateLabel->setText(tempStr);
	Widget* pCardCatePanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_CARD_CATEGORY));
	vector<CCString*> catestrs;
	catestrs.push_back(CCString::createWithFormat("%s", "(无)"));
	catestrs.push_back(CCString::createWithFormat("%s", "怪兽"));
	catestrs.push_back(CCString::createWithFormat("%s", "魔法"));
	catestrs.push_back(CCString::createWithFormat("%s", "陷阱"));
	tempSize = pCardCatePanel->getContentSize();
	m_pListCateFilter = DropDownList::create((*catestrs.begin())->getCString(),
			&catestrs, tempSize, 20);
	m_pListCateFilter->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListCateFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListCateFilter->setTag(DECK_EDIT_PANEL_FILTER_CARD_CATEGORY);
	pCardCatePanel->addNode(m_pListCateFilter);

	Widget* pCardCateDetailPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_CARD_CATEGORY_DETAIL));
	vector<CCString*> catedetailstrs;
	catedetailstrs.push_back(CCString::createWithFormat("%s", "(无)"));
	tempSize = pCardCateDetailPanel->getContentSize();
	m_pListCateDetailFilter = DropDownList::create(
			(*catedetailstrs.begin())->getCString(), &catedetailstrs, tempSize, 20);
	m_pListCateDetailFilter->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListCateDetailFilter->setPosition(
			ccp(tempSize.width/2, tempSize.height/2));
	m_pListCateDetailFilter->setTag(
			DECK_EDIT_PANEL_FILTER_CARD_CATEGORY_DETAIL);
	pCardCateDetailPanel->addNode(m_pListCateDetailFilter);
	//属性
	Label* pCardProperLabel =
			dynamic_cast<Label *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_FILTER_CARD_PROPERTY));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("property")->getCString();
	pCardProperLabel->setText(tempStr);
	Widget* pCardProperPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_PROPERTY));
	vector<CCString*> properstrs;
	properstrs.push_back(CCString::createWithFormat("%s", "(无)"));
	tempSize = pCardProperPanel->getContentSize();
	m_pListPropertyFilter = DropDownList::create(
			(*properstrs.begin())->getCString(), &properstrs, tempSize, 20);
	m_pListPropertyFilter->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListPropertyFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListPropertyFilter->setTag(DECK_EDIT_PANEL_FILTER_PROPERTY);
	pCardProperPanel->addNode(m_pListPropertyFilter);
	//种族
	Label* pCardRaceLabel =
			dynamic_cast<Label *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_FILTER_CARD_RACE));
	tempStr = ::XMLParser::sharedXMLParser()->getString("race")->getCString();
	pCardRaceLabel->setText(tempStr);
	Widget* pCardRacePanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_RACE));
	vector<CCString*> racestrs;
	racestrs.push_back(CCString::createWithFormat("%s", "(无)"));
	tempSize = pCardRacePanel->getContentSize();
	m_pListRaceFilter = DropDownList::create((*racestrs.begin())->getCString(),
			&racestrs, tempSize, 20);
	m_pListRaceFilter->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListRaceFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListRaceFilter->setTag(DECK_EDIT_PANEL_FILTER_RACE);
	pCardRacePanel->addNode(m_pListRaceFilter);
	//星数/等级
	Widget* pLevelPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_STAR));
	tempSize = pLevelPanel->getContentSize();
	tempStr = ::XMLParser::sharedXMLParser()->getString("star")->getCString();
	m_pEditBoxStarFilter = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	m_pEditBoxStarFilter->setFont("fonts/arial.ttf", 20);
	m_pEditBoxStarFilter->setPlaceHolder(tempStr.c_str());
	m_pEditBoxStarFilter->setPlaceholderFontColor(ccBLACK);
	m_pEditBoxStarFilter->setPlaceholderFontSize(20);
	m_pEditBoxStarFilter->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBoxStarFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pEditBoxStarFilter->setTag(DECK_EDIT_PANEL_FILTER_STAR);
	pLevelPanel->addNode(m_pEditBoxStarFilter);
	//禁限
	Label* pCardLimitLabel =
			dynamic_cast<Label *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_LABEL_FILTER_CARD_LIMIT));
	tempStr = ::XMLParser::sharedXMLParser()->getString("limit")->getCString();
	pCardLimitLabel->setText(tempStr);
	Widget* pCardLimitPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_CARD_LIMIT));
	vector<CCString*> limitstrs;
	limitstrs.push_back(CCString::createWithFormat("%s", "(无)"));
	tempSize = pCardLimitPanel->getContentSize();
	m_pListCardLimitFilter = DropDownList::create(
			(*limitstrs.begin())->getCString(), &limitstrs, tempSize, 20);
	m_pListCardLimitFilter->addClickObserver(this, callfuncO_selector(YGODeckEditLayer::dropdownListDeckEditCallback));
	m_pListCardLimitFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pListCardLimitFilter->setTag(DECK_EDIT_PANEL_FILTER_CARD_LIMIT);
	pCardLimitPanel->addNode(m_pListCardLimitFilter);
	//攻击&防御&关键字
	Widget* pAtkPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_ATK));
	tempStr = ::XMLParser::sharedXMLParser()->getString("attack")->getCString();
	tempSize = pAtkPanel->getContentSize();
	m_pEditBoxAtkFilter = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	m_pEditBoxAtkFilter->setFont("fonts/arial.ttf", 20);
	m_pEditBoxAtkFilter->setPlaceHolder(tempStr.c_str());
	m_pEditBoxAtkFilter->setPlaceholderFontColor(ccBLACK);
	m_pEditBoxAtkFilter->setPlaceholderFontSize(20);
	m_pEditBoxAtkFilter->setMaxLength(5);
	m_pEditBoxAtkFilter->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBoxAtkFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pEditBoxAtkFilter->setTag(DECK_EDIT_PANEL_FILTER_ATK);
	pAtkPanel->addNode(m_pEditBoxAtkFilter);
	Widget* pDefPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_DEF));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("defense")->getCString();
	tempSize = pDefPanel->getContentSize();
	m_pEditBoxDefFilter = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	m_pEditBoxDefFilter->setFont("fonts/arial.ttf", 20);
	m_pEditBoxDefFilter->setPlaceHolder(tempStr.c_str());
	m_pEditBoxDefFilter->setPlaceholderFontColor(ccBLACK);
	m_pEditBoxDefFilter->setPlaceholderFontSize(20);
	m_pEditBoxDefFilter->setMaxLength(5);
	m_pEditBoxDefFilter->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBoxDefFilter->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	m_pEditBoxDefFilter->setTag(DECK_EDIT_PANEL_FILTER_DEF);
	pDefPanel->addNode(m_pEditBoxDefFilter);

	Widget* pKeyPanel =
			dynamic_cast<Widget *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_PANEL_FILTER_KEYWORD));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("keyword")->getCString();
	tempSize = pKeyPanel->getContentSize();
	m_pEditBoxKeywordFilter = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	m_pEditBoxKeywordFilter->setFont("fonts/arial.ttf", 20);
	m_pEditBoxKeywordFilter->setPlaceHolder(tempStr.c_str());
	m_pEditBoxKeywordFilter->setPlaceholderFontColor(ccBLACK);
	m_pEditBoxKeywordFilter->setPlaceholderFontSize(20);
	m_pEditBoxKeywordFilter->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBoxKeywordFilter->setPosition(
			ccp(tempSize.width/2, tempSize.height/2));
	m_pEditBoxKeywordFilter->setTag(DECK_EDIT_PANEL_FILTER_KEYWORD);
	pKeyPanel->addNode(m_pEditBoxKeywordFilter);
	//效果&重新搜索
	tempStr =
			::XMLParser::sharedXMLParser()->getString("effects")->getCString();
	m_pButtonEffectsFilter =
			dynamic_cast<Button *>(pFilterRelatePanel->getChildByTag(
					DECK_EDIT_BUTTON_EFFECT));
	m_pButtonEffectsFilter->setTitleText(tempStr);
	m_pButtonEffectsFilter->setScale9Enabled(true);
	m_pButtonEffectsFilter->setPressedActionEnabled(true);
	m_pButtonEffectsFilter->setTouchEnabled(true);
	m_pButtonEffectsFilter->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("restart_search")->getCString();
	m_pSearchButton = dynamic_cast<Button *>(pFilterRelatePanel->getChildByTag(
			DECK_EDIT_BUTTON_RESTART_SEARCH));
	m_pSearchButton->setTitleText(tempStr);
	m_pSearchButton->setScale9Enabled(true);
	m_pSearchButton->setPressedActionEnabled(true);
	m_pSearchButton->setTouchEnabled(true);
	m_pSearchButton->addTouchEventListener(this,
			toucheventselector(YGODeckEditLayer::buttonDeckEditCallback));
	//其他label
	Label* pMainDeckLabel = dynamic_cast<Label *>(pPanel->getChildByTag(
			DECK_EDIT_LABEL_MAIN_DECK));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("main_deck")->getCString();
	pMainDeckLabel->setText(tempStr);
	Label* pExtraDeckLabel = dynamic_cast<Label *>(pPanel->getChildByTag(
			DECK_EDIT_LABEL_MAIN_DECK));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("extra_deck")->getCString();
	pExtraDeckLabel->setText(tempStr);
	Label* pSideDeckLabel = dynamic_cast<Label *>(pPanel->getChildByTag(
			DECK_EDIT_LABEL_MAIN_DECK));
	tempStr =
			::XMLParser::sharedXMLParser()->getString("side_deck")->getCString();
	pSideDeckLabel->setText(tempStr);

	m_pWidgetContainer->setPosition(CCPointZero);
	this->addChild(m_pWidgetContainer);
	return true;
}

void YGODeckEditLayer::buttonDeckEditCallback(CCObject* pSender,
		cocos2d::gui::TouchEventType type) {
	static bool button_pressed = false;
	switch (type) {
	case TOUCH_EVENT_BEGAN:
		CCLOG("TOUCH_EVENT_BEGAN, pressed = %d", button_pressed);
	case TOUCH_EVENT_MOVED:
		CCLOG("TOUCH_EVENT_MOVED, pressed = %d", button_pressed);
		button_pressed = true;
		break;
	case TOUCH_EVENT_ENDED:
		CCLOG("TOUCH_EVENT_ENDED, pressed = %d", button_pressed);
		if (button_pressed) {
			onEvent(dynamic_cast<Button *>(pSender)->getTag());
			button_pressed = false;
		}
		break;
	case TOUCH_EVENT_CANCELED:
		CCLOG("TOUCH_EVENT_CANCELED, pressed = %d", button_pressed);
		button_pressed = false;
		break;
	}
}

void YGODeckEditLayer::gridcellSelectedDeckEditCallback(CCObject* pSender) {
	YGOCardCell* pCell = dynamic_cast<YGOCardCell*>(pSender);
	if (pCell) {
		m_pCardDetail->resetWithData(pCell->getCard());
	}
}

void YGODeckEditLayer::onEvent(int tag) {
	CCLOG("YGODeckEditLayer::onEvent, Enter()");
	switch (tag) {
	case DECK_EDIT_BUTTON_CLEAN_DECK: {
		m_pDeckMgr->current_deck.clear();
		break;
	}
	case DECK_EDIT_BUTTON_SORT_DECK: {
		std::sort(m_pDeckMgr->current_deck.main.begin(),
				m_pDeckMgr->current_deck.main.end(),
				YGOClientCard::deck_sort_lv);
		std::sort(m_pDeckMgr->current_deck.extra.begin(),
				m_pDeckMgr->current_deck.extra.end(),
				YGOClientCard::deck_sort_lv);
		std::sort(m_pDeckMgr->current_deck.side.begin(),
				m_pDeckMgr->current_deck.side.end(),
				YGOClientCard::deck_sort_lv);
		break;
	}
	case DECK_EDIT_BUTTON_SHUFFLE_DECK: {
		std::random_shuffle(m_pDeckMgr->current_deck.main.begin(),
				m_pDeckMgr->current_deck.main.end());
		break;
	}
	case DECK_EDIT_BUTTON_SAVE: {
		if (m_pDeckMgr->SaveDeck(m_pDeckMgr->current_deck,
				m_pListDeckDetail->getCurrentText())) {
			//TODO:弹出提示
//			mainGame->stACMessage->setText(dataManager.GetSysString(1335));
//			mainGame->PopupElement(mainGame->wACMessage, 20);
		}
		break;
	}
	case DECK_EDIT_BUTTON_SAVE_AS: {
		const char* dname = m_pEditBoxSaveAs->getText();
		if (*dname == 0)
			break;
		int sel = -1;
		for (size_t i = 0; i < m_pListDeckDetail->getItemCount(); ++i) {
			if (!strcmp(dname, m_pListDeckDetail->getItemText(i))) {
				sel = i;
				break;
			}
		}
		if (sel >= 0)
			m_pListDeckDetail->setSelected(sel);
		else {
			m_pListDeckDetail->pushBackItem(dname);
			m_pListDeckDetail->setSelected(
					m_pListDeckDetail->getItemCount() - 1);
		}
		if (m_pDeckMgr->SaveDeck(m_pDeckMgr->current_deck, dname)) {
			//TODO:弹出提示
//			mainGame->stACMessage->setText(dataManager.GetSysString(1335));
//			mainGame->PopupElement(mainGame->wACMessage, 20);
		}
		break;
	}
	case DECK_EDIT_BUTTON_QUIT: {
		CCScene* currentScene = CCDirector::sharedDirector()->getRunningScene();
//		mainGame->is_building = false;
//		mainGame->wDeckEdit->setVisible(false);
//		mainGame->wCategories->setVisible(false);
//		mainGame->wFilter->setVisible(false);
//		mainGame->wCardImg->setVisible(false);
//		mainGame->wInfos->setVisible(false);
//		mainGame->PopupElement(mainGame->wMainMenu);
//		mainGame->device->setEventReceiver(&mainGame->menuHandler);
//		mainGame->wACMessage->setVisible(false);
//		imageManager.ClearTexture();
//		mainGame->scrFilter->setVisible(false);
		YGOGameConfig* gameConfig = YGOGameConfig::sharedGameConfig();
		if (m_pListDeckDetail->getSelected() != -1) {
			strncpy((char *) gameConfig->getCommonConfig().lastdeck,
					m_pListDeckDetail->getCurrentText(), 64);
		}
		currentScene->removeChild(this);
		YGOMainMenuLayer* layer = YGOMainMenuLayer::create();
		layer->setTag(MAIN_MENU_LAYER);
		currentScene->addChild(layer);
//		if (exit_on_return)
//			mainGame->device->closeDevice();
		break;
	}
	case DECK_EDIT_BUTTON_EFFECT: {
		//TODO:弹出效果选择界面
//		mainGame->PopupElement(mainGame->wCategories);
		break;
	}
	case DECK_EDIT_BUTTON_RESTART_SEARCH: {
		wchar_t tmp_buff[256];
		wmemset(tmp_buff, L'\0', 256);
		YGODeckBuilder* pDeckBuilder = YGODeckBuilder::create();
		pDeckBuilder->setFilterType(m_pListCateFilter->getSelected());
		pDeckBuilder->setFilterType2(m_pListCateDetailFilter->getSelected());
		pDeckBuilder->setFilterLm(m_pListCardLimitFilter->getSelected());
		const char* keyword = m_pEditBoxKeywordFilter->getText();
		mbstowcs(tmp_buff, keyword, (strlen(keyword) + 1) * 2);
		pDeckBuilder->setFilterKeyword(tmp_buff);
		if (m_pListCateFilter->getSelected() > TYPE_MONSTER) {
			pDeckBuilder->FilterCards();
		} else {
			pDeckBuilder->setFilterRace(m_pListRaceFilter->getSelected());
			pDeckBuilder->setFilterAttrib(m_pListPropertyFilter->getSelected());
			wmemset(tmp_buff, L'\0', 256);
			const char* atk = m_pEditBoxAtkFilter->getText();
			mbstowcs(tmp_buff, atk, (strlen(atk) + 1) * 2);
			pDeckBuilder->setAtkFilter(tmp_buff);
			wmemset(tmp_buff, L'\0', 256);
			const char* def = m_pEditBoxDefFilter->getText();
			mbstowcs(tmp_buff, def, (strlen(def) + 1) * 2);
			pDeckBuilder->setDefFilter(tmp_buff);
			wmemset(tmp_buff, L'\0', 256);
			const char* lv = m_pEditBoxStarFilter->getText();
			mbstowcs(tmp_buff, lv, (strlen(lv) + 1) * 2);
			pDeckBuilder->setLvFilter(tmp_buff);
			pDeckBuilder->FilterCards();
		}
		break;
	}
	case DECK_EDIT_PANEL_DECK_DETAIL: {
		const char* str = m_pListDeckDetail->getCurrentText();
		CCLOG("m_pListDeckDetail->getCurrentText()) = %s", str);
		m_pDeckMgr->LoadDeck(m_pListDeckDetail->getCurrentText());
		YGOCardDeck* pMainDeck = YGOCardDeck::create(
				&m_pDeckMgr->current_deck.main, 10, 4, 60, CCSizeMake(44, 64));
		YGOCardDeck* pExtraDeck = YGOCardDeck::create(
				&m_pDeckMgr->current_deck.extra, 10, 1, 15, CCSizeMake(44, 64));
		YGOCardDeck* pSideDeck = YGOCardDeck::create(
				&m_pDeckMgr->current_deck.side, 10, 1, 15, CCSizeMake(44, 64));
		m_pMainDeckGrid->setDataSource(pMainDeck);
		m_pExtraDeckGrid->setDataSource(pExtraDeck);
		m_pSideDeckGrid->setDataSource(pSideDeck);
		m_pCardDetail->resetWithData(*(m_pDeckMgr->current_deck.main.begin()));
		break;
	}
	default:
		break;
	}
}

} /* namespace ygo */
