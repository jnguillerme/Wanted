#include "CharacterSelection.h"
#include "GameCenter/GameCenter.h"
#include "Scenes/Duel.h"

namespace wanted {

cocos2d::CCScene* CharacterSelection::scene()
{
    CCScene *scene = CCScene::create();
    CharacterSelection *layer = CharacterSelection::create();
    scene->addChild(layer);

    return scene;
}

bool CharacterSelection::init()
{
	if ( !CCLayer::init() ) {
		return false;
	}

	GC_REGISTER_NOTIFICATION(this, CharacterSelection::processWantedGameInitialized, WANTED_GAME_INITIALIZED);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    WantedLayer::addSpriteAndScale(this, CCSprite::create("UI/Back_Menu.png"), 0, size.height, -1);

    CCMenuItemImage* item1 = CCMenuItemImage::create("Character/Kid.png", "Character/Kid_selected.png", this,
    												menu_selector(CharacterSelection::onKidSelected));
    item1->setScale(0.8);

    CCMenuItemImage* item2 = CCMenuItemImage::create("Character/OutLaw.png", "Character/OutLaw_selected.png", this,
													menu_selector(CharacterSelection::onOutlawSelected));
    item2->setScale(0.8);

    CCMenuItemImage* item3 =  CCMenuItemImage::create("Character/Samaritan.png", "Character/Samaritan_selected.png", this,
			menu_selector(CharacterSelection::onSamaritanSelected));

    item3->setScale(0.8);

    CCMenu* menu = CCMenu::create(item1, item2, item3, NULL);

	menu->alignItemsHorizontallyWithPadding(30);
	this->addChild(menu, 100);

	return true;
}

void CharacterSelection::onKidSelected(cocos2d::CCObject* pSender)
{
	onCharacterSelected(WANTED_CHARACTER_KID);
//	CCDirector::sharedDirector()->replaceScene(Duel::scene());
}
void CharacterSelection::onOutlawSelected(cocos2d::CCObject* pSender)
{
	onCharacterSelected(WANTED_CHARACTER_OUTLAW);
}
void CharacterSelection::onSamaritanSelected(cocos2d::CCObject* pSender)
{
	onCharacterSelected(WANTED_CHARACTER_SAMARITAN);
}

void CharacterSelection::onCharacterSelected(const unsigned int character)
{
	GameCenter::sharedGC().setMyCharacter(character);
	GameCenter::sharedGC().start();
}

void CharacterSelection::processWantedGameInitialized(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted.CharacterSelection - processWantedGameInitialized");
	CCDirector::sharedDirector()->replaceScene(Duel::scene());
}

}		// namespace wanted
