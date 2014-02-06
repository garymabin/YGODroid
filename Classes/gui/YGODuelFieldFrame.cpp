/*
 * YGODuelFieldFrame.cpp
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#include "YGODuelFieldFrame.h"

namespace ygo {

YGODuelFieldFrame::YGODuelFieldFrame() {
	// TODO Auto-generated constructor stub
	m_pDeckMgr = YGODeckManager::sharedDeckManager();
}

YGODuelFieldFrame::~YGODuelFieldFrame() {
	// TODO Auto-generated destructor stub
}

bool YGODuelFieldFrame::init() {
	bool bRet = false;
	do {
		if (!CCLayer::init()) {
			return false;
		}
		m_pDeckMgr->RefreshDeckList(&m_pDeckNameList);
		CCLOG("first deck name = %s", (*m_pDeckNameList.begin())->getCString());
		Config config = YGOGameConfig::sharedGameConfig()->getCommonConfig();
		m_pDeckMgr->LoadDeck(
				config.lastdeck[0] == '\0' ?
						(*m_pDeckNameList.begin())->getCString() :
						config.lastdeck);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		m_pWidgetContainer = TouchGroup::create();
		m_pWidgetContainer->retain();
		Widget* panel = GUIReader::shareReader()->widgetFromJsonFile(
				"ygocore_duel_field_frame.json");
		CCSize mainPanelSize = panel->getContentSize();
		panel->setScaleX(visibleSize.width / mainPanelSize.width);
		panel->setScaleY(visibleSize.height / mainPanelSize.height);
		panel->setAnchorPoint(ccp(0.5, 0.5));
		panel->setPosition(ccp (visibleSize.width/2, visibleSize.height/2));
		m_pWidgetContainer->addWidget(panel);
		m_pWidgetContainer->setPosition(CCPointZero);
		this->addChild(m_pWidgetContainer);

		Widget* pCardFieldPanel = dynamic_cast<Widget*>(panel->getChildByTag(
				DUEL_FIELD_IMAGE_DUEL_FIELD));
		CCCamera* camera = pCardFieldPanel->getCamera();
		float x = 0, y = 0, z = 0;
		camera->getEyeXYZ(&x, &y, &z);
		CCLOG("camera x =%f, y=%f, z=%f", x, y, z);
		camera->setCenterXYZ(x - 0.000001, y + 0.0001, z + 0.0001);

		Widget* pCardInHandPanel = dynamic_cast<Widget*>(panel->getChildByTag(
				DUEL_FIELD_PANEL_CARD_IN_HAND));
		CC_BREAK_IF(!pCardInHandPanel);
		std::vector<code_pointer> data;
		for (int i = 0; i < 5; i++) {
			data.push_back(m_pDeckMgr->current_deck.main.at(i));
		}
		YGOCardDeck* deck = YGOCardDeck::create(&data, 5, 1, -1,
				CCSizeMake(61, 89), false);
		YGOHandCardList * pHandCard = YGOHandCardList::create(
				pCardInHandPanel->getContentSize());
		pHandCard->setPosition(CCPointZero);
		pCardInHandPanel->addChild(pHandCard);
		pHandCard->setDataSource(deck);
		bRet = true;

	} while (0);
	return bRet;
}

} /* namespace ygo */
