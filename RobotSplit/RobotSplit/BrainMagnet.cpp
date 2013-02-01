#include "BrainMagnet.h"

BrainMagnet::BrainMagnet(std::string spriteName):
	Unit(sf::Vector2f(100, 100), "FeetExt", spriteName)
{
	mSprite=TextureManager::getSprite(spriteName);
	mSolid=true;
}

	void BrainMagnet::setSolid(bool b){
		mSolid=b;
	}