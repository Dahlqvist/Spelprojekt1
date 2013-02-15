#include "DialogueBox.h"

DialogueBox::DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible, std::string id)
	:Unit(position, id, spriteName, false)
	,mText(text)
	,mVisible(visible)
	,mFadeIn(fadeIn)
	,mDeactivated(false)
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
	
	//Fade in
	if (!mVisible)
	{
		mAlpha=0;
	}
	else if (!mFadeIn)
	{
		mAlpha=255;
	}
	else if (mAlpha<255-FADE_SPEED)
	{
		mAlpha+=FADE_SPEED;
	}
	else if (mAlpha<255)
	{
		mAlpha=255;
	}
}

void DialogueBox::hit()
{
	if (mVisible)
	{
		mAlpha=255/2;
	}
}

void DialogueBox::activate()
{
	mVisible=true;
}

void DialogueBox::deactivate()
{
	mVisible=false;
	mDeactivated=true;
}

sf::Text DialogueBox::getText()
{
	mText.setColor(sf::Color(255, 255, 255, mAlpha));
	return mText;
}

sf::Sprite DialogueBox::getSprite()
{
	mSprite.setColor(sf::Color(255, 255, 255, mAlpha));
	return mSprite;
}

bool DialogueBox::isFullyVisible()
{
	return mAlpha==255;
}