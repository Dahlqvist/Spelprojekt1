#include "Meanix.h"

Meanix::Meanix(sf::Vector2f pos):
Unit(pos, "Meanix", "Meanix", false),
	mAni("MeanixAni", 100, 8)
{
	mPosition=pos;
	mAnimation=&mAni;
	mAnimation->setPosition(mPosition);
	mSolid=false;
}