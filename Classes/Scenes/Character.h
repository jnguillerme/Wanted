#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

using namespace cocos2d;

#define CHARACTER_LEFT	0x01
#define CHARACTER_RIGHT	0x02

class Character : public CCNode
{
	CCSprite* m_characterSprite;
	CCString m_type;
public:
	virtual bool initWithTypeAndPosition(const char* type, unsigned int position);

	static Character* createWithTypeAndPosition(const char* type, unsigned int position) {
	    Character *pRet = new Character();
	    if (pRet && pRet->initWithTypeAndPosition(type, position)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }
	}

	void shoot();
};

#endif // __CHARACTER_H__
