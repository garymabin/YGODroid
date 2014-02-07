/*
 * CCMenuItemImageFont.cpp
 *
 *  Created on: 2014年1月21日
 *      Author: mabin
 */

#include "CCMenuItemImageFont.h"

namespace cocos2d {

CCMenuItemImageFont::CCMenuItemImageFont() {
	// TODO Auto-generated constructor stub

}

CCMenuItemImageFont::~CCMenuItemImageFont() {
	// TODO Auto-generated destructor stub
}

/** 通过BMFont和CCSprite创建菜单项
 // text : 显示文本内容
 // fontFile ： BMFont 字库文件路径
 // menubg ： 菜单背景图片（暂未做背景拉伸，大家自由发挥）
 // target，selector 回调函数
 */
CCMenuItemImageFont* CCMenuItemImageFont::itemWithTarget(const char* text,
		const char* fontFile, const char * menubg, CCObject* target,
		SEL_MenuHandler selector) {
	CCSprite *sprite = CCSprite::create(menubg);
	CCLabelTTF* label = CCLabelTTF::create(text, fontFile, 30);

	CCSize size = sprite->getContentSize();

	//初始化一块texture区域， 大小为背景图片尺寸， 这里可以考虑缩放适应字的宽度。
	CCRenderTexture *texture = CCRenderTexture::create(size.width, size.height,
			kCCTexture2DPixelFormat_RGBA8888);

	//这里不清楚的可以详细看下CCRenderTexture.h里面的定义
	texture->begin();
	sprite->setPosition(ccp(size.width/2, size.height/2));
	sprite->visit();
	label->setPosition(ccp(size.width/2, size.height/2));
	label->visit();

	texture->end();

	//这里可能有点争议， CCRenderTexture本身会addchild()当前sprite， 所以要先移除掉， 然后再add菜单。
	texture->removeChild(texture->getSprite(), false);
	CCMenuItemImageFont *imageFont =
			(CCMenuItemImageFont *) CCMenuItemSprite::create(
					texture->getSprite(), texture->getSprite(), NULL, target,
					selector);

	return imageFont;
}

} /* namespace cocos2d */
