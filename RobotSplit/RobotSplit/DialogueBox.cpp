#include "DialogueBox.h"

DialogueBox::DialogueBox(sf::Vector2f position, std::string text, bool fadeIn)
	:Unit(position, "DialogueBox", "DialogueBox1", false)
{
	if (fadeIn)
	{
		mAlpha=0;
	}
	else
	{
		mAlpha=255;
	}
}

void DialogueBox::update()
{
	const int FADE_SPEED=1;
	
	//Fade in
	if (mAlpha<255-FADE_SPEED)
	{
		mAlpha+=FADE_SPEED;
	}
	else if (mAlpha<255)
	{
		mAlpha=255;
	}
}

sf::Sprite DialogueBox::getSprite()
{
	mSprite.setColor(sf::Color(255, 255, 255, mAlpha));
	return mSprite;
}