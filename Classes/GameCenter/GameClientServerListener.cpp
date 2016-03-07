#include "GameCenter.h"
#include "GameClientServerListener.h"
#include "GameCenterHelper.h"

namespace wanted {

/**
 * constructor
 */
GameClientServerListener::GameClientServerListener() : CCObject()
{
}
/**
 * destructor
 */
GameClientServerListener::~GameClientServerListener()
{
}
/**
 * init
 */
bool GameClientServerListener::init()
{
	registerNotifications();
	return true;
}
/**
 * processWantedNotifyCharacter
 *
 * WANTED_NOTIFY_CHARACTER received
 * Will set the character for the opponent
 */
void GameClientServerListener::processWantedNotifyCharacter(GameCenterMessage* gcMsg)
{
	GameCenter::sharedGC().setOpponentCharacter(gcMsg->getBytes()[0]);
	GameCenter::sharedGC().notifyGameInitialized();
}

/**
 * processWantedStartGame
 *
 * WANTED_START_GAME message received
 * Will start the game if the scene is initialized
 */
void GameClientServerListener::processWantedStartGame(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted.gameClientServerListener::processWantedStartGame - [readyToStart:%s][initialised:%s]",
			GameCenter::sharedGC().isGameStarted() ? "true" : "false", GameCenter::sharedGC().getSceneInitialized() ? "true" : "false");

/*	if (GameCenter::sharedGC().getSceneInitialized()) {
		onStartGame(gcMsg);
	}*/

	helper::gamecenter::callStaticVoidMethodWithInt("notifyOpponentOfCharacter", GameCenter::sharedGC().getMyCharacter());

}
/**
 * processWantedSceneInitialized
 *
 * WANTED_SCENE_INITIALIZED received
 * Will start the game if WANTED_START_MESSAGE was already received
 */
void GameClientServerListener::processWantedSceneInitialized(GameCenterMessage* gcMsg) {
	CCLog("com.jino.wanted.gameClientServerListener::processWantedSceneInitialized - [readyToStart:%s][initialised:%s]",
			GameCenter::sharedGC().isGameStarted() ? "true" : "false", GameCenter::sharedGC().getSceneInitialized() ? "true" : "false");

	if (GameCenter::sharedGC().isGameStarted()) {
		onStartGame(gcMsg);
	}
}


}		// namespace wanted
