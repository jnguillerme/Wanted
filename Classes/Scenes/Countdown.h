#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "cocos2d.h"

using namespace cocos2d;

class Countdown : public CCNode
{
	CCLabelTTF* m_label;
	unsigned int m_value;
	SEL_CallFunc m_onCountdownDone;
public:
	virtual ~Countdown();
	bool initWithOnDoneFunc(SEL_CallFunc onCountdownDone);

	static Countdown* createWithOnDoneFunc(SEL_CallFunc onCountdownDone) {
		Countdown *pRet = new Countdown();
	    if (pRet && pRet->initWithOnDoneFunc(onCountdownDone)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }
	}


    void fadeOutDone(CCNode* sender);

};

#endif // _COUNTDOWN_H_
