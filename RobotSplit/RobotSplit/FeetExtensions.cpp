#include "FeetExtensions.h"

FeetExtensions::FeetExtensions(std::string spriteName):
	Unit(sf::Vector2f(100, 100), "FeetExt", spriteName)
{
	mSprite=TextureManager::getSprite(spriteName);
}