#include "Star.h"

Star::Star(Animation ani, sf::Vector2f startPos, bool active, bool loop):
	mAnimation(ani)
{
	mPosition=startPos;
	mActive=active;
	mLoop=loop;
	mDone=false;
}

void Star::update()
{
	if(mActive==true)
	{
		if(mLoop==true)
		{
			mAnimation.update();
		}
		else if(mAnimation.getCurrentFrame()!=mAnimation.getMaxFrame()-1)
		{
			mAnimation.update();
		}
		else
		{
			mDone=true;
		}
	}
}

sf::Sprite Star::getSprite()
{
	mSprite=mAnimation.getSprite();
	mSprite.setPosition(mPosition);
	return mSprite;
}

void Star::setActive(bool b)
{
	mActive=b;
}
void Star::setPosition(sf::Vector2f vec)
{
	mPosition=vec;
}
bool Star::getActive()
{
	return mActive;
}
sf::Vector2f Star::getPosition()
{
	return mPosition;
}
bool Star::getDone()
{
	return mDone;
}