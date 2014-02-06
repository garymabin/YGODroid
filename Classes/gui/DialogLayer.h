// 原理：
// 模态对话框 能够拦截所有下层的消息
// cocos2d-x 消息处理优先级【-128,128】越小优先级越高
// 菜单kCCMenuHandlerPriority优先级 -128 要想拦截所有消息(包括菜单) 
// 必须将我们的模态对话框优先级<-128 但是也意味着拦截了当前模态对话框的菜单消息(-128)
// 我们需要手动将消息传给模态对话框上的按钮进行处理
// 使用：1.重载OnInitDialog将需要的控件添加到dlg上
//       2.需要响应事件的按钮使用pushMenu添加
//       3.派生类需要实现宏CREATE_FUNC(class_name)

#ifndef _DIALOGLAYER_H_
#define _DIALOGLAYER_H_

#include "cocos2d.h"

class DialogLayer: public cocos2d::CCLayerColor {
public:
	DialogLayer();
	virtual ~DialogLayer();

public:
	/** 初始化对话框 */
	virtual bool onInitDialog() = 0;

	/** 所有的菜单按钮压入到容器中 */
	void pushMenu(cocos2d::CCMenuItem *pMenu);

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch,
			cocos2d::CCEvent *pEvent);

private:
	/** 初始化菜单 将菜单添加到模态对话框上*/
	bool initMenu();

private:
	cocos2d::CCMenu *mMenu;             // 模态对话框菜单
	cocos2d::CCArray *mMenuItemArray;   // 所有菜单
	bool mTouchedMenu;                  // 记录菜单点击
};

#endif
