#include "WantedLayer.h"

namespace wanted {
/**
 * addSpriteAndScale
 */
void WantedLayer::addSpriteAndScale(CCLayer* layer, CCSprite* sprite, int bottomY, int topY, int zOrder)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    // position the sprite on the centre of the screen + black band on top and bottom

	sprite->setScaleX(size.width / sprite->getContentSize().width);
	sprite->setScaleY((topY - bottomY) / sprite->getContentSize().height);

	sprite->setPosition( ccp(size.width/2,  bottomY +( sprite->boundingBox().size.height / 2)) );


    // add the sprite as a child to this layer
    layer->addChild(sprite, zOrder);
}

} // namespace wanted
