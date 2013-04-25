#include "PlayerLight.h"
#include "TextureManager.h"

PlayerLight::PlayerLight()
{
	mActiveLight=&mLightTogether;
	mLightTogether=TextureManager::getSprite("LightTogether");
	mLightBody=TextureManager::getSprite("LightBody");
	mLightFeet=TextureManager::getSprite("LightFeet");
}

void PlayerLight::setSprite(bool together, bool bodyActive, bool attachedWall, int wall, sf::Vector2f Pos)
{
	if(together==true)
	{
		mActiveLight=&mLightTogether;
		mActiveLight->setPosition(Pos+sf::Vector2f(-32, -48));
	}
	else if(bodyActive==true)
	{
		mActiveLight=&mLightBody;
		mActiveLight->setPosition(Pos+sf::Vector2f(-32, -32));
	}
	else
	{
		mActiveLight=&mLightFeet;
		if(attachedWall==false)
		{
			mActiveLight->setPosition(Pos+sf::Vector2f(-32, -64));
		}
		else if(wall==0 || wall==2)
		{
			mActiveLight->setPosition(Pos+sf::Vector2f(-32, -64));
		}
		else if(wall==1)
		{
			mActiveLight->setPosition(Pos+sf::Vector2f(-32, -48));
		}
	}
}

sf::Sprite* PlayerLight::getSprite()
{
	return mActiveLight;
}