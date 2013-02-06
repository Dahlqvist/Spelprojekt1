#include "FeetExtensions.h"

FeetExtensions::FeetExtensions():
	Unit(sf::Vector2f(100, 100), "FeetExt", "FeetExt"),
	mLeft("StixFeetExtend", 200, 1),
	mRight("StixFeetExtend", 200, 1),
	mLeftAni("StixFeetExtendAni", 200, 5),
	mRightAni("StixFeetExtendAni", 200, 5)
{
	mSprite=TextureManager::getSprite("FeetExt");
	mActiveAnimation=&mRight;
	mTimer.restart();
}

void FeetExtensions::update(){
	mActiveAnimation->update();
	if(mFacingRight==true && mTimer.getElapsedTime().asSeconds() < 0.8)
	{
		mActiveAnimation=&mRightAni;
	}
	else if(mFacingRight==false && mTimer.getElapsedTime().asSeconds() < 0.8)
	{
		mActiveAnimation=&mLeftAni;
	}
	else if(mFacingRight==true)
	{
		mActiveAnimation=&mRight;
	}
	else
	{
		mActiveAnimation=&mLeft;
	}
}