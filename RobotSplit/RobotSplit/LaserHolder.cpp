#include "LaserHolder.h"

LaserHolder::LaserHolder(Laser* laser):
	Unit(laser->getPosition(), "LaserHolder", "LaserHolder", false)
{
	mSprite=TextureManager::getSprite("YellowLaserHolder");
	mPosition=laser->getPosition();//+sf::Vector2f(2, -2);
	mPosition+=sf::Vector2f(-8, -8);
	mRotation=laser->getRotation();
	//mSprite.setOrigin(8, 8);
	//mSprite.setRotation(mRotation);
	mSprite.setPosition(mPosition);
}

