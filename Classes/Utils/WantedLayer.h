#ifndef _WANTEDLAYER_H_
#define _WANTEDLAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

namespace wanted {
class WantedLayer {
public:
	static void addSpriteAndScale(CCLayer* layer, CCSprite* _sprite, int _bottomY, int _topY, int _zOrder);
};

} // namespace wanted

#endif //_WANTEDLAYER_H_
