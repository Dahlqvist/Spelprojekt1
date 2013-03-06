#include "Meanix.h"

Meanix::Meanix(sf::Vector2f pos):
Unit(pos, "Meanix", new Animation("MeanixAni", 100, 8), false)
{
	mPosition=pos;
	mAnimation->setPosition(mPosition);
	mSolid=false;
}