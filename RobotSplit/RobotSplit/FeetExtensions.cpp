#include "FeetExtensions.h"

FeetExtensions::FeetExtensions():
	Unit(sf::Vector2f(100, 100), "FeetExt", "FeetExt"),
	mLeft("StixFeetExtendL", 200, 1),
	mRight("StixFeetExtend", 200, 1),
	mLeftAni("StixFeetExtendAniL", 100, 5),
	mRightAni("StixFeetExtendAni", 100, 5)
{
	mSprite=TextureManager::getSprite("FeetExt");
	mActiveAnimation=&mRight;
	mTimer.restart();
}

void FeetExtensions::update(){
	mActiveAnimation->update();
	if(mFacingRight==true && mRightAni.getCurrentFrame()!=4 && mLeftAni.getCurrentFrame()!=4)
	{
		if(mMagnet==true)
			mActiveAnimation=&mRightAni;
		else
			mActiveAnimation=&mRightAni;
	}
	else if(mFacingRight==false && mRightAni.getCurrentFrame()!=4 && mLeftAni.getCurrentFrame()!=4)
	{
		if(mMagnet==true)
			mActiveAnimation=&mLeftAni;
		else
			mActiveAnimation=&mLeftAni;
	}
	else if(mFacingRight==true)
	{
		//if(mMagnet==true)
		//	mActiveAnimation=&mRight;
		//else
		mActiveAnimation=&mRight;

		mSolid=true;
	}
	else
	{
		if(mMagnet==true)
			mActiveAnimation=&mLeft;
		else
			mActiveAnimation=&mLeft;
		mSolid=true;
	}
}
void FeetExtensions::setFacingRight(bool b, bool m){
	if(mActiveAnimation==&mRight)
	{
		mActiveAnimation=&mRightAni;
	}
	else
	{
		mActiveAnimation=&mLeftAni;
	}
	mFacingRight=b;
	mMagnet=m;
	mTimer.restart();
	mLeftAni.restart();
	mRightAni.restart();
};