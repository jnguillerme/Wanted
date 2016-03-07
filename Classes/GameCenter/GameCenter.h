#ifndef __GAMECENTER_H__
#define __GAMECENTER_H__

#include "cocos2d.h"
#include "GameCenter/GameCenterMessage.h"
#include "GameCenter/GameClientServerListener.h"
#include "GameCenter/Game.h"

using namespace cocos2d;

namespace wanted {


#define GC_REGISTER_NOTIFICATION(target, callback, notification) \
GameCenter::sharedGC().registerNotification(target, callfuncO_selector(callback), notification);

#define GC_UNREGISTER_NOTIFICATION(target, notification) \
GameCenter::sharedGC().unregisterNotification(target, notification);

class GameCenter
{
	Game m_theGame;
	GameClientServerListener *m_gameCenterListener;
	CCDictionary m_notifications;
	CC_SYNTHESIZE_READONLY(bool, m_sceneInitialized, SceneInitialized );
	CC_SYNTHESIZE(unsigned int, m_duelWon, DuelWon);
	CC_SYNTHESIZE(unsigned int, m_duelLost, DuelLost);

	struct Device {
		static bool m_enableGameCenter;
		static bool m_enableBluetooth;
	} m_device;
public:
	GameCenter();
	virtual ~GameCenter();

    static GameCenter& sharedGC(void) {
    	static GameCenter theGameCenter;
    	return theGameCenter;
    };

    bool applicationDidFinishLaunching();

    void enableGameCenter(bool enable)	{ 	Device::m_enableGameCenter = enable;}
    bool isGameCenterEnable() 	const	{ 	return Device::m_enableGameCenter; 	}
    void enableBluetooth(bool enable)	{ 	Device::m_enableBluetooth = enable; }
    bool isBluetoothEnable()	const	{ 	return Device::m_enableBluetooth;	}

    void registerNotification(CCObject* target, SEL_CallFuncO sel, unsigned int notif);
    void unregisterAllNotifications();
    void unregisterNotification(CCObject* target, unsigned int notif);
    void onMessageSent(int msgType);
    void postMessageToListener(GameCenterMessage *gcMsg);
    void onMessageReceived(unsigned int* bytes, int size);

    void setMyCharacter(const unsigned int theCharacter) { m_theGame.setMyCharacter(theCharacter); }
    unsigned int getMyCharacter() const { return m_theGame.getMyCharacter(); }
    const char* getMyCharacterName() const { return (m_theGame.getMyCharacter() < WANTED_NB_CHARACTERS) ?  characters[m_theGame.getMyCharacter()]
                                                                                                          : characters[WANTED_NB_CHARACTERS-1]; }

    void setOpponentCharacter(unsigned int theCharacter) { m_theGame.setOpponentCharacter(theCharacter); }
    unsigned int getOpponentCharacter() const { return m_theGame.getOpponentCharacter(); }
    const char* getOpponentCharacterName() const { return (m_theGame.getOpponentCharacter() < WANTED_NB_CHARACTERS) ?  characters[m_theGame.getOpponentCharacter()]
                                                                                                              : characters[WANTED_NB_CHARACTERS-1]; }

    void setMyTimeToHit(const unsigned int tth)			{ m_theGame.setMyTimeToHit(tth); }
    const unsigned int getMyTimeToHit()	const			{ return m_theGame.getMyTimeToHit(); }
    void setOpponentTimeToHit(const unsigned int tth)	{ m_theGame.setOpponentTimeToHit(tth); }
    const unsigned int getOpponentTimeToHit()	const	{ return m_theGame.getOpponentTimeToHit(); }

    void startGame();
    void startServer();
    void startClient();
    void startDuel();

    void onError(const char* errorMessage, bool fatal = false);

    void login();

    bool showAchievements();
    void postAchievement(const char* idName, int percentComplete);
    void clearAllAchievements();

    bool showScores();
    void postScore(const char* idName, int score);
    void clearAllScores();

    void start();
    void stop();
    bool isSignedIn();
    bool isGameStarted() const 		{ return (m_theGame.getGameStatus() == eStarted); }
    void setCommunicationGooglePlayGameServices();
    void setCommunicationBlueTooth();
    void setCommunicationTest();

    void notifyGameInitialized();
    void notifySceneInitialized();
    void notifyTargetPosition(CCPoint pos);
    void notifyTargetHit(int timeToHit);
    void notifyWinner(ePlayer winner);

    void duelWon();
    void duelLost();
    void updateWinRatio();
    void displayLeaderboard();
};

} // namespace wanted

#endif /* __GAMECENTER_H__ */
