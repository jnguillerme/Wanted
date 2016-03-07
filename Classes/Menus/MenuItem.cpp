#include "MenuItem.h"

namespace wanted {

CCMenuItemImage* MenuItem::item(const char * title, CCObject* target, SEL_MenuHandler selector, const bool fEnable)
{
    // 'scene' is an auto release object
	CCMenuItemImage *item = CCMenuItemImage::create("UI/Back_Onglet_Menu.png", "UI/Back_Onglet_Menu.png", target, selector);

	if (item) {
		item->setScale(0.8);
		MenuItem* mi = 	MenuItem::createWithTitle(title, fEnable);

		if (mi) {
			CCSize itemSize = item->getContentSize();
			mi->setPosition(itemSize.width / 2, itemSize.height / 2);
			item->addChild(mi);
		}
	}
    // return the scene
    return item;
}

bool MenuItem::initWithTitle(const char* title, const bool fEnable)
{
	if ( !CCNode::init()) {
		return false;
	}

	CCLabelTTF* label = CCLabelTTF::create(title, "PressStart2P.ttf", 30);

	if (!fEnable) {
		ccColor3B color;
		color.r = 150;
		color.g = 150;
		color.b = 150;
		label->setColor(color);
	}
	this->addChild(label);

	return true;
}

}	// namespace wanted
