#ifndef __GAME_SERVER_LISTENER_H__
#define __GAME_SERVER_LISTENER_H__

#include "GameClientServerListener.h"

namespace wanted {

class GameServerListener : public GameClientServerListener {

public:
	GameServerListener() : GameClientServerListener() {	}
	~GameServerListener() {}

	CREATE_FUNC(GameServerListener);


private:
	bool init();
	const CCPoint calculateTargetPosition() const;

	ePlayer getWinner() const;
	void registerNotifications();
	void onStartGame(GameCenterMessage* gcMsg);
	void processWantedNotifyTargetHit(GameCenterMessage *gcMsg);
	void processWantedOpponentIsComputer(GameCenterMessage *gcMsg);
};

} // namespace wanted

#endif // __GAME_SERVER_LISTENER_H__
