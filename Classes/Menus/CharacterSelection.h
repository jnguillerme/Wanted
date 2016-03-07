#ifndef __CHARACTER_SELECTION_H__
#define __CHARACTER_SELECTION_H__

#include "cocos2d.h"
#include "GameCenter/GameCenterMessage.h"

using namespace cocos2d;

namespace wanted {

class CharacterSelection : public CCLayer {

public:
	static cocos2d::CCScene* scene();
	virtual bool init();
    CREATE_FUNC(CharacterSelection);

protected:
    virtual void onKidSelected(cocos2d::CCObject* pSender);
    virtual void onOutlawSelected(cocos2d::CCObject* pSender);
    virtual void onSamaritanSelected(cocos2d::CCObject* pSender);

    void processWantedGameInitialized(GameCenterMessage* gcMsg);

private:
    void onCharacterSelected(const unsigned int character);
};

} 		// namespace wanted

#endif //__CHARACTER_SELECTION_H__
