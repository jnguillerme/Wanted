#include "AppData.h"
#include "Cloud.h"
#include "Duel.h"

namespace wanted {

int Cloud::m_nbClouds = 0;

// on "init" you need to initialize your instance
bool Cloud::init()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	return initWithPositionX(size.width);
}

// on "init" you need to initialize your instance
bool Cloud::initWithPositionX(int x)
{
	if ( !CCNode::init() ){
        return false;
    }

    if ( m_nbClouds >= 5 || !CCNode::init() ){
        return false;
    }

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// get cloud height position
	int minHeight = size.height - 130;
	int maxHeight = size.height - 200;
	int rangeHeight= maxHeight - minHeight;
	int actualHeight = ( rand() % rangeHeight) + minHeight;

	// get cloud type
	int minCloudType = 1;
	int maxCloudType = 5;
	int rangeCloudType = maxCloudType - minCloudType;
	int actualCloudType= ( rand() % rangeCloudType) + minCloudType;

    // create sprite
    CCString *spriteFileName = CCString::createWithFormat("Cloud%d.png", actualCloudType);
    m_cloudSprite = CCSprite::create(spriteFileName->getCString());

    int cloudPosX = x +  m_cloudSprite->getContentSize().width;
    m_cloudSprite->setPosition(ccp(cloudPosX, actualHeight));

    m_cloudSprite->setScaleX(AppData::sharedData().getScaleX() / 2);
    m_cloudSprite->setScaleY(AppData::sharedData().getScaleY() / 2);

    // create Action
    CCActionInterval* move = CCMoveTo::create((100* (cloudPosX /size.width)), ccp(- m_cloudSprite->getContentSize().width / 2, actualHeight));
    CCFiniteTimeAction *moveDone = CCCallFuncN::create(this, callfuncN_selector(Cloud::moveDone));

    // start movement and add the sprite
    m_cloudSprite->runAction(CCSequence::create(move, moveDone, NULL));
    this->addChild(m_cloudSprite);

    m_nbClouds++;
    return true;
}

void Cloud::moveDone(CCNode* sender)
{
	m_nbClouds --;
	this->removeFromParentAndCleanup(true);
}

} 		// namespace wanted
