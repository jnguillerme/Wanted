#include "GameCenter.h"
#include "cocos2d.h"
#include "GameCenterHelper.h"
#include "GameServerListener.h"
#include "GameClientListener.h"
#include "Menus/MainMenu.h"

/**
 * Public API
 */
namespace wanted {

bool GameCenter::Device::m_enableGameCenter = false;
bool GameCenter::Device::m_enableBluetooth = false;

GameCenter::GameCenter() : m_theGame(), m_gameCenterListener(0), m_notifications(), m_sceneInitialized(false), m_duelWon(0), m_duelLost(0)
{
}
GameCenter::~GameCenter()
{
}

bool GameCenter::applicationDidFinishLaunching()
{
	helper::gamecenter::callStaticVoidMethod("onApplicationDidFinishLaunching");
	return true;
}

void GameCenter::registerNotification(CCObject* target, SEL_CallFuncO sel, unsigned int notif)
{
	CCArray* a = (CCArray*) m_notifications.objectForKey(notif);

	if (a == NULL) {
		a = CCArray::createWithCapacity(1);
		m_notifications.setObject((CCObject*)a, notif);
	}
	a->addObject(CCCallFuncO::create(target, sel, NULL));
}

void GameCenter::unregisterAllNotifications()
{
	CCArray* keys =  m_notifications.allKeys();
	CCObject* key;

	CCARRAY_FOREACH(keys, key) {
		CCArray *listeners = (CCArray*)m_notifications.objectForKey((unsigned int)key);

		if (listeners) {
			CCObject* listener;
			CCCallFuncO* notification;

			CCARRAY_FOREACH(listeners, listener) {
				notification = (CCCallFuncO*)(listener);
				listeners->removeObject(notification, true);
			}
		}
	}
}
void GameCenter::unregisterNotification(CCObject* target, unsigned int notif)
{
/*	CCArray* listeners = (CCArray*) m_notifications.objectForKey(notif);

	if (listeners) {
		CCObject* listener;
		CCCallFuncO* notification;

		CCARRAY_FOREACH(listeners, listener) {
			notification = (CCCallFuncO*)(listener);
			if (notification->getTarget() == target) {
				listeners->removeObject(listener, true);
				break;
			}
		}
	}
	*/
}


/**
 * onMessageSent
 */
void GameCenter::onMessageSent(int msgType)
{
	postMessageToListener( GameCenterMessage::createWithMessageType(msgType));
}

/**
 * onRawMessageReceived
 * Message was received by the GameCenter
 * Decoded it and Forward it to the listeners
 */
void GameCenter::onMessageReceived(unsigned int* bytes, int size)
{
	GameCenterMessage *gcMsg = GameCenterMessage::createWithByteArray(bytes, size);

	if (gcMsg) {
		CCLog("com.jino.wanted.gamecenter - onMessageReceived [%d]", gcMsg->getMsgType());
		for (int i=1; i < size; i++) {
			CCLog("com.jino.wanted.gamecenter - %d >>> [%d][%d]", i, bytes[i], gcMsg->getBytes()[i-1]);
		}
		postMessageToListener(gcMsg);
	}

}

/**
 * onMessageReceived
 * Message was received by the GameCenter
 * Forward it to the listeners
 */
void GameCenter::postMessageToListener(GameCenterMessage *gcMsg)
{
	CCLog("com.jino.wanted.gamecenter - postMessageToListener %s", gcMsg->getMsgTypeName());
	//CCNotificationCenter::sharedNotificationCenter()->postNotification(gcMsg->getMsgTypeName(), gcMsg);
	CCArray *listeners = (CCArray*)m_notifications.objectForKey(gcMsg->getMsgType());

	if (listeners) {
		CCCallFuncO * notification;
		CCObject *listener;
		CCLog("com.jino.wanted.gamecenter - postMessageToListener : %d listeners found", listeners->capacity());

		CCARRAY_FOREACH(listeners, listener) {
			notification = (CCCallFuncO*)(listener);
			notification->setObject((CCObject*)gcMsg);
			notification->execute();
		}
	}
}
/**
 * startGame
 */
void GameCenter::startGame()
{
	m_theGame.setGameStatus(eStarted);
	postMessageToListener( GameCenterMessage::createWithMessageType(WANTED_START_GAME));
}

/**
 * startServer
 * start the server part
 */
void GameCenter::startServer()
{
	m_gameCenterListener = GameServerListener::create();
}
/**
 * startClient
 * start the client part
 *
 */
void GameCenter::startClient()
{
	m_gameCenterListener = GameClientListener::create();
}
/**
 * startDuel
 */
void GameCenter::startDuel()
{
	CCLog("com.jino.wanted.gamecenter - notifyOpponentOfDuelStart");
    helper::gamecenter::callStaticVoidMethod("notifyOpponentOfDuelStart");
}

/**
 * start
 */
void GameCenter::start()
{
    helper::gamecenter::callStaticVoidMethod("startGameServices");
}

void GameCenter::stop()
{
	CCLog("com.jino.wanted.gamecenter::stop");
    helper::gamecenter::callStaticVoidMethod("stopGameServices");

	if (m_gameCenterListener) {
    	m_gameCenterListener->release();
    	m_gameCenterListener = NULL;
    }


	CCLog("com.jino.wanted.gamecenter::stop - releasing notifications");
//	m_notifications.removeAllObjects();
	unregisterAllNotifications();

	m_theGame.setGameStatus(eNotStarted);
	m_sceneInitialized = false;
}

void GameCenter::onError(const char* errorMessage, bool fatal)
{
	CCMessageBox(errorMessage, "Wanted");

	if (fatal) {
		postMessageToListener(GameCenterMessage::createWithMessageType(WANTED_ERROR));
		stop();
	}
}

void GameCenter::setCommunicationGooglePlayGameServices()
{
    helper::gamecenter::callStaticVoidMethod("setGameCommunicationGooglePlayGameServices");
}
void GameCenter::setCommunicationBlueTooth()
{
    helper::gamecenter::callStaticVoidMethod("setGameCommunicationBlueTooth");
}
void GameCenter::setCommunicationTest()
{
    helper::gamecenter::callStaticVoidMethod("setGameCommunicationTest");
}
/**
 * notifyGameInitialized();
 * Notify that Game is initialisze
 */
void GameCenter::notifyGameInitialized()
{
	CCLog("com.jino.wanted.GameCenter::NotifyGameInitialized");

	postMessageToListener(GameCenterMessage::createWithMessageType(WANTED_GAME_INITIALIZED));
}

/**
 * NotifySceneInitialized
 * Notify that the scene is initialized
 */
void GameCenter::notifySceneInitialized()
{
	CCLog("com.jino.wanted.GameCenter::NotifySceneInitialized");

	m_sceneInitialized = true;
	postMessageToListener(GameCenterMessage::createWithMessageType(WANTED_SCENE_INITIALIZED));
}
/**
 * NotifyTargetPosition
 * Send the target position to client
 */
void GameCenter::notifyTargetPosition(CCPoint pos)
{
	CCLog("com.jino.wanted.GameCenter::NotifyTargetPosition [%d][%d]", (int)pos.x, (int)pos.y);

	postMessageToListener(GameCenterMessage::createWithMessageTypeAndParams(WANTED_NOTIFY_TARGET_POS, 2, (int)pos.x, (int)pos.y));
}
/**
 * NotifyTargetHit
 * Target was hit
 * 	Server side : 	store the info and check if client side was received
 * 					if so, check the result
 * 	Client side : send the info to the server
 */
void GameCenter::notifyTargetHit(int timeToHit)
{
	postMessageToListener(GameCenterMessage::createWithMessageTypeAndParams(WANTED_NOTIFY_TARGET_HIT, 2, timeToHit, me));
}
/**
 * notifyWinner
 *
 * Duel is over - notify who won
 */
void GameCenter::notifyWinner(ePlayer winner)
{
	postMessageToListener(GameCenterMessage::createWithMessageTypeAndParams(WANTED_NOTIFY_WINNER, 1, winner));
}

/**
 * duelWon
 * Duel was won - update data and save data on the cloud
 */
void GameCenter::duelWon()
{
	helper::gamecenter::callStaticVoidMethodWithInt("saveDuelWon", (int)(++m_duelWon) );
	helper::gamecenter::callStaticVoidMethodWithInt("updateLeaderBoardDuelWon", (int)(m_duelWon) );
	updateWinRatio();
}
/**
 * duelLost
 * Duel was lost- update data and save data on the cloud
 */
void GameCenter::duelLost()
{
	helper::gamecenter::callStaticVoidMethodWithInt("saveDuelLost", (int)(++m_duelLost) );
	updateWinRatio();
}

/**
 * updateWinRatio
 * Update Leaderboard with the ratio of duel won
 * Multiply by 1000 -> 100 to get the percentage
 * 					-> another 100 as the leaderboard is configured with 2 decimals
 */
void GameCenter::updateWinRatio()
{
	float winRatio = (m_duelWon / (m_duelWon + m_duelLost) ) * 10000;
	helper::gamecenter::callStaticVoidMethodWithInt("updateLeaderBoardDuelRatio", (int)(winRatio) );
}

/**
 * displayLeaderboard
 */
void GameCenter::displayLeaderboard()
{
	helper::gamecenter::callStaticVoidMethod("displayLeaderboard");
}

} // namespace wanted
