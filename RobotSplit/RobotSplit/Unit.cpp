#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
{
	mPosition=position;
	mId=id;
}