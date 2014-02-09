/*
 * YGOCardOpsPanel.h
 *
 *  Created on: 2014年2月7日
 *      Author: mabin
 */

#ifndef YGOCARDOPSPANEL_H_
#define YGOCARDOPSPANEL_H_

#include "CommonGui.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

namespace ygo {

class YGOCardOpsPanel: public CCScale9Sprite, public cocos2d::CCTargetedTouchDelegate {
public:
	YGOCardOpsPanel();
	virtual ~YGOCardOpsPanel();
	static YGOCardOpsPanel* createWithItems(const char* file,
			std::vector<CCString*>* strs, int textSize);
	bool setUpdateList(std::vector<CCString*>* strs);
	void addItem(const char* str, int i);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *touch, CCEvent *event);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *event);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *event);

	CCRect rect();
	bool containsTouchLocation(CCTouch *touch);

	void addItemSelectedListener(CCObject* target, SEL_CallFuncND callback);

protected:

	//点击了某一项后的回调方法，让点击的那一行背景该表
	void didSelectCallBack(CCObject* obj);
	void didSelectCallBack_1();

	CCRenderTexture* m_render;
	CCArray* m_pItemArray;
	int m_textSize;
	CCSize m_itemSize;
	CCObject* m_pItemSelectedTarget;
	SEL_CallFuncND m_pFnItemSelected;

};

} /* namespace ygo */
#endif /* YGOCARDOPSPANEL_H_ */
