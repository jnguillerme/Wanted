#ifndef __DUEL_SCENE_H__
#define __DUEL_SCENE_H__

#include "cocos2d.h"
#include "Utils/WantedLayer.h"
#include "Target.h"
#include "Countdown.h"
#include "Character.h"
#include "Cloud.h"

using namespace cocos2d;

namespace wanted {

#define NB_CLOUDS 5
#define CLOUDS_ZORDER 15

class Duel : public CCLayer {
	unsigned int m_nbClouds;
	Target* m_target;
    CC_SYNTHESIZE_READONLY(Countdown*, m_countdown, Layer);
    float m_initialScaleY;
    Character* m_myCharacter;
    Character* m_myOpponentCharacter;
    bool m_duelInProgress;

public:
    Duel() : CCLayer(), m_nbClouds(0), m_target(NULL), m_countdown(0), m_initialScaleY(1.0),
    		m_myCharacter(NULL), m_myOpponentCharacter(NULL), m_duelInProgress(false) {}
    ~Duel();
	virtual bool init();
	void onExit();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Duel);


	void ccTouchesEnded(CCSet* touches, CCEvent* event);
	void ccTouchesBegan(CCSet* touches, CCEvent* event);
	void ccTouchesMoved(CCSet* touches, CCEvent* event);

private:
    void createBackground();
    void addClouds();

	void registerWithTouchDispatcher();

	void displayGameResult(const char* result);

	void checkIfTargetHit(CCPoint location);

    // selectors callback
    void createCloud(float dt);
    void blowWind(float dt);
    void blowWindDone(CCNode* sender);
    void countdown(float dt);
    void onCountdownDone();

    void registerNotifications();
    void processWantedStartDuel(GameCenterMessage* gcMsg);
    void processWantedWinner(GameCenterMessage* gcMsg);
    void processBackToMainMenu(GameCenterMessage* gcMsg);
};

} // namespace wanted

#endif // __DUEL_SCENE_H__
