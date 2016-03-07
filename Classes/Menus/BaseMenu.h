#ifndef __BASEMENU_H__
#define __BASEMENU_H__

#include "cocos2d.h"
#include "Utils/WantedLayer.h"

using namespace cocos2d;

namespace wanted {

class BaseMenu : public CCLayer {
	CCArray m_menuItems;

public:
	BaseMenu(CCString menuName) : CCLayer() {};
	virtual ~BaseMenu() {};			// RELEASE MENUITEMS
	virtual bool init();
//    static CCScene* scene();
private:
    void createBackground();
    void createMenu();

protected:
    virtual void createMenuItems() = 0;

    void addMenuItem(const char * title, SEL_MenuHandler menuAction, bool fEnable = true);

};

} //namespace wanted
#endif // __BASEMENU_H__
