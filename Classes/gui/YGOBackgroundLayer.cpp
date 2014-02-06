#include "YGOBackgroundLayer.h"

USING_NS_CC;
using namespace extension;
using namespace gui;

namespace ygo {

// on "init" you need to initialize your instance
bool YGOBackgroundLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCTexture2D* pTexture = YGOImageManager::sharedImageManager()->getBackgroundTexture();
    CCSprite* pSprite = CCSprite::createWithTexture(pTexture);
    CCSize size = pSprite->getContentSize();
    pSprite->setScaleX(visibleSize.width/size.width);
    pSprite->setScaleY(visibleSize.height/size.height);

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

}  // namespace ygo


