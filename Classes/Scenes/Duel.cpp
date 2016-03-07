#include "AppData.h"
#include "GameCenter/GameCenter.h"
#include "Duel.h"
#include "Cloud.h"
#include "Menus/MainMenu.h"

using namespace cocos2d;

namespace wanted {
CCScene* Duel::scene()
{
    // 'scene' is an auto release object
    CCScene *scene = CCScene::create();

    // 'layer' is an auto release object
    Duel *layer = Duel::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
/**
 * destructor
 */
Duel::~Duel()
{

}

// on "init" you need to initialize your instance
bool Duel::init()
{
	// init scene
	if ( !CCLayer::init() ){
        return false;
    }

	CCLog("com.jino.wanted : initializing duel scene ...");

	registerNotifications();
	registerWithTouchDispatcher();
    //this->setTouchEnabled(true);

	createBackground();
	addClouds();
	m_target = Target::create();
    this->addChild(m_target, 100);

    // add characters
    m_myCharacter = Character::createWithTypeAndPosition(GameCenter::sharedGC().getMyCharacterName(), CHARACTER_LEFT);
    this->addChild(m_myCharacter, 50);

    m_myOpponentCharacter = Character::createWithTypeAndPosition(GameCenter::sharedGC().getOpponentCharacterName(), CHARACTER_RIGHT);
    this->addChild(m_myOpponentCharacter, 50);

    GameCenter::sharedGC().notifySceneInitialized();
    return true;
}

/**
 * onExit
 */
void Duel::onExit()
{
	//this->setTouchEnabled(false);
}
/**
 * createBackground
 * add background scene
 */
void Duel::createBackground()
{
	CCLog("com.jino.wanted.Duel::createBackground");

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    WantedLayer::addSpriteAndScale(this, CCSprite::create("Ciel.png"), 0, size.height, -1);
    WantedLayer::addSpriteAndScale(this, CCSprite::create("Back_Input_Screen.png"), 0, size.height /3, 0);
    WantedLayer::addSpriteAndScale(this, CCSprite::create("thdPlan.png"), size.height/3, size.height * 0.9, 10);

    // scale to use for clouds
    CCSprite* pSndPlan = CCSprite::create("SndPlan.png");
    AppData::sharedData().setScaleX( size.width / pSndPlan->getContentSize().width );
    AppData::sharedData().setScaleY( size.height / pSndPlan->getContentSize().height );
    WantedLayer::addSpriteAndScale(this, pSndPlan, size.height/3, size.height * 0.9, 20);

    WantedLayer::addSpriteAndScale(this, CCSprite::create("FstPlan.png"), 0, size.height/2, 30);
}

/**
 * addClouds
 * Add clouds to the scene when it starts
 * Clouds will be create randomly
 * */
void Duel::addClouds()
{
	CCLog("com.jino.wanted.Duel::addClouds");

	Cloud::setNbClouds(0);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Cloud* cloud = Cloud::createWithPositionX(40);
	if (cloud) {
		this->addChild(cloud, CLOUDS_ZORDER);
	}

	cloud = Cloud::createWithPositionX(size.width/2);
	if (cloud) {
		this->addChild(cloud, CLOUDS_ZORDER);
	}

	cloud = Cloud::createWithPositionX(size.width - 40);
	if (cloud) {
		this->addChild(cloud, CLOUDS_ZORDER);
	}

    this->schedule(schedule_selector(Duel::createCloud), 1);

}
/**
 * createCloud
 * Add a new random cloud to the scene
 * */
void Duel::createCloud(float dt)
{
	// will a cloud be created ?
	int minCreateCloud = 1;
	int maxCreateCloud = 15;
	int rangeCreateCloud = maxCreateCloud - minCreateCloud;
	int actualCreateCloud = ( rand() % rangeCreateCloud) + minCreateCloud;

	if (actualCreateCloud == 1) {
		Cloud* cloud = Cloud::create();
		if (cloud) {
			this->addChild(cloud, CLOUDS_ZORDER);
		}
	}
}

void Duel::blowWind(float dt)
{
	CCParticleSystemQuad* wind = CCParticleSystemQuad::create("wind2.plist");
	wind->setPosition(ccp(this->getContentSize().width, 80));

	CCActionInterval* blow= CCMoveTo::create(6, ccp(0, 100));
    CCFiniteTimeAction *blowDone = CCCallFuncN::create(this, callfuncN_selector(Duel::blowWindDone));
    wind->runAction( CCSequence::create(blow, blowDone, NULL));

	this->addChild(wind, 100);
}

void Duel::blowWindDone(CCNode* sender)
{
	CCParticleSystem *wind = (CCParticleSystem*)sender;
	wind->stopSystem();
	this->removeChild(wind);
}


void Duel::countdown(float dt)
{
	CCLog("com.jino.wanted.Duel::countdown");

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	m_countdown = Countdown::createWithOnDoneFunc(callfunc_selector(Duel::onCountdownDone));
	this->addChild(m_countdown, 100);

	this->scheduleOnce(schedule_selector(Duel::onCountdownDone), 7);
}

void Duel::onCountdownDone()
{
    // once countdown completed, show the target
	m_target->show();
}

/**
 * checkIfTargetHit
 * called when the user touched the screen
 * will check if the target was hit and notify Gamecenter if so
 */
void Duel::checkIfTargetHit(CCPoint location)
{
	if (m_target && m_target->wasHit(location) ) {
		m_target->onHit();
		m_myCharacter->shoot();
		//target was hit - don't get any more touches until duel result
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}

}

void Duel::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCLog("com.jino.wanted : ccTouchesEnded");

	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );

	// did we hit the target?
	if (m_duelInProgress) {
		checkIfTargetHit(touch->getLocation());
	} else {
		// back to main menu
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCScene *pScene = wanted::MainMenu::scene();
		CCLog("com.jino.wanted : ccTouchesEnded - about to replace scene...");
	    CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void Duel::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCLog("com.jino.wanted : ccTouchesBegan");
}

void Duel::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	CCLog("com.jino.wanted : ccTouchesMoved");
}

void Duel::registerWithTouchDispatcher()
{
	CCLog("com.jino.wanted.Duel::registerWithTouchDispatcher");
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void Duel::displayGameResult(const char* result)
{
//	CCMessageBox(result, "Wanted");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label ;
	label = CCLabelTTF::create(result, "PressStart2P.ttf", 30);
	label->setPosition(ccp(winSize.width/2 , winSize.height*0.6));
	this->addChild(label, 100);

	// get touches again so the player can touch the screen to go back to main menu
	registerWithTouchDispatcher();
}

////////////////////////////////////////////
// Messages management
////////////////////////////////////////////

void Duel::registerNotifications()
{
	CCLog("com.jino.wanted.Duel::registerNotifications");

	GC_REGISTER_NOTIFICATION(this, Duel::processWantedStartDuel, WANTED_NOTIFY_DUEL_START);
	GC_REGISTER_NOTIFICATION(this, Duel::processWantedWinner, WANTED_NOTIFY_WINNER);
	GC_REGISTER_NOTIFICATION(this, Duel::processBackToMainMenu, WANTED_ERROR);

}
/**
 * processWantedStartDuel
 *
 */
void Duel::processWantedStartDuel(GameCenterMessage* gcMsg)
{
	CCLog("com.jino.wanted : Duel is starting...");

	m_duelInProgress = true;
	this->scheduleOnce(schedule_selector(Duel::countdown), 5);

	// animation
//	this->scheduleOnce(schedule_selector(Duel::blowWind), 2);

	GC_UNREGISTER_NOTIFICATION(this, WANTED_NOTIFY_DUEL_START);

}
/**
 * processWantedWinner
 *
 */
void Duel::processWantedWinner(GameCenterMessage* gcMsg)
{
	m_duelInProgress = false;

	if (gcMsg->getBytesLen() == 1) {
		CCLog("com.jino.wanted.Duel : processWantedWinner(%d)", gcMsg->getBytes()[0]);
		ePlayer winner = (gcMsg->getBytes()[0] == 0) ? opponent : (gcMsg->getBytes()[0] == 1) ? me : undefined;
		if (winner == me) {
			// DISPLAY MESSAGE ! I WON !
			CCLog("com.jino.wanted.Duel : processWantedWinner - I WON !!!");
			displayGameResult("vous avez gagne");
			GameCenter::sharedGC().duelWon();
		} else if (winner == opponent) {
			// DISPLAY MESSAGE ! I LOST ...
			CCLog("com.jino.wanted.Duel : processWantedWinner - I LOST :(");
			displayGameResult("vous avez perdu");
			GameCenter::sharedGC().duelLost();
		} else {
			// ERROR
			CCLog("com.jino.wanted.Duel : processWantedWinner - undefined !!!");
		}
	}

	GameCenter::sharedGC().stop();

}
/**
 * processBackToMainMenu
 */
void Duel::processBackToMainMenu(GameCenterMessage* gcMsg)
{
	CCDirector::sharedDirector()->replaceScene(wanted::MainMenu::scene());
}


} // namespace wanted

