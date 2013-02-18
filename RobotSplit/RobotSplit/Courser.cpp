#include "Courser.h"
#include "TextureManager.h"
#include "Window.h"

Courser::Courser()
{
	mSprite=TextureManager::getSprite("StixBrain");
}

sf::Sprite* Courser::getSprite(sf::Vector2f mVec)
{
	sf::Vector2f Mouse(mVec);
	mSprite.setPosition(Mouse);
	mSprite.setColor(sf::Color(255, 255, 255, 126));
	return &mSprite;
}