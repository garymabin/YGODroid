/*
 * YGOCreateServerLayer.cpp
 *
 *  Created on: 2014年2月3日
 *      Author: mabin
 */

#include "YGOCreateServerLayer.h"

USING_NS_CC;
using namespace gui;
using namespace extension;

namespace ygo {

YGOCreateServerLayer::YGOCreateServerLayer() {
	// TODO Auto-generated constructor stub
	m_pLimitListData = new vector<CCString*>(1, CCString::create("(无)"));
	m_pCardAllowedData = new vector<CCString*>(1, CCString::create("(无)"));
	m_pDuelModeData = new vector<CCString*>(1, CCString::create("(无)"));
}

YGOCreateServerLayer::~YGOCreateServerLayer() {
	// TODO Auto-generated destructor stub
	m_pWidgetContainer->clear();
	m_pWidgetContainer->release();
	CC_SAFE_DELETE(m_pLimitListData);
}

bool YGOCreateServerLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(153, 153, 153, 77))) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pWidgetContainer = TouchGroup::create();
	m_pWidgetContainer->retain();
	Widget* panel = GUIReader::shareReader()->widgetFromJsonFile(
			"ygocore_lan_mode_create_host.json");
	CCSize mainPanelSize = panel->getContentSize();
	panel->setScaleX(visibleSize.width/mainPanelSize.width);
	panel->setScaleY(visibleSize.height/mainPanelSize.height);
	panel->setAnchorPoint(ccp(0.5, 0.5));
	panel->setPosition(ccp (visibleSize.width/2, visibleSize.height/2));
	m_pWidgetContainer->addWidget(panel);
	m_pWidgetContainer->setPosition(CCPointZero);
	this->addChild(m_pWidgetContainer);

	Widget* mainPanel = dynamic_cast<Widget*>(panel->getChildByTag(CREATE_SERVER_MAIN_WIDGET));
	//初始化UI
	//标签
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_LIMIT_LIST, "limit_list");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_CARD_ALLOWED, "card_allowed");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_DUEL_MODE, "duel_mode");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_LIMIT_EACH_ROUND, "time_limit_each_round");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_EXTRA_SETTINGS, "extra_settings");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_ALLOW_CARD_EFFECTS_PRIVILEGE, "allow_card_effects_privilege");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_INITIAL_LIFE_POINTS, "initial_life_points");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_IGNORE_DECK_CHECK, "ignore_deck_check");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_INITIAL_CARD_IN_HAND, "initial_card_in_hand");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_IGNORE_DECK_SHUFFLE, "ignore_deck_shuffle");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_DRAW_EACH_ROUND, "draw_each_round");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_HOST_NAME, "host_name");
	addNewLabel(mainPanel, CREATE_SERVER_LABEL_PASSWORD, "host_password");
	//下拉框
	m_pListLimit = addNewDropDownList(mainPanel, CREATE_SERVER_LIST_LIMIT_LIST, m_pLimitListData);
	m_pListCardAllowed = addNewDropDownList(mainPanel, CREATE_SERVER_LIST_CARD_ALLOWED, m_pCardAllowedData);
	m_pListDuelMode = addNewDropDownList(mainPanel, CREATE_SERVER_LIST_DUEL_MODE, m_pDuelModeData);
	//编辑框
	m_pEditBoxInitLp = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_INITIAL_LIFE_POINTS, "initial_life_points");
	m_pEditBoxInitCards = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_INITIAL_CARD_IN_HAND, "initial_card_in_hand");
	m_pEditBoxDrawCard = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_DRAW_EACH_ROUND, "draw_each_round");
	m_pEditBoxHostName = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_HOST_NAME, "host_name");
	m_pEditBoxPassword = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_PASSWORD, "host_password");
	m_pEditBoxTimeLimit = addNewEditBox(mainPanel, CREATE_SERVER_TEXT_FIELD_LIMIT_EACH_ROUND, "time_limit_each_round");
	//单选框
	m_pCheckBoxCEP = addNewCheckBox(mainPanel, CREATE_SERVER_CHECKBOX_ALLOW_CARD_EFFECTS_PRIVILEGE);
	m_pCheckBoxIgnoreCheck = addNewCheckBox(mainPanel, CREATE_SERVER_CHECKBOX_IGNORE_DECK_CHECK);
	m_pCheckBoxIgnoreShuffle = addNewCheckBox(mainPanel, CREATE_SERVER_CHECKBOX_IGNORE_DECK_SHUFFLE);
	//按钮
	m_pButtonCancel = addNewButton(mainPanel, CREATE_SERVER_BUTTON_CANCEL, "cancel");
	m_pButtonConfirm = addNewButton(mainPanel, CREATE_SERVER_BUTTON_CONFIRM, "confirm");

	return true;
}

inline Label* YGOCreateServerLayer::addNewLabel(Widget* container, int tag, const char* key) {
	std::string tempStr = XMLParser::sharedXMLParser()->getString(key)->getCString();
	Label* pLabel = dynamic_cast<Label*>(container->getChildByTag(tag));
	pLabel->setText(tempStr);
	return pLabel;
}

inline CCEditBox* YGOCreateServerLayer::addNewEditBox(Widget* container, int tag,
		const char* key) {
	const char* tempStr = XMLParser::sharedXMLParser()->getString(key)->getCString();
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	CCEditBox* pEditBox = CCEditBox::create(pInnerContainer->getContentSize(), CCScale9Sprite::create("1.png"));
	pEditBox->setFont("fonts/arial.ttf", 28);
	pEditBox->setPlaceHolder(tempStr);
	pEditBox->setPlaceholderFontColor(ccBLACK);
	pEditBox->setPlaceholderFontSize(28);
	pEditBox->setReturnType(kKeyboardReturnTypeDone);
	pEditBox->setPosition(ccp(innerSize.width/2, innerSize.height/2));
	pEditBox->setTag(tag);
	pInnerContainer->addNode(pEditBox);
	return pEditBox;
}

void YGOCreateServerLayer::dropdownListCallback(CCObject* pSender) {
	onEvent(dynamic_cast<DropDownList*>(pSender)->getTag());
}

inline DropDownList* YGOCreateServerLayer::addNewDropDownList(Widget* container, int tag, vector<CCString*> *strings) {
	Widget* pInnerContainer = dynamic_cast<Widget*>(container->getChildByTag(tag));
	CCSize innerSize = pInnerContainer->getContentSize();
	DropDownList* pDrowdownList = DropDownList::create((*strings->begin())->getCString(), strings,
			innerSize, 30);
	pDrowdownList->addClickObserver(this, callfuncO_selector(YGOCreateServerLayer::dropdownListCallback));
	pDrowdownList->setPosition( ccp(innerSize.width/2, innerSize.height/2));
	pDrowdownList->setTag(tag);
	pInnerContainer->addNode(pDrowdownList);
	return pDrowdownList;
}

inline CheckBox* YGOCreateServerLayer::addNewCheckBox(Widget* container, int tag) {
	CheckBox* pCheckBox = dynamic_cast<CheckBox*>(container->getChildByTag(tag));
	pCheckBox->setTouchEnabled(true);
	return pCheckBox;
}

void YGOCreateServerLayer::buttonCallback(CCObject* pSender,
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

void YGOCreateServerLayer::onEvent(int tag) {
	switch (tag) {
		case CREATE_SERVER_BUTTON_CANCEL: {
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
			m_pWidgetContainer->clear();
			scene->removeChild(this);
			scene->addChild(YGOLANModeLayer::create());
			break;
		}
		case CREATE_SERVER_BUTTON_CONFIRM: {
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
			NetServer::StartServer(7911);
			scene->removeChild(this);
			scene->addChild(YGODuelPrepareLayer::create());
			break;
		}
		default:
			break;
	}
}

inline Button* YGOCreateServerLayer::addNewButton(Widget* container, int tag,
		const char* key) {
	std::string tempStr = XMLParser::sharedXMLParser()->getString(key)->getCString();
	Button* pButton = dynamic_cast<Button*>(container->getChildByTag(tag));
	pButton->setTitleText(tempStr);
	pButton->setScale9Enabled(true);
	pButton->setTouchEnabled(true);
	pButton->setPressedActionEnabled(true);
	pButton->addTouchEventListener(this, toucheventselector(YGOCreateServerLayer::buttonCallback));
	return pButton;
}

} /* namespace ygo */
