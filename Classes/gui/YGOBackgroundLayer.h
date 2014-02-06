#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "XMLParser.h"
#include "YGOImageManager.h"

namespace ygo {

class YGOBackgroundLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static node()" method manually
    CREATE_FUNC(YGOBackgroundLayer);
};


}  // namespace ygo

#endif // __HELLOWORLD_SCENE_H__
