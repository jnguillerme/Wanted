#include "MainMenu.h"
#include "DuelMenu.h"
#include "GameCenter/GameCenter.h"

namespace wanted {

CCScene* MainMenu::scene()
{
    // 'scene' is an auto release object
    CCScene *scene = CCScene::create();

    // 'layer' is an auto release object
    MainMenu *layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void MainMenu::createMenuItems()
{
	addMenuItem("Aventure", menu_selector(MainMenu::onMenuAdventure), false);
	addMenuItem("Duels", menu_selector(MainMenu::onMenuDuels));
	addMenuItem("Classement", menu_selector(MainMenu::onMenuLeaderboard), GameCenter::sharedGC().isGameCenterEnable());
	addMenuItem("Carnet", menu_selector(MainMenu::onMenuBook), false);
	addMenuItem("Quitter", menu_selector(MainMenu::onMenuClose));
}

void MainMenu::onMenuAdventure(cocos2d::CCObject* pSender)
{

}
void MainMenu::onMenuDuels(cocos2d::CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(DuelMenu::scene());
}
void MainMenu::onMenuLeaderboard(cocos2d::CCObject* pSender)
{
	GameCenter::sharedGC().displayLeaderboard();
}
void MainMenu::onMenuBook(cocos2d::CCObject* pSender)
{

}
void MainMenu::onMenuClose(cocos2d::CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

}
