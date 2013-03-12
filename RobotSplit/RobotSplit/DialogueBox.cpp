#include "DialogueBox.h"

DialogueBox::DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible, std::string id)
	:Unit(position, id, spriteName, false, true)
	,mText(text)
	,mVisible(visible)
	,mFadeIn(fadeIn)
	,mStartVisible(visible)
	,mStartFadeIn(fadeIn)
	,mHasFaded(false)
{
	const int TEXT_OFFSET_X=10;
	const int TEXT_OFFSET_Y=10;
	const int TEXT_SIZE=14;

	if (fadeIn)
	{
		mAlpha=0;
	}
	else
	{
		mAlpha=255;
	}
	
	mText.setPosition(mPosition.x+TEXT_OFFSET_X, mPosition.y+TEXT_OFFSET_Y);
	mText.setCharacterSize(TEXT_SIZE);

}

void DialogueBox::update()
{
	const int FADE_SPEED=1;

	mLastAlpha=mAlpha;
	
	//Fade in
	if (!mVisible)
	{
		mAlpha=0;
	}
	else if (!mFadeIn)
	{
		mAlpha=255;
	}
	else if (mAlpha>0)
	{
		mAlpha-=FADE_SPEED;
	}
	else if (mAlpha<=0)
	{
		mAlpha=0;
	}

	mVisible=false;
	mHasFaded=false;
}

void DialogueBox::activate()
{
	const int FADE_SPEED=2;

	mVisible=true;

	if (!mFadeIn)
	{
		mAlpha=255;
	}
	else if (!mHasFaded)
	{
		mHasFaded=true;
		if (mAlpha<255-FADE_SPEED)
		{
			mAlpha+=FADE_SPEED;
		}
		else if (mAlpha<255)
		{
			mAlpha=255;
		}
	}
}

void DialogueBox::deactivate()
{
	mVisible=false;
}

void DialogueBox::reset()
{
	mVisible=mStartVisible;
	mFadeIn=mStartFadeIn;
}

void DialogueBox::setReset()
{
	mStartVisible=mVisible;
	mStartFadeIn=mFadeIn;
}

sf::Text DialogueBox::getText()
{
	if (mAlpha!=mLastAlpha)
	{
		mText.setColor(sf::Color(255, 255, 255, mAlpha));
	}
	return mText;
}

sf::Sprite DialogueBox::getSprite()
{
	if (mAlpha!=mLastAlpha)
	{
		mSprite.setColor(sf::Color(255, 255, 255, mAlpha));
	}
	return mSprite;
}

bool DialogueBox::isFullyVisible()
{
	return mAlpha==255;
}

bool DialogueBox::getFadeIn()
{
	return mFadeIn;
}

bool DialogueBox::getVisible()
{
	return mVisible;
}

void DialogueBox::setVisible(bool newbool)
{
	mVisible=newbool;
}

void DialogueBox::setFadeIn(bool newbool)
{
	mFadeIn=newbool;
}

void DialogueBox::forceAlpha(sf::Uint8	alpha)
{
	mAlpha=alpha;
}