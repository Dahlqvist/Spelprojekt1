#include "LaserHolder.h"

LaserHolder::LaserHolder(Laser* laser):
	Unit(laser->getPosition(), "LaserHolder", "LaserHolder", false)
{
	mSprite=TextureManager::getSprite("YellowLaserHolder");
	mPosition=laser->getPosition();//+sf::Vector2f(2, -2);
	mRotation=laser->getRotation()-180;
	//mSprite.setOrigin(mSprite.getGlobalBounds().width/2, mSprite.getGlobalBounds().height/2);
	mSprite.setRotation(mRotation);
	mPosition+=sf::Vector2f(2, -2);
	mSprite.setPosition(mPosition);
}

