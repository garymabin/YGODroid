/*
 * YGODuelFieldFrame.cpp
 *
 *  Created on: 2014年2月5日
 *      Author: mabin
 */

#include "YGODuelFieldFrame.h"

#include "YGODuelField.h"
#include "YGOMainScene.h"

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
		YGODuelField* pDuelField = YGODuelField::create();
		pDuelField->setPosition(CCPointZero);
		pCardFieldPanel->addChild(pDuelField);

//		CCCamera* camera = pCardFieldPanel->getCamera();
//		float x = 0, y = 0, z = 0;
//		camera->getCenterXYZ(&x, &y, &z);
//		CCLOG("camera x =%f, y=%f, z=%f", x, y, z);
//		camera->setCenterXYZ(x, y + 0.0001, z + 0.0001);

		//己方手牌
		Widget* pCardInHandPanel = dynamic_cast<Widget*>(panel->getChildByTag(
				DUEL_FIELD_PANEL_CARD_IN_HAND1));
		CC_BREAK_IF(!pCardInHandPanel);
		std::vector<code_pointer> data;
		for (int i = 0; i < 5; i++) {
			data.push_back(m_pDeckMgr->current_deck.main.at(i));
		}
		YGOCardDeck* deck = YGOCardDeck::create(&data, 5, 1, -1,
				CCSizeMake(61, 89), false);
		CCSize tempSize = pCardInHandPanel->getContentSize();
		YGOHandCardList * pHandCard = YGOHandCardList::create(
				tempSize);
		pHandCard->setPosition(CCPointZero);
		pCardInHandPanel->addChild(pHandCard);
		pHandCard->setDataSource(deck);
		pHandCard->addChildTouchedObserver(this,callfuncO_selector(YGODuelFieldFrame::widgetTouchedCallBack));
		pHandCard->addChildDraggedObserver(this, callfuncND_selector(YGODuelFieldFrame::cardInHandDraggedCallBack));
		bRet = true;
		m_pSurranderButton = addNewButton(panel, DUEL_FIELD_BUTTON_SURRENDER, "surrander");

		//大图区
		Widget* pCardDetailPanel = dynamic_cast<Widget *>(panel->getChildByTag(DUEL_FIELD_IMAGE_CARD_DETAIL));
		CC_BREAK_IF(!pCardDetailPanel);

	} while (0);
	return bRet;
}

void YGODuelFieldFrame::cardInHandDraggedCallBack(CCObject* pSender,
		void* param) {
	CCLOG("cardInHand dragged!");
	CCPoint point = this->convertToNodeSpace(*((CCPoint*)param));
//	YGOCardCell* card = (YGOCardCell*)pSender;
	std::vector<CCString*> strings;
	strings.push_back(CCString::create("盖放"));
	m_pCardOpsPanel = YGOCardOpsPanel::createWithItems("orange_edit.png", &strings, 30);
	m_pCardOpsPanel->setPosition(point);
	m_pCardOpsPanel->addItemSelectedListener(this, callfuncND_selector(YGODuelFieldFrame::menuItemCallback));
	addChild(m_pCardOpsPanel, 100);
}

void YGODuelFieldFrame::widgetTouchedCallBack(CCObject* pSender) {
	CCLOG("cardInHand touched!");
}

void YGODuelFieldFrame::menuItemCallback(CCObject* pSender, void * param) {
	CCLOG("menuButtonCallback called!");
	removeChild(m_pCardOpsPanel);
}

void YGODuelFieldFrame::buttonCallback(CCObject* pSender,
		TouchEventType type) {
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
			onEvent(dynamic_cast<Button*>(pSender)->getTag());
			button_pressed = false;
		}
		break;
	case TOUCH_EVENT_CANCELED:
		CCLOG("TOUCH_EVENT_CANCELED, pressed = %d", button_pressed);
		button_pressed = false;
		break;
	}
}

inline Button* YGODuelFieldFrame::addNewButton(Widget* container, int tag,
		const char* key) {
	std::string tempStr =
			XMLParser::sharedXMLParser()->getString(key)->getCString();
	Button* pButton = dynamic_cast<Button*>(container->getChildByTag(tag));
	pButton->setTitleText(tempStr);
	pButton->setScale9Enabled(true);
	pButton->setTouchEnabled(true);
	pButton->setPressedActionEnabled(true);
	pButton->addTouchEventListener(this,
			toucheventselector(YGODuelFieldFrame::buttonCallback));
	return pButton;
}

void YGODuelFieldFrame::onEvent(int tag) {
	switch (tag) {
		case DUEL_FIELD_BUTTON_SURRENDER:
			CCDirector::sharedDirector()->replaceScene(YGOMainScene::create());
			break;
		default:
			break;
	}
}

} /* namespace ygo */
