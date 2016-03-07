#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "BaseMenu.h"

namespace wanted {

class MainMenu : public BaseMenu {

public:
	MainMenu():BaseMenu("MainMenu") {};
	~MainMenu() {};

	static CCScene* scene();
	//virtual bool init();
    CREATE_FUNC(MainMenu);

protected:
    virtual void createMenuItems();

	virtual void onMenuAdventure(cocos2d::CCObject* pSender);
	virtual void onMenuDuels(cocos2d::CCObject* pSender);
	virtual void onMenuLeaderboard(cocos2d::CCObject* pSender);
	virtual void onMenuBook(cocos2d::CCObject* pSender);
	virtual void onMenuClose(cocos2d::CCObject* pSender);

};

} // namespace wanted
#endif //_MAIN_MENU_H_
