#include "ExitDialog.h"
#include "cocos2d.h"

USING_NS_CC;
namespace ygo {


bool ExitDlg::onInitDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "Arial", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);

    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(ExitDlg::okMenuItemCallback));
    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));

    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(ExitDlg::cancelMenuItemCallback));
    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));

    pushMenu(okMenuItem);
    pushMenu(cancelMenuItem);

    setColor(ccc3(0,125,0));
    setOpacity(128);
    return true;
}

void ExitDlg::okMenuItemCallback(CCObject *obj)
{
    CCDirector::sharedDirector()->end();
}

void ExitDlg::cancelMenuItemCallback(CCObject *obj)
{
    removeFromParentAndCleanup(true);
}

}
