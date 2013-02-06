#include "DialogueBox.h"

DialogueBox::DialogueBox(sf::Vector2f position, std::string text, bool fadeIn)
	:Unit(position, "DialogueBox", "DialogueBox1", false)
	,mText(text)
{
	const int TEXT_OFFSET_X=10;
	const int TEXT_OFFSET_Y=10;

	if (fadeIn)
	{
		mAlpha=0;
	}
	else
	{
		mAlpha=255;
	}
	
	mText.setPosition(mPosition.x+TEXT_OFFSET_X, mPosition.y+TEXT_OFFSET_Y);
	mText.setCharacterSize(14);

}

void DialogueBox::update()
{
	const int FADE_SPEED=1;
	
	//Fade in
	if (mAlpha<255-FADE_SPEED)
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

sf::Text DialogueBox::getText()
{
	
	return mText;
}

sf::Sprite DialogueBox::getSprite()
{
	mSprite.setColor(sf::Color(255, 255, 255, mAlpha));
	return mSprite;
}