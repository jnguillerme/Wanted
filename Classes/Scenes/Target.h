#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "GameCenter/GameCenterMessage.h"

using namespace cocos2d;
namespace wanted {


class Target : public CCNode {

	CCSprite* m_target;
	struct cc_timeval m_targetShowStartTime;
	CCPoint m_targetPosition;

public:
	Target() : CCNode(), m_target(0), m_targetShowStartTime(), m_targetPosition() {}
	virtual ~Target() {}
	CREATE_FUNC(Target);

	virtual bool init();
    void setPosition();
    void show();
    bool wasHit(CCPoint location) const { return (m_target) ? m_target->boundingBox().containsPoint(location) : false; }
    int onHit();

    void registerNotifications();
    void processWantedTargetPos(GameCenterMessage *gcMsg);


};

} 	//namespace wanted

#endif 	//__TARGET_H__
