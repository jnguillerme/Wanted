#include "Countdown.h"

Countdown::~Countdown()
{
	if (m_label) {
		m_label->release();
		m_label = NULL;
	}
}

bool Countdown::initWithOnDoneFunc(SEL_CallFunc onCountdownDone)
{
	if ( !CCNode::init()) {
		return false;
	}

	m_value = 3;
	m_onCountdownDone = onCountdownDone;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_label = CCLabelTTF::create("3", "PressStart2P.ttf", 60);
	m_label->setPosition( ccp(winSize.width/2, 3* winSize.height/4) );

	CCFiniteTimeAction *actionFadeOut = CCFadeOut::create(2.0);
	CCFiniteTimeAction* actionFadeOutDone = CCCallFuncN::create( this, callfuncN_selector(Countdown::fadeOutDone));
	m_label->runAction( CCSequence::create(actionFadeOut, actionFadeOutDone, NULL) );
	this->addChild(m_label);

	return true;
}
void Countdown::fadeOutDone(CCNode* sender)
{
		CCLabelTTF *label = (CCLabelTTF*)sender;
	if ((m_value--) > 1) {
		CCString* labelValue = CCString::createWithFormat("%d", m_value);
		m_label->setString(labelValue->getCString());
		CCFiniteTimeAction *actionFadeOut = CCFadeOut::create(2.0);
		CCFiniteTimeAction* actionFadeOutDone = CCCallFuncN::create( this, callfuncN_selector(Countdown::fadeOutDone));
		m_label->runAction( CCSequence::create(actionFadeOut, actionFadeOutDone, NULL) );
	} else {
		this->removeChild(label, true);
	}
}

