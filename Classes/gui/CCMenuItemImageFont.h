/*
 * CCMenuItemImageFont.h
 *
 *  Created on: 2014年1月21日
 *      Author: mabin
 */

#ifndef CCMENUITEMIMAGEFONT_H_
#define CCMENUITEMIMAGEFONT_H_

#include "cocos2d.h"

namespace cocos2d {

class CCMenuItemImageFont: public cocos2d::CCMenuItemSprite {
public:
	CCMenuItemImageFont();
	virtual ~CCMenuItemImageFont();

	static CCMenuItemImageFont* itemWithTarget(const char* text,
			const char* fontFile, const char * menubg, CCObject* target,
			SEL_MenuHandler selector);

	CREATE_FUNC(CCMenuItemImageFont)
};

} /* namespace cocos2d */
#endif /* CCMENUITEMIMAGEFONT_H_ */
