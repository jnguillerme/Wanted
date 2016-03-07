
#ifndef __GAME_CENTER_MESSAGE_H__
#define __GAME_CENTER_MESSAGE_H__

#include "cocos2d.h"
#include <stdarg.h>

using namespace cocos2d;
namespace wanted {


// messages definition
#define WANTED_START_GAME			0x000
#define WANTED_GAME_INITIALIZED		0x001
#define WANTED_SCENE_INITIALIZED	0x002
#define	WANTED_NOTIFY_CHARACTER		0x003
#define WANTED_NOTIFY_TARGET_POS	0x004
#define WANTED_NOTIFY_DUEL_START	0x005
#define WANTED_NOTIFY_TARGET_HIT	0x006
#define WANTED_NOTIFY_WINNER		0x007
#define WANTED_ERROR				0x008
#define WANTED_OPPONENT_IS_COMPUTER 0x009
#define WANTED_NB_NOTIFICATIONS		0x010

const char notifications[WANTED_NB_NOTIFICATIONS][50] = {	{"WANTED_START_GAME"},
															{"WANTED_GAME_INITIALIZED"},
															{"WANTED_SCENE_INITIALIZED"},
															{"WANTED_NOTIFY_CHARACTER"},
															{"WANTED_NOTIFY_TARGET_POS"},
															{"WANTED_NOTIFY_DUEL_START"},
															{"WANTED_NOTIFY_TARGET_HIT"},
															{"WANTED_NOTIFY_WINNER"},
															{"WANTED_ERROR"},
															{"WANTED_OPPONENT_IS_COMPUTER"},
														};

enum ePlayer { opponent = 0, me = 1, undefined = 2};


// characters definition
#define WANTED_CHARACTER_KID		0x000
#define WANTED_CHARACTER_OUTLAW		0x001
#define WANTED_CHARACTER_SAMARITAN	0x002
#define WANTED_NB_CHARACTERS 		0x003
const char characters[WANTED_NB_CHARACTERS][30] = {	{"Kid"},
													{"OutLaw"},
													{"Samaritan"}
													};

class GameCenterMessage : public CCObject {
	CC_SYNTHESIZE_READONLY(unsigned int, m_msgType, MsgType);
	CC_SYNTHESIZE_READONLY(unsigned int*, m_bytes, Bytes);
	CC_SYNTHESIZE_READONLY(unsigned int, m_bytesLen, BytesLen);

public:
	GameCenterMessage() : m_msgType(0), m_bytes(0), m_bytesLen(0) {}
	virtual ~GameCenterMessage() {
		if (m_bytes) {
			delete m_bytes;
			m_bytes = 0;
		}
	}

	static GameCenterMessage* createWithMessageType(const unsigned int msgType) {
		GameCenterMessage *pRet = new GameCenterMessage();
	    if (pRet && pRet->initWithMessageType(msgType)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }

	}
	static GameCenterMessage* createWithByteArray(const unsigned int* bytes, const unsigned int size) {
		GameCenterMessage *pRet = new GameCenterMessage();
	    if (pRet && pRet->initWithByteArray(bytes, size)) {
	        pRet->autorelease();
	        return pRet;
	    }
	    else {
	        delete pRet;
	        pRet = 0;
	        return 0;
	    }
	}

	static GameCenterMessage* createWithMessageTypeAndParams(const unsigned int msgType, const unsigned int count, ...) {
		GameCenterMessage *pRet = new GameCenterMessage();

	    if (pRet) {
	    	va_list params;
	    	va_start(params, count);
	    	if (pRet->initWithMessageTypeAndParams(msgType, count, params)) {
	    		pRet->autorelease();
	    	} else {
	    		pRet = 0;
	    	}
	    	va_end(params);
	    }

	    if (!pRet){
	        delete pRet;
	    }
		return pRet;

	}

	const char *getMsgTypeName() const 	{ return  notifications[m_msgType]; }
	virtual bool initWithByteArray(const unsigned int* bytes, const unsigned int size);
	virtual bool initWithMessageType(const unsigned int msgType);
	virtual bool initWithMessageTypeAndParams(const unsigned int msgType, const unsigned int count, va_list params);

};

} // namespace wanted

#endif // __GAME_CENTER_MESSAGE_H__
