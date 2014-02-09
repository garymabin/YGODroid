/*
 * DropDownList.h
 *
 *  Created on: 2014年1月29日
 *      Author: mabin
 */

#ifndef DROPDOWNLIST_H_
#define DROPDOWNLIST_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SelectedItemsSprite.h"

USING_NS_CC;
using namespace std;
using namespace extension;

namespace ygo {

class DropDownList: public cocos2d::CCSprite {
public:
	DropDownList();
	virtual ~DropDownList();
	static DropDownList* create(const char * defaultFn, const char * pressedFn,
			const char * title, vector<CCString*>* strs, CCSize size, int textSize);
	static DropDownList* create(const char * title, vector<CCString*>* strs,
			CCSize size, int textSize);
	void addClickObserver(CCObject* target, SEL_CallFuncO func);
	const char* getCurrentText() {
		CCAssert(m_pLabel,"m_pLabel can not be null");
		return m_pLabel->getString();
	}

	void setSelected(int idx) {
		return m_pLabel->setString(m_pDropDownListItem->getItemText(idx));
	}

	int getSelected() {
		return m_pDropDownListItem->indexOfText(m_pLabel->getString());
	}

	const char* getItemText(int idx) {
		return m_pDropDownListItem->getItemText(idx);
	}

	int getItemCount() {
		return m_pDropDownListItem->getItemCount();
	}

	void pushBackItem(const char* itemText) {
		m_pDropDownListItem->pushBackItem(itemText);
	}

private:
	virtual bool init(const char * defaultFn, const char * pressedFn,
			const char * title, vector<CCString*>* strs, CCSize size, int textSize);
	void dropDownListCallBack(CCObject* pObject, CCControlEvent event);

	//通知中心的回调方法
	void myNotificationFunc(CCObject* obj);
	CCLabelTTF* m_pLabel;
	SelectedItemsSprite* m_pDropDownListItem;
	CCObject* m_pTarget;
	SEL_CallFuncO m_pFnClicked;
};

} /* namespace ygo */
#endif /* DROPDOWNLIST_H_ */
