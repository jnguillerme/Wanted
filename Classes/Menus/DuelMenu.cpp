#include "DuelMenu.h"
#include "Scenes/Duel.h"
#include "GameCenter/GameCenter.h"
#include "Menus/CharacterSelection.h"

namespace wanted {

CCScene* DuelMenu::scene()
{
    // 'scene' is an auto release object
    CCScene *scene = CCScene::create();
    // 'layer' is an auto release object
    DuelMenu *layer = DuelMenu::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool DuelMenu::init()
{
	if (!BaseMenu::init()) {
		return false;
	}

	return true;
}
void DuelMenu::createMenuItems()
{
	addMenuItem("GameCenter", menu_selector(DuelMenu::onMenuGameCenter), GameCenter::sharedGC().isGameCenterEnable());
	addMenuItem("Bluetooth", menu_selector(DuelMenu::onMenuBlueTooth), GameCenter::sharedGC().isBluetoothEnable());
	addMenuItem("Test", menu_selector(DuelMenu::onMenuTest));
}

void DuelMenu::onMenuGameCenter(cocos2d::CCObject* pSender)
{
	GameCenter::sharedGC().setCommunicationGooglePlayGameServices();
	CCDirector::sharedDirector()->replaceScene(CharacterSelection::scene());
}

void DuelMenu::onMenuBlueTooth(cocos2d::CCObject* pSender)
{
	CCLog("com.jino.wanted.DuelMenu - onMenuBlueTooth");
	GameCenter::sharedGC().setCommunicationBlueTooth();
	CCDirector::sharedDirector()->replaceScene(CharacterSelection::scene());
}
void DuelMenu::onMenuTest(cocos2d::CCObject* pSender)
{
	CCLog("com.jino.wanted.DuelMenu - onMenuTest");
	GameCenter::sharedGC().setCommunicationTest();
	CCDirector::sharedDirector()->replaceScene(CharacterSelection::scene());
}


} // namespace wanted
