/*
 * SelectedBoxSprite.h
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#ifndef SELECTEDBOXSPRITE_H_
#define SELECTEDBOXSPRITE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include <iostream>
USING_NS_CC;

#define MyNotification "DidSelectIndex"

namespace ygo {

class SelectedItemsSprite: public cocos2d::extension::CCScale9Sprite,
		public cocos2d::CCTargetedTouchDelegate {
public:
	SelectedItemsSprite();
	virtual ~SelectedItemsSprite();

    static SelectedItemsSprite* create(const char* name, CCSize size, std::vector<CCString*>* strs, int textSize);
    bool setUpdateList(std::vector<CCString*>* strs);

    virtual void onEnter();
    virtual void onExit();

    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
    virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

    CCRect rect();
    bool containsTouchLocation(CCTouch *touch);

    int getItemCount() {
    	return m_pItemArray->count();
    }

    const char* getItemText(int idx) {
    	CCLabelTTF* ttf = dynamic_cast<CCLabelTTF*>(m_pItemArray->objectAtIndex(idx));
    	return ttf->getString();
    }

    int indexOfText(const char* str);
    void pushBackItem(const char* str);
	void addItem(const char* str, int i);

private:
    CCArray* m_pItemArray;
    CCSize m_itemSize;
    int m_textSize;

    //点击了列表框后的回调方法，让点击的那一行闪烁
    void didSelectCallBack(CCObject* obj);
    void didSelectCallBack_1();

};

} /* namespace ygo */
#endif /* SELECTEDBOXSPRITE_H_ */
