#include "FeetExtensions.h"

FeetExtensions::FeetExtensions():
	Unit(sf::Vector2f(100, 100), "FeetExt", "FeetExt"),
	mLeft("StixFeetExtendL", 200, 1),
	mRight("StixFeetExtend", 200, 1),
	mLeftAni("StixFeetExtendAniL", 60, 5),
	mRightAni("StixFeetExtendAni", 60, 5),
	mLeftAniMagnet("StixFeetExtendAniLMagnet", 60, 5),
	mRightAniMagnet("StixFeetExtendAniMagnet", 60, 5)
{
	mSprite=TextureManager::getSprite("FeetExt");
	mActiveAnimation=&mRight;
	mTimer.restart();
}

void FeetExtensions::update(){
	mActiveAnimation->update();
	if(mFacingRight==true && mRightAni.getCurrentFrame()!=4 && mLeftAni.getCurrentFrame()!=4 && mRightAniMagnet.getCurrentFrame()!=4 && mLeftAniMagnet.getCurrentFrame()!=4)
	{
		if(mMagnet==true)
			mActiveAnimation=&mRightAniMagnet;
		else
			mActiveAnimation=&mRightAni;
	}
	else if(mFacingRight==false && mRightAni.getCurrentFrame()!=4 && mLeftAni.getCurrentFrame()!=4 && mRightAniMagnet.getCurrentFrame()!=4 && mLeftAniMagnet.getCurrentFrame()!=4)
	{
		if(mMagnet==true)
			mActiveAnimation=&mLeftAniMagnet;
		else
			mActiveAnimation=&mLeftAni;
	}
	else if(mFacingRight==true)
	{
		mActiveAnimation=&mRight;
		mSolid=true;
	}
	else
	{
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
	mLeftAniMagnet.restart();
	mRightAniMagnet.restart();
};