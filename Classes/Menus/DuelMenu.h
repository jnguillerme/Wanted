#ifndef _DUEL_MENU_H_
#define _DUEL_MENU_H_

#include "BaseMenu.h"
#include "GameCenter/GameCenterMessage.h"

namespace wanted {

class DuelMenu : public BaseMenu {
public:
	DuelMenu():BaseMenu("DuelMenu") {};
	~DuelMenu() {};

	static CCScene* scene();
	bool init();
    CREATE_FUNC(DuelMenu);

    void startDuel() const;

protected:
    virtual void createMenuItems();

	virtual void onMenuGameCenter(cocos2d::CCObject* pSender);
	virtual void onMenuBlueTooth(cocos2d::CCObject* pSender);
	virtual void onMenuTest(cocos2d::CCObject* pSender);

};

} // namespace wanted
#endif //_DUEL_MENU_H_
