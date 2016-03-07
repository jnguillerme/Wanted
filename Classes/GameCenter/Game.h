#ifndef __GAME_H__
#define __GAME_H__
#include "cocos2d.h"
#include "GameCenterMessage.h"


namespace wanted {
using namespace cocos2d;

enum eGameStatus {eNotStarted = 0, eStarted = 1 };

struct Player{
	CC_SYNTHESIZE(unsigned int, m_timeToHit, TimeToHit);
	CC_SYNTHESIZE(unsigned int, m_character, Character);

public:
	Player() : m_timeToHit(0), m_character(0) {}
	virtual ~Player() {}
} ;

class Game {
	CC_SYNTHESIZE(eGameStatus, m_gameStatus, GameStatus);

	Player m_me;
	Player m_opponent;
public:
	Game() : m_gameStatus(eNotStarted), m_me(), m_opponent() {}
	virtual ~Game() {};

    void setMyCharacter(const unsigned int theCharacter) { m_me.setCharacter(theCharacter); }
    const unsigned int getMyCharacter() const { return m_me.getCharacter(); }

    void setOpponentCharacter(const unsigned int theCharacter) { m_opponent.setCharacter(theCharacter); }
    const unsigned int getOpponentCharacter() const { return m_opponent.getCharacter(); }

    void setMyTimeToHit(const unsigned int tth)			{ m_me.setTimeToHit(tth); }
    const unsigned int getMyTimeToHit()	const			{ return m_me.getTimeToHit(); }
    void setOpponentTimeToHit(const unsigned int tth)	{ m_opponent.setTimeToHit(tth); }
    const unsigned int getOpponentTimeToHit()	const	{ return m_opponent.getTimeToHit(); }

};

}

#endif // __GAME_H__
