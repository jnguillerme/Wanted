#ifndef __GAME_CLIENT_LISTENER_H__
#define __GAME_CLIENT_LISTENER_H__

#include "GameClientServerListener.h"

namespace wanted {

class GameClientListener : public GameClientServerListener {
	bool m_isTargetPositionSet;

public:
	GameClientListener() : GameClientServerListener(), m_isTargetPositionSet(false) {}
	~GameClientListener() {}

	CREATE_FUNC(GameClientListener);

private:
	bool init();

	void registerNotifications();
	void onStartGame(GameCenterMessage* gcMsg);
	void processWantedTargetPos(GameCenterMessage* gcMsg);
	void processWantedNotifyTargetHit(GameCenterMessage *gcMsg);
};

}		// namespace wanted

#endif // __GAME_CLIENT_LISTENER_H__
