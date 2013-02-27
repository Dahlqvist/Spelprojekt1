#include "Checkpoint.h"

Checkpoint::Checkpoint(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string spriteOn, std::string spriteOff)
	:Unit(position, size, offset, "Checkpoint", spriteOff, false, true)
	,mSpriteOn(TextureManager::getSprite(spriteOn))
	,mSpriteOff(TextureManager::getSprite(spriteOff))
	,mActive(false)
{

}

void Checkpoint::activate()
{
	mSprite=mSpriteOn;
	mActive=true;
}

void Checkpoint::deactivate()
{
	mSprite=mSpriteOff;
	mActive=false;
}