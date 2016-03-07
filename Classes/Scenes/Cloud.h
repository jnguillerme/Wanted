#ifndef __CLOUD_H__
#define __CLOUD_H__

#include "cocos2d.h"

using namespace cocos2d;

namespace wanted {

class Duel;

class Cloud : public CCNode
{
	CCSprite* m_cloudSprite;
	static int m_nbClouds;
public:
	virtual bool init();
	virtual bool initWithPositionX(int x);
    void moveDone(CCNode* sender);

    static void setNbClouds(const int nbClouds) { m_nbClouds = nbClouds; }
    CREATE_FUNC(Cloud);

    static Cloud* createWithPositionX(int x) {
	    Cloud *pRet = new Cloud();
	    if (pRet && pRet->initWithPositionX(x)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }
	}
};

}		 // namespace wanted
#endif // __CLOUD_H__
