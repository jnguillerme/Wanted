#include "BaseMenu.h"
#include "MenuItem.h"

namespace wanted {


// on "init" you need to initialize your instance
bool BaseMenu::init()
{
	CCLog("com.jino.wanted.BaseMenu::init");

	// init scene
	if ( !CCLayer::init() ){
		CCLog("com.jino.wanted.BaseMenu::init : CCLayer::init failed !");
        return false;
    }

	CCMenuItemFont::setFontSize(28);
	CCMenuItemFont::setFontName("PressStart2P.ttf");

	createBackground();
	createMenu();

	return true;
}
/**
 * createBackground
 */
void BaseMenu::createBackground()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    WantedLayer::addSpriteAndScale(this, CCSprite::create("UI/Back_Menu.png"), 0, size.height, -1);
}
/**
 * createMenu
 */
void BaseMenu::createMenu()
{
	createMenuItems();
	CCMenu* menu = CCMenu::createWithArray(&m_menuItems);
	menu->alignItemsVerticallyWithPadding(30);
	this->addChild(menu, 100);
}
/**
 * addMenuItem
 */
void BaseMenu::addMenuItem(const char * title, SEL_MenuHandler menuAction, bool fEnable)
{
	m_menuItems.addObject((CCObject*)MenuItem::item(title, this, menuAction, fEnable));
}

} // namespace wanted
