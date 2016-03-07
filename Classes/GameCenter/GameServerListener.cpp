#include "GameServerListener.h"
#include "GameCenter.h"
#include "GameCenterHelper.h"

namespace wanted {

bool GameServerListener::init()
{
	if (!GameClientServerListener::init()) {
		return false;
	}
	return true;
}

const CCPoint GameServerListener::calculateTargetPosition() const
{
	/// set the random position for the target
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint actualPoint;

	int minY = 0;
	int maxY = size.height;
	int rangeY = maxY- minY;
	actualPoint.y = (float)(( rand() % rangeY) + minY);
	actualPoint.y = (actualPoint.y / size.height) * 100;	// send the ratio to accommodate different screen sizes

	int minX = 0;
	int maxX = size.width;
	int rangeX = maxX- minX;
	actualPoint.x = (float)(( rand() % rangeX) + minX);
	actualPoint.x = (actualPoint.x / size.width) * 100;	// send the ratio to accommodate different screen sizes


	return actualPoint;
}

/**
 * getWinner
 *
 * return the player that won the duel
 */

ePlayer GameServerListener::getWinner() const
{
	CCLog("com.jino.wanted.GameServerListener::getWinner");

	ePlayer winner = undefined;

	if ( GameCenter::sharedGC().getMyTimeToHit() == 0 || GameCenter::sharedGC().getOpponentTimeToHit() == 0 ) {
		winner = undefined;
	} else {
		winner = ( GameCenter::sharedGC().getMyTimeToHit() < GameCenter::sharedGC().getOpponentTimeToHit() ) ? me : opponent;
	}
	return winner;

}

void GameServerListener::registerNotifications()
{
	CCLog("com.jino.wanted.GameServerListener::registerNotifications");
	GC_REGISTER_NOTIFICATION(this, GameServerListener::processWantedNotifyCharacter, WANTED_NOTIFY_CHARACTER);
	GC_REGISTER_NOTIFICATION(this, GameServerListener::processWantedStartGame, WANTED_START_GAME);
	GC_REGISTER_NOTIFICATION(this, GameServerListener::processWantedNotifyTargetHit, WANTED_NOTIFY_TARGET_HIT);
	GC_REGISTER_NOTIFICATION(this, GameServerListener::processWantedSceneInitialized, WANTED_SCENE_INITIALIZED);
	GC_REGISTER_NOTIFICATION(this, GameServerListener::processWantedOpponentIsComputer, WANTED_OPPONENT_IS_COMPUTER);
}

/**
 * processWantedStartGame
 * Game is starting - calculate target position and notify the duel scene and the opponent
 *
 */
void GameServerListener::onStartGame(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted.GameServerListener::processWantedStartGame");

	// unregister messages we won't need anymore
	GC_UNREGISTER_NOTIFICATION(this, WANTED_SCENE_INITIALIZED);
	GC_UNREGISTER_NOTIFICATION(this, WANTED_START_GAME);

	// calculate target pos and notify game center and opponent
	CCPoint targetPosition = calculateTargetPosition();
	CCLog("com.jino.wanted.GameServerListener::processWantedStartGame - Target position calculated [%d][%d]", (int)targetPosition.x, (int)targetPosition.y);
	GameCenter::sharedGC().notifyTargetPosition(targetPosition);
	helper::gamecenter::callStaticVoidMethodWithIntAndInt("notifyOpponentOfTargetPos", (int)targetPosition.x, (int)targetPosition.y);
}
/**
 * processWantedNotifyTargetHit
 */
void GameServerListener::processWantedNotifyTargetHit(GameCenterMessage *gcMsg)
{
	CCLog("com.jino.wanted.GameServerListener::processWantedNotifyTargetHit");

	if (gcMsg && gcMsg->getBytesLen() == 2) {		// macro IS_EXPECTED_MESSAGE ?
		CCLog("com.jino.wanted.GameServerListener::processWantedNotifyTargetHit [%d]", (int)gcMsg->getBytes()[1]);
		if (gcMsg->getBytes()[1] == me) {
			GameCenter::sharedGC().setMyTimeToHit(gcMsg->getBytes()[0]);
		} else if (gcMsg->getBytes()[1] == opponent) {
			GameCenter::sharedGC().setOpponentTimeToHit(gcMsg->getBytes()[0]);
		} else {
			// ERROR
		}

		// CHECKRESULT
		ePlayer winner = getWinner();
		if (winner != undefined) {
			helper::gamecenter::callStaticVoidMethodWithInt("notifyOpponentOfWinner", (int)winner );
			GameCenter::sharedGC().notifyWinner(winner );
		}
	}

}

/**
 * processWantedOpponentIsComputer
 * Opponent is computer - give it a random time
 */
void GameServerListener::processWantedOpponentIsComputer(GameCenterMessage *gcMsg)
{
	CCLog("com.jino.wanted.GameServerListener::processWantedOpponentIsComputer");
	GameCenter::sharedGC().setOpponentTimeToHit(1000);
}
} // namespace wanted
