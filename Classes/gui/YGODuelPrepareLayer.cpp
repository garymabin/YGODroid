/*
 * YGODuelPrepareLayer.cpp
 *
 *  Created on: 2014年2月4日
 *      Author: mabin
 */

#include "YGODuelPrepareLayer.h"

namespace ygo {

YGODuelPrepareLayer::YGODuelPrepareLayer() {
	// TODO Auto-generated constructor stub
	m_pDeckMgr = YGODeckManager::sharedDeckManager();
}

YGODuelPrepareLayer::~YGODuelPrepareLayer() {
	// TODO Auto-generated destructor stub
	m_pWidgetContainer->clear();
	m_pWidgetContainer->release();
}

bool YGODuelPrepareLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(153, 153, 153, 77))) {
			return false;
	}
	//初始化数据
	m_pDeckMgr->RefreshDeckList(&m_deckNameList);
	//初始化UI
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pWidgetContainer = TouchGroup::create();
	m_pWidgetContainer->retain();
	Widget* panel = GUIReader::shareReader()->widgetFromJsonFile(
				"ygocore_lan_mode_duel_preparation.json");
	CCSize mainPanelSize = panel->getContentSize();
	m_pWidgetContainer->setPosition(CCPointZero);
	panel->setScaleX(visibleSize.width/mainPanelSize.width);
	panel->setScaleY(visibleSize.height/mainPanelSize.height);
	panel->setAnchorPoint(ccp(0.5, 0.5));
	panel->setPosition(ccp (visibleSize.width/2, visibleSize.height/2));
	m_pWidgetContainer->addWidget(panel);
	this->addChild(m_pWidgetContainer);
	Widget* infoPanel= dynamic_cast<Widget*>(panel->getChildByTag(DUEL_PREPARE_PANEL_DUEL_INFO));
	//标签
	addNewLabel(panel, DUEL_PREPARE_LABEL_DECK_LIST, "deck_list");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_CARD_ALLOWED, "card_allowed");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_DRAW_EACH_ROUND, "draw_each_round");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_DUEL_MODE, "duel_mode");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_INITIAL_CARD_IN_HAND, "initial_card_in_hand");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_INITIAL_LIFE_POINTS, "initial_life_points");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_LIMIT_EACH_ROUND, "time_limit_each_round");
	addNewLabel(infoPanel, DUEL_PREPARE_LABEL_INFO_LIMIT_LIST, "limit_list");
	addNewLabel(panel, DUEL_PREPARE_LABEL_NICK_NAME_1, "categor_none");
	addNewLabel(panel, DUEL_PREPARE_LABEL_NICK_NAME_2, "categor_none");
	//按钮
	m_pButtonCancel = addNewButton(panel, DUEL_PREPARE_BUTTON_CANCEL, "cancel");
	m_pButtonStart = addNewButton(panel, DUEL_PREPARE_BUTTON_START, "start");
	addNewButton(panel, DUEL_PREPARE_BUTTON_KICK_1);
	addNewButton(panel, DUEL_PREPARE_BUTTON_KICK_2);
	addNewButton(panel, DUEL_PREPARE_BUTTON_DUELIST, "duelist");
	addNewButton(panel, DUEL_PREPARE_BUTTON_WATCH_DUEL, "watch_duel");
	//单选框
	addNewCheckBox(panel, DUEL_PREPARE_CHECKBOX_1);
	addNewCheckBox(panel, DUEL_PREPARE_CHECKBOX_2);
	//编辑框
	addNewEditBox(panel, DUEL_PREPARE_TEXTFIELD_CHAT);
	//下拉框
	addNewDropDownList(panel, DUEL_PREPARE_LIST_DECK_LIST, &m_deckNameList);

	return true;
}

void YGODuelPrepareLayer::dropdownListCallback(CCObject* pSender) {
	onEvent(dynamic_cast<DropDownList*>(pSender)->getTag());
}

void YGODuelPrepareLayer::buttonCallback(CCObject* pSender,
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

void YGODuelPrepareLayer::onEvent(int tag) {
	switch (tag) {
		case DUEL_PREPARE_BUTTON_START: {
			CCDirector::sharedDirector()->replaceScene(YGODuelScene::create());
			break;
		}
		case DUEL_PREPARE_BUTTON_CANCEL: {
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
			scene->removeChild(this);
			scene->addChild(YGOLANModeLayer::create());
			break;
		}
		default:
			break;
	}
}

inline Label* YGODuelPrepareLayer::addNewLabel(Widget* container, int tag,
		const char* key) {
	std::string tempStr =
			XMLParser::sharedXMLParser()->getString(key)->getCString();
	Label* pLabel = dynamic_cast<Label*>(container->getChildByTag(tag));
	pLabel->setText(tempStr);
	return pLabel;
}

inline CCEditBox* YGODuelPrepareLayer::addNewEditBox(Widget* container, int tag,
		const char* key) {
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(
			tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	CCEditBox* pEditBox = CCEditBox::create(pInnerContainer->getContentSize(),
			CCScale9Sprite::create("1.png"));
	if (key[0] != '\0') {
		const char* tempStr =
				XMLParser::sharedXMLParser()->getString(key)->getCString();
		pEditBox->setPlaceHolder(tempStr);
		pEditBox->setPlaceholderFontColor(ccBLACK);
		pEditBox->setPlaceholderFontSize(28);
	}
	pEditBox->setFont("fonts/arial.ttf", 28);
	pEditBox->setReturnType(kKeyboardReturnTypeDone);
	pEditBox->setPosition(ccp(innerSize.width/2, innerSize.height/2));
	pEditBox->setTag(tag);
	pInnerContainer->addNode(pEditBox);
	return pEditBox;
}

inline DropDownList* YGODuelPrepareLayer::addNewDropDownList(Widget* container,
		int tag, vector<CCString*>* strings) {
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(
			tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	DropDownList* pDrowdownList = DropDownList::create(
			(*strings->begin())->getCString(), strings, innerSize, 30);
	pDrowdownList->addClickObserver(this,
			callfuncO_selector(YGODuelPrepareLayer::dropdownListCallback));
	pDrowdownList->setPosition(ccp(innerSize.width/2, innerSize.height/2));
	pDrowdownList->setTag(tag);
	pInnerContainer->addNode(pDrowdownList);
	return pDrowdownList;
}

inline CheckBox* YGODuelPrepareLayer::addNewCheckBox(Widget* container, int tag) {
	CheckBox* pCheckBox = dynamic_cast<CheckBox*>(container->getChildByTag(tag));
	pCheckBox->setEnabled(true);
	pCheckBox->setTouchEnabled(true);
	return pCheckBox;
}

inline Button* YGODuelPrepareLayer::addNewButton(Widget* container, int tag,
		const char* key) {
	Button* pButton = dynamic_cast<Button*>(container->getChildByTag(tag));
	if (key[0] != '\0') {
			std::string tempStr =
					XMLParser::sharedXMLParser()->getString(key)->getCString();
			pButton->setTitleText(tempStr);
		}
	pButton->setScale9Enabled(true);
	pButton->setTouchEnabled(true);
	pButton->setPressedActionEnabled(true);
	pButton->addTouchEventListener(this, toucheventselector(YGODuelPrepareLayer::buttonCallback));
	return pButton;
}

} /* namespace ygo */
