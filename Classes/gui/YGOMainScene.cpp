/*
 * YGOMainScene.cpp
 *
 *  Created on: 2014年1月20日
 *      Author: mabin
 */

#include "YGOMainScene.h"
#include "ExitDialog.h"

USING_NS_CC;
using namespace gui;

namespace ygo {

YGOMainScene::YGOMainScene() {
	// TODO Auto-generated constructor stub
}

YGOMainScene::~YGOMainScene() {
	// TODO Auto-generated destructor stub
}

bool YGOMainScene::init() {
	if (!CCScene::init()) {
		return false;
	}
	// 'layer' is an autorelease object
	YGOBackgroundLayer* layer1 = YGOBackgroundLayer::create();

	// add backgrond layer
	this->addChild(layer1, 0);
	// add menu layer
	YGOMainMenuLayer* layer2 = YGOMainMenuLayer::create();
	layer2->setTag(MAIN_MENU_LAYER);
	this->addChild(layer2, 2);

	// return the scene
	return scene;
}

void YGOMainScene::menuLANModeCallback(CCObject* pSender) {
	YGOMainScene* scene =
			(YGOMainScene*) CCDirector::sharedDirector()->getRunningScene();
	scene->removeChildByTag(MAIN_MENU_LAYER);
	scene->addChild(YGOLANModeLayer::create(), 1);
}

void YGOMainScene::menuSingleModeCallback(CCObject* pSender) {
	YGOMainScene* scene =
			(YGOMainScene*) CCDirector::sharedDirector()->getRunningScene();
	scene->removeChildByTag(MAIN_MENU_LAYER);
	scene->addChild(YGOSingleModeLayer::create(), 1);
}

void YGOMainScene::menuReplayModeCallback(CCObject* pSender) {
	YGOMainScene* scene =
			(YGOMainScene*) CCDirector::sharedDirector()->getRunningScene();
	scene->removeChildByTag(MAIN_MENU_LAYER);
	scene->addChild(YGOReplayModeLayer::create(), 1);
}

void YGOMainScene::menuDeckEditModeCallback(CCObject* pSender) {
	YGOMainScene* scene =
			(YGOMainScene*) CCDirector::sharedDirector()->getRunningScene();
	scene->removeChildByTag(MAIN_MENU_LAYER);
	scene->addChild(YGODeckEditLayer::create(), 1);

}

void YGOMainScene::menuQuitCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
//	CCDirector::sharedDirector()->end();
	YGOMainScene* scene =
				(YGOMainScene*) CCDirector::sharedDirector()->getRunningScene();
	scene->addChild(ExitDlg::create());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

}  // namespace ygo

