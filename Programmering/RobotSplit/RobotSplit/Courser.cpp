#include "Courser.h"
#include "TextureManager.h"
#include "Window.h"

Courser::Courser()
{
	mSprite=TextureManager::getSprite("StixBrain");
	mSprite.setColor(sf::Color(255, 255, 255, 126));
}

sf::Sprite* Courser::getSprite(const sf::Vector2f& mVec)
{
	//sf::Vector2f Mouse(mVec);
	mSprite.setPosition(mVec);
	return &mSprite;
}