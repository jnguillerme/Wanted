#ifndef _WANTED_MENU_ITEM_H_
#define _WANTED_MENU_ITEM_H_

#include "cocos2d.h"

using namespace cocos2d;

namespace wanted {

class MenuItem : public CCNode {

public:
	static CCMenuItemImage* item(const char * title, CCObject* target, SEL_MenuHandler selector, const bool fEnable = true);
	static MenuItem* createWithTitle(const char * title, const bool fEnable = true) {
	    MenuItem *pRet = new MenuItem();
	    if (pRet && pRet->initWithTitle(title, fEnable)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }
	}

private:
	bool initWithTitle(const char* title, const bool fEnable = true);
};

} // namespace wanted

#endif // _WANTED_MENU_ITEM_
