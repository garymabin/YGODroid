/*
 * YGOLANModeLayer.cpp
 *
 *  Created on: 2014年1月22日
 *      Author: mabin
 */

#include "YGOLANModeLayer.h"

USING_NS_CC;
using namespace gui;
using namespace extension;

namespace ygo {

YGOLANModeLayer::YGOLANModeLayer() :
		m_pWidgetContainer(NULL) {
	// TODO Auto-generated constructor stub

}

YGOLANModeLayer::~YGOLANModeLayer() {
	// TODO Auto-generated destructor stub
	m_pWidgetContainer->clear();
	m_pWidgetContainer->release();
}

bool YGOLANModeLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(153, 153, 153, 77))) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	m_pWidgetContainer = TouchGroup::create();
	m_pWidgetContainer->retain();
	Widget* panel = GUIReader::shareReader()->widgetFromJsonFile(
			"ygocore_lan_mode.json");
	m_pWidgetContainer->addWidget(panel);
	//初始化UI控件
	std::string tempText = ::XMLParser::sharedXMLParser()->getString(
			"nick_name")->getCString();
	Widget* pContainerNickName = dynamic_cast<Widget*>(panel->getChildByTag(
			LAN_MODE_TEXT_FIELD_NICK_NAME));
	CCSize tempSize = pContainerNickName->getContentSize();
	CCEditBox* pNickNameEdit = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	pNickNameEdit->setFont("fonts/arial.ttf", 28);
	pNickNameEdit->setPlaceHolder(tempText.c_str());
	pNickNameEdit->setPlaceholderFontColor(ccBLACK);
	pNickNameEdit->setPlaceholderFontSize(28);
	pNickNameEdit->setMaxLength(8);
	pNickNameEdit->setReturnType(kKeyboardReturnTypeDone);
	pNickNameEdit->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	pContainerNickName->addNode(pNickNameEdit);

	Widget* pContainerAddress = dynamic_cast<Widget*>(panel->getChildByTag(
			LAN_MODE_TEXT_FIELD_ADDRESS));
	tempSize = pContainerAddress->getContentSize();
	tempText =
			::XMLParser::sharedXMLParser()->getString("host_address")->getCString();
	CCEditBox* pHostEdit = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	pHostEdit->setFont("fonts/arial.ttf", 28);
	pHostEdit->setPlaceHolder(tempText.c_str());
	pHostEdit->setPlaceholderFontColor(ccBLACK);
	pHostEdit->setPlaceholderFontSize(28);
	pHostEdit->setMaxLength(8);
	pHostEdit->setReturnType(kKeyboardReturnTypeDone);
	pHostEdit->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	pContainerAddress->addNode(pHostEdit);

	Widget* pContainerPasswd = dynamic_cast<Widget*>(panel->getChildByTag(
			LAN_MODE_TEXT_FIELD_PASSWORD));
	tempText =
			::XMLParser::sharedXMLParser()->getString("host_password")->getCString();
	tempSize = pContainerPasswd->getContentSize();
	CCEditBox* pPasswdEdit = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	pPasswdEdit->setFont("fonts/arial.ttf", 28);
	pPasswdEdit->setPlaceHolder(tempText.c_str());
	pPasswdEdit->setPlaceholderFontColor(ccBLACK);
	pPasswdEdit->setPlaceholderFontSize(28);
	pPasswdEdit->setMaxLength(8);
	pPasswdEdit->setReturnType(kKeyboardReturnTypeDone);
	pPasswdEdit->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	pContainerPasswd->addNode(pPasswdEdit);

	Widget* pContainerPort = dynamic_cast<Widget*>(panel->getChildByTag(LAN_MODE_TEXT_FIELD_PORT));
	tempText = ::XMLParser::sharedXMLParser()->getString("port_name")->getCString();
	tempSize = pContainerPort->getContentSize();
	CCEditBox* pPortEdit = CCEditBox::create(tempSize,
			CCScale9Sprite::create("1.png"));
	pPortEdit->setFont("fonts/arial.ttf", 28);
	pPortEdit->setPlaceHolder(tempText.c_str());
	pPortEdit->setPlaceholderFontColor(ccBLACK);
	pPortEdit->setPlaceholderFontSize(28);
	pPortEdit->setMaxLength(8);
	pPortEdit->setReturnType(kKeyboardReturnTypeDone);
	pPortEdit->setPosition(ccp(tempSize.width/2, tempSize.height/2));
	pContainerPort->addNode(pPortEdit);

	Button* pButtonRefresh = reinterpret_cast<Button *>(panel->getChildByTag(
			LAN_MODE_BUTTON_REFRESH));
	tempText =
			::XMLParser::sharedXMLParser()->getString("refresh")->getCString();
	pButtonRefresh->setTitleText(tempText);
	pButtonRefresh->setScale9Enabled(true);

	Button* pButtonJoinGame = reinterpret_cast<Button *>(panel->getChildByTag(
			LAN_MODE_BUTTON_JOIN_GAME));
	tempText =
			::XMLParser::sharedXMLParser()->getString("join_game")->getCString();
	pButtonJoinGame->setTitleText(tempText);
	pButtonJoinGame->setScale9Enabled(true);

	Button* pButtonCreateHost = reinterpret_cast<Button *>(panel->getChildByTag(
			LAN_MODE_BUTTON_CREATE_HOST));
	tempText =
			::XMLParser::sharedXMLParser()->getString("create_host")->getCString();
	pButtonCreateHost->setTitleText(tempText);
	pButtonCreateHost->setScale9Enabled(true);
	pButtonCreateHost->addTouchEventListener(this,
				toucheventselector(YGOLANModeLayer::buttonLanModeCallback));

	Button* pButtonCancel = reinterpret_cast<Button *>(panel->getChildByTag(
			LAN_MODE_BUTTON_CANCEL));
	tempText =
			::XMLParser::sharedXMLParser()->getString("cancel")->getCString();
	pButtonCancel->setTitleText(tempText);
	pButtonCancel->setScale9Enabled(true);
	pButtonCancel->setTouchEnabled(true);
	pButtonCancel->addTouchEventListener(this,
			toucheventselector(YGOLANModeLayer::buttonLanModeCallback));

//	CCPoint p = ul->getPosition();
//	CCPoint ap = ul->getAnchorPoint();
//	CCLog("p.x = %f, p.y = %f", p.x, p.y);
//	CCLog("ap.x = %f, ap.y = %f", ap.x, ap.y);
	CCSize panelSize = panel->getContentSize();
//	CCLog("visibleSize.width  = %f, visibleSize.height  = %f",visibleSize.width, visibleSize.height);
//	CCLog("size.width = %f, size.height = %f", size.width, size.height);
	panel->setScaleX(visibleSize.width/panelSize.width);
	panel->setScaleY(visibleSize.height/panelSize.height);
	m_pWidgetContainer->setPosition(CCPointZero);
	this->addChild(m_pWidgetContainer);
	return true;
}

void YGOLANModeLayer::buttonLanModeCallback(CCObject* pSender,
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

void YGOLANModeLayer::onEvent(int tag) {
	switch (tag) {
		case LAN_MODE_BUTTON_CANCEL: {
			m_pWidgetContainer->clear();
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
			scene->removeChild(this);
			YGOMainMenuLayer* layer = YGOMainMenuLayer::create();
			layer->setTag(MAIN_MENU_LAYER);
			scene->addChild(layer);
			break;
		}
		case LAN_MODE_BUTTON_CREATE_HOST: {
			CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
			scene->removeChild(this);
			scene->addChild(YGOCreateServerLayer::create());
			break;
		}
		default:
			break;
	}
}

} /* namespace ygo */
