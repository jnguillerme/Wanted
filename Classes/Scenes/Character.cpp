#include "AppData.h"
#include "Character.h"


// on "init" you need to initialize your instance
bool Character::initWithTypeAndPosition(const char* type, unsigned int position)
{
    if ( !CCNode::init() ){
        return false;
    }

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float scaleX = AppData::sharedData().getScaleX() / 2;
	float scaleY = AppData::sharedData().getScaleY() / 2;
	// create sprite
	m_type = type;
    CCString *spriteFileName = CCString::createWithFormat("Character/%s.png", type);
    m_characterSprite = CCSprite::create(spriteFileName->getCString());
    m_characterSprite->setScaleX(scaleX);
    m_characterSprite->setScaleY(scaleY);

    int characterOffsetX = 40 + ((m_characterSprite->getContentSize().width * scaleX));
    int characterOffsetY = 40 + ((m_characterSprite->getContentSize().height* scaleY) /2);

    if (position == CHARACTER_LEFT) {
    	m_characterSprite->setPosition(ccp(characterOffsetX, characterOffsetY));
    	m_characterSprite->setRotationY(180);
    } else {
    	m_characterSprite->setPosition(ccp(size.width - characterOffsetX, characterOffsetY));
    }

    this->addChild(m_characterSprite);

    return true;
}

void Character::shoot()
{
	CCString *spriteFileName = CCString::createWithFormat("Character/%sShot.png", m_type.getCString());
	m_characterSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(spriteFileName->getCString()));
}
