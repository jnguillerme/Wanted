#include "Target.h"
#include "GameCenter/GameCenter.h"

namespace wanted {


bool Target::init()
{
	if ( !CCNode::init() ){
        return false;
    }
	registerNotifications();

	// create and scale target sprite
    m_target = CCSprite::create("Target.png");
    m_target->setScaleX(50 / m_target->getContentSize().width);
    m_target->setScaleY(50 / m_target->getContentSize().height);

    m_target->setVisible(false);
    this->addChild(m_target);
    return true;
}

void Target::show()
{
	////////////////////////////
    // add target as invisible
    setPosition();

	m_target->setVisible(true);

    // init the timer
    CCTime::gettimeofdayCocos2d(&m_targetShowStartTime, NULL);
}

////
// Target was hit
// remove it and return the time it took to hit it
////
int Target::onHit()
{
	CCLog("com.jino.wanted.Target : Target has been hit!");

	m_target->setVisible(false);
	struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);

    int timeToHit = (int)CCTime::timersubCocos2d(&m_targetShowStartTime, &now);

	CCLog("com.jino.wanted.Target : Time to hit target %d", timeToHit);

    GameCenter::sharedGC().notifyTargetHit(timeToHit);
    return timeToHit;
}


void Target::setPosition()
{
	CCPoint actualPosition(m_targetPosition);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// make sure the whole target is visible
	if (m_targetPosition.x < m_target->boundingBox().size.width / 2) {
		actualPosition.x = m_target->boundingBox().size.width / 2;
	}

	if (m_targetPosition.x > (size.width - m_target->boundingBox().size.width / 2) ) {
		actualPosition.x = size.width - m_target->boundingBox().size.width / 2;
	}

	if (m_targetPosition.y < m_target->boundingBox().size.height / 2) {
		actualPosition.y = m_target->boundingBox().size.height / 2;
	}

	if (m_targetPosition.y > (size.height - m_target->boundingBox().size.height / 2) ) {
		actualPosition.y = size.height- m_target->boundingBox().size.height / 2;
	}

	m_target->setPosition(actualPosition);
}

///////////
// Messages management
//////////
void Target::registerNotifications()
{
	GC_REGISTER_NOTIFICATION(this, Target::processWantedTargetPos, WANTED_NOTIFY_TARGET_POS);
}

void Target::processWantedTargetPos(GameCenterMessage *gcMsg)
{
	if (gcMsg->getBytesLen() == 2) {
		CCLog("com.jino.wanted : Target:: processWantedTargetPos(%d, %d)", gcMsg->getBytes()[0], gcMsg->getBytes()[1]);
		CCPoint pos((float)gcMsg->getBytes()[0], (float)gcMsg->getBytes()[1]);
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		pos.x = (pos.x * size.width) / 100;			// position is received as a ratio to accommodate different screen size
		pos.y = (pos.y * size.height) / 100;

		m_targetPosition = pos;
	}

	GC_UNREGISTER_NOTIFICATION(this, WANTED_NOTIFY_TARGET_POS);

}

} // namespace wanted
