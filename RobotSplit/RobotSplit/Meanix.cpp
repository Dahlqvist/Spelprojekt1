#include "Meanix.h"

Meanix::Meanix(sf::Vector2f pos, Player* player):
Unit(pos, "Meanix", "Meanix", false),
	mRight("MeanixAni", 100, 8),
	mLeft("MeanixAniL", 100, 8)
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
			//std::cout << "Hej    ";
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