#include "Courser.h"
#include "TextureManager.h"
#include "Window.h"

Courser::Courser()
{
	mSprite=TextureManager::getSprite("StixBrain");
}

sf::Sprite* Courser::getSprite()
{
	sf::Vector2f Mouse(sf::Mouse::getPosition(Window.getWindow().getSize().x), sf::Mouse::getPosition(Window.getWindow().getPosition().y));
	mSprite.setPosition(Mouse);
	return &mSprite;
}