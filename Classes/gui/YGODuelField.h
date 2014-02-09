/*
 * YGODuelField.h
 *
 *  Created on: 2014年2月8日
 *      Author: mabin
 */

#ifndef YGODUELFIELD_H_
#define YGODUELFIELD_H_

#include "CommonGui.h"

class YGODuelField: public cocos2d::gui::Layout {
public:
	YGODuelField();
	virtual ~YGODuelField();
	virtual bool init();
	CREATE_FUNC(YGODuelField)

	// default implements are used to call script callback if exist
	virtual bool onTouchBegan(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void onTouchMoved(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void onTouchEnded(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void onTouchCancelled(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();
protected:
	cocos2d::gui::Widget* m_pContent;
	CC_SYNTHESIZE_READONLY(cocos2d::gui::Widget*, m_pExtra1, Extra1);

};

#endif /* YGODUELFIELD_H_ */
