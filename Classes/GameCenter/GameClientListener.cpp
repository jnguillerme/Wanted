#include "GameClientListener.h"
#include "GameCenter.h"
#include "GameCenterHelper.h"

namespace wanted {

bool GameClientListener::init()
{
	if (!GameClientServerListener::init()) {
		return false;
	}

	m_isTargetPositionSet = false;
	return true;
}

void GameClientListener::registerNotifications()
{
	CCLog("com.jino.wanted.GameClientListener::registerNotifications");

	GC_REGISTER_NOTIFICATION(this, GameClientListener::processWantedNotifyCharacter, WANTED_NOTIFY_CHARACTER);
	GC_REGISTER_NOTIFICATION(this, GameClientListener::processWantedStartGame, WANTED_START_GAME);
	GC_REGISTER_NOTIFICATION(this, GameClientListener::processWantedTargetPos, WANTED_NOTIFY_TARGET_POS);
	GC_REGISTER_NOTIFICATION(this, GameClientListener::processWantedSceneInitialized, WANTED_SCENE_INITIALIZED);
	GC_REGISTER_NOTIFICATION(this, GameClientListener::processWantedNotifyTargetHit, WANTED_NOTIFY_TARGET_HIT);
}

void GameClientListener::onStartGame(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted.GameClientListener::processWantedStartGame");

	// unregister messages we won't need anymore
	GC_UNREGISTER_NOTIFICATION(this, WANTED_SCENE_INITIALIZED);
	GC_UNREGISTER_NOTIFICATION(this, WANTED_START_GAME);

	if ( m_isTargetPositionSet ) {
		CCLog("com.jino.wanted.GameClientListener::processWantedStartGame - StartDuel");
		GameCenter::sharedGC().startDuel();
	}

}

void GameClientListener::processWantedTargetPos(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted.GameClientListener::processWantedTargetPos");
	// target is set and game is started - the duel can start
	m_isTargetPositionSet = true;

	if ( GameCenter::sharedGC().isGameStarted() ) {
		CCLog("com.jino.wanted.GameClientListener::processWantedTargetPos - StartDuel");
		GameCenter::sharedGC().startDuel();
	}
}

/**
 * processWantedNotifyTargetHit
 *
 * Notify the server that target was hit
 */
void GameClientListener::processWantedNotifyTargetHit(GameCenterMessage *gcMsg)
{
	CCLog("com.jino.wanted.GameClientListener::processWantedNotifyTargetHit");
	helper::gamecenter::callStaticVoidMethodWithInt("notifyOpponentOfTimeToHit", gcMsg->getBytes()[0]);
}
}
