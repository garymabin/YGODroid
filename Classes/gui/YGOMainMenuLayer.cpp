/*
 * YGOMainMenuLayer.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#include "YGOMainMenuLayer.h"

USING_NS_CC;

namespace ygo {

YGOMainMenuLayer::YGOMainMenuLayer() {
	// TODO Auto-generated constructor stub

}

YGOMainMenuLayer::~YGOMainMenuLayer() {
	// TODO Auto-generated destructor stub
}

bool YGOMainMenuLayer::init() {
	if (!CCLayerColor::initWithColor(ccc4(153, 153, 153, 77))) {
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemFont::setFontName("Arial");
	CCMenuItemFont::setFontSize(36);
	CCMenuItem* pOnlineModeItem =
			CCMenuItemFont::create(
					::XMLParser::sharedXMLParser()->getString("online_mode")->getCString(),
					this, menu_selector(YGOMainScene::menuLANModeCallback));
	CCMenuItem* pSingleModeItem =
			CCMenuItemFont::create(
					::XMLParser::sharedXMLParser()->getString("single_mode")->getCString(),
					this, menu_selector(YGOMainScene::menuSingleModeCallback));
	CCMenuItem* pReplayModeItem =
			CCMenuItemFont::create(
					::XMLParser::sharedXMLParser()->getString("watch_replay")->getCString(),
					this, menu_selector(YGOMainScene::menuReplayModeCallback));
	CCMenuItem* pDeckEditModeItem =
			CCMenuItemFont::create(
					::XMLParser::sharedXMLParser()->getString("edit_deck")->getCString(),
					this,
					menu_selector(YGOMainScene::menuDeckEditModeCallback));
	CCMenuItem* pQuitItem =
			CCMenuItemFont::create(
					::XMLParser::sharedXMLParser()->getString("quit_game")->getCString(),
					this, menu_selector(YGOMainScene::menuQuitCallback));

	CCMenu* pMenu = CCMenu::create(pOnlineModeItem, pSingleModeItem,
			pReplayModeItem, pDeckEditModeItem, pQuitItem, NULL);
	pMenu->alignItemsVertically();
	pMenu->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pMenu);
	return true;
}

} /* namespace ygo */
