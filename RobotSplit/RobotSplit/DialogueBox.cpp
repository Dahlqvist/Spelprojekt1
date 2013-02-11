#include "DialogueBox.h"

DialogueBox::DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible)
	:Unit(position, "DialogueBox", spriteName, false)
	,mText(text)
	,mVisible(visible)
	,mFadeIn(fadeIn)
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
		mText.setColor(sf::Color(255, 255, 255, mAlpha));
	}
	else if (!mFadeIn)
	{
		mAlpha=255;
	}
	else if (mAlpha<255-FADE_SPEED)
	{
		mAlpha+=FADE_SPEED;
		mText.setColor(sf::Color(255, 255, 255, mAlpha));
	}
	else if (mAlpha<255)
	{
		mAlpha=255;
		mText.setColor(sf::Color(255, 255, 255, mAlpha));
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

sf::Text DialogueBox::getText()
{
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