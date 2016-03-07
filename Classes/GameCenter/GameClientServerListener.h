#ifndef __GAME_CLIENT_SERVER_LISTENER_H__
#define __GAME_CLIENT_SERVER_LISTENER_H__

#include "cocos2d.h"
#include "GameCenterMessage.h"

using namespace cocos2d;

namespace wanted {

class GameClientServerListener : public CCObject {

public:
	GameClientServerListener();
	virtual ~GameClientServerListener();

protected:
	bool init();

	virtual void registerNotifications() = 0;
	virtual void onStartGame(GameCenterMessage* gcMsg) = 0;

	void processWantedNotifyCharacter(GameCenterMessage* gcMsg);
	void processWantedStartGame(GameCenterMessage* gcMsg);
	void processWantedSceneInitialized(GameCenterMessage* gcMsg);
};

}		// namespace wanted

#endif // __GAME_CLIENT_SERVER_LISTENER_H__
