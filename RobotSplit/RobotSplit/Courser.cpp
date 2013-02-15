#include "Courser.h"
#include "TextureManager.h"

Courser::Courser()
{
	mSprite=TextureManager::getSprite("StixBrain");
}

sf::Sprite* Courser::getSprite()
{
	sf::Vector2f Mouse(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	mSprite.setPosition(Mouse);
	return &mSprite;
}