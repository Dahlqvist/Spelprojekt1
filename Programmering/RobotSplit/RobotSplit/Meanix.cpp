#include "Meanix.h"

Meanix::Meanix(sf::Vector2f pos, std::string sprite, std::string sprite2, Player* player):
Unit(pos, "Meanix", "Meanix", false, true),
	mRight(Animation(sprite, 100, 8)),
	mLeft(Animation(sprite2, 100, 8))
{
	mPosition=pos;
	mLeft.setPosition(mPosition);
	mRight.setPosition(mPosition);
	mSolid=false;
	mPlayer=player;
	mAni=&mLeft;
	if(mPlayer->getCollisionSprite()[1]->getPosition().x<mPosition.x)
	{
		mFacingRight=false;
		mAni=&mLeft;
	}
	else
	{
		mFacingRight=true;
		mAni=&mRight;
	}
}

void Meanix::update()
{
	Meanix::facingStix();
	mAni->update();
}

void Meanix::facingStix()
{
	if(mPlayer->getTogether()==true)
	{
		if(mPlayer->getCollisionSprite()[1]->getPosition().x<mPosition.x)
		{
			mFacingRight=false;
		}
		else
		{
			mFacingRight=true;
		}
	}
	else if(mPlayer->getBodyActive()==true)
	{
		if(mPlayer->getCollisionSprite()[1]->getPosition().x<mPosition.x)
		{
			mFacingRight=false;
		}
		else
		{
			mFacingRight=true;
		}
	}
	else
	{
		if(mPlayer->getCollisionSprite()[0]->getPosition().x<mPosition.x)
		{
			mFacingRight=false;
		}
		else
		{
			mFacingRight=true;
		}
	}

	if(mFacingRight==true)
	{
		mAni=&mRight;
	}
	else
	{
		mAni=&mLeft;
	}
}

void Meanix::setPosition(sf::Vector2f position)
{
	mPosition=position;
	mAni->setPosition(position);
}