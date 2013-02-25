#include "Collision.h"
#include <iostream>

std::set<Unit*> Collision::mUnitsOnTopLeft;
std::set<Unit*> Collision::mUnitsOnTopRight;
std::set<Unit*> Collision::mUnitsOnBottomLeft;
std::set<Unit*> Collision::mUnitsOnBottomRight;

std::set<Unit*> Collision::mUnitsOnLeftTop;
std::set<Unit*> Collision::mUnitsOnLeftBottom;
std::set<Unit*> Collision::mUnitsOnRightTop;
std::set<Unit*> Collision::mUnitsOnRightBottom;

Collision::Collision(int playerPart, Player& player, std::vector<Unit*> &mUnits)
	:mMovedX(false)
	,mMovedY(false)
	,mMovedLeft(false)
	,mMovedRight(false)
	,mMovedUp(false)
	,mMovedDown(false)
	,mPlayer(&player)
	,mUnits(mUnits)
	,mPlayerPart(playerPart)
{

}

void Collision::collide()
{
	sf::Sprite* playerSprite=mPlayer->getCollisionSprite()[mPlayerPart];
	mResetted=false;

	//Check which sides collide
	for (std::vector<Unit*>::size_type j=0; j<mUnits.size(); j++)
	{
		if (mUnits[j]->getId()!="PlayerPart")
		{
			sf::FloatRect collisionRect;
			if (!mResetted && testCollisions(playerSprite, j, collisionRect))
			{
				testCollidedSides(playerSprite, j, collisionRect);
			}
		}
	}
	//Handle collisions
	for (std::vector<Unit*>::size_type j=0; j<mUnits.size(); j++)
	{
		if (mUnits[j]->getId()!="PlayerPart" && (mPlayer->getId(mPlayerPart)=="PlayerPartFeet" || mPlayer->getId(mPlayerPart)=="PlayerPartBody" || mPlayer->getId(mPlayerPart)=="PlayerPartHead"))
		{
			sf::FloatRect collisionRect;
			if (!mResetted && testCollisions(playerSprite, j, collisionRect))
			{
				//Hit once per collision
				if (!mUnits[j]->wasHit())
				{
					mUnits[j]->setWasHit(true);
					mUnits[j]->setHitThisFrame(true);
				}
				if (mUnits[j]->isHitThisFrame())
				{
					mUnits[j]->hitOnce();
					mUnits[j]->setHitThisFrame(false);
				}

				//Hit every frame during collision
				mUnits[j]->setHit(true);
				mUnits[j]->hit();

				handleCollisions(j, collisionRect);
			}
		}
	}
}

bool Collision::isCollidedSide(int side)
{
	if (mCollidedSides.count(side)==0)
	{
		return false;
	}

	////If the player haven't been moved, return false (bugfix)
	//if (side==LEFT && !mMovedLeft)
	//{
	//	return false;
	//}
	//if (side==RIGHT && !mMovedRight)
	//{
	//	return false;
	//}
	//if (side==TOP && !mMovedDown)
	//{
	//	return false;
	//}
	//if (side==BOTTOM && !mMovedUp)
	//{
	//	return false;
	//}

	return true;
}

void Collision::unitAtSides(const std::vector<Unit*> &mUnits)
{
	for (std::vector<Unit*>::size_type i=0; i<mUnits.size(); i++)
	{
		for (std::vector<Unit*>::size_type j=i+1; j<mUnits.size(); j++)
		{
			sf::FloatRect obj1;
			sf::FloatRect obj2;
			if (mUnits[i]->getSize()==sf::Vector2f(0,0))
			{
				obj1=mUnits[i]->getSprite().getGlobalBounds();
			}
			else
			{
				obj1=sf::FloatRect(mUnits[i]->getPosition(), mUnits[i]->getSize());
			}

			if (mUnits[j]->getSize()==sf::Vector2f(0,0))
			{
				obj2=mUnits[j]->getSprite().getGlobalBounds();
			}
			else
			{
				obj2=sf::FloatRect(mUnits[j]->getPosition(), mUnits[j]->getSize());
			}
			obj1.width+=1;
			obj2.width+=1;

			if (mUnits[i]->isSolid() && mUnits[j]->isSolid() && obj1.intersects(obj2))
			{
				//If the top sides are equal
				if (obj1.top==obj2.top)
				{
					if (obj1.left<obj2.left)
					{
						mUnitsOnTopLeft.insert(mUnits[i]);
						mUnitsOnTopRight.insert(mUnits[j]);
					}
					else
					{
						mUnitsOnTopLeft.insert(mUnits[j]);
						mUnitsOnTopRight.insert(mUnits[i]);
					}
				}
				//If the bottom sides are equal
				if (obj1.top+obj1.height==obj2.top+obj2.height)
				{
					if (obj1.left<obj2.left)
					{
						mUnitsOnBottomLeft.insert(mUnits[i]);
						mUnitsOnBottomRight.insert(mUnits[j]);
					}
					else
					{
						mUnitsOnBottomLeft.insert(mUnits[j]);
						mUnitsOnBottomRight.insert(mUnits[i]);
					}
				}
			}
			obj1.width-=1;
			obj2.width-=1;

			obj1.height+=1;
			obj2.height+=1;
			if (mUnits[i]->isSolid() && mUnits[j]->isSolid() && obj1.intersects(obj2))
			{

				//If the left sides are equal
				if (obj1.left==obj2.left)
				{
					if (obj1.top<obj2.top)
					{
						mUnitsOnLeftBottom.insert(mUnits[i]);
						mUnitsOnLeftTop.insert(mUnits[j]);
					}
					else
					{
						mUnitsOnLeftBottom.insert(mUnits[j]);
						mUnitsOnLeftTop.insert(mUnits[i]);
					}
				}
				//If the right sides are equal
				if (obj1.left+obj1.width==obj2.left+obj2.width)
				{
					if (obj1.top<obj2.top)
					{
						mUnitsOnRightBottom.insert(mUnits[i]);
						mUnitsOnRightTop.insert(mUnits[j]);
					}
					else
					{
						mUnitsOnRightBottom.insert(mUnits[j]);
						mUnitsOnRightTop.insert(mUnits[i]);
					}
				}

				obj1.height-=1;
				obj2.height-=1;
			}
		}
	}
}

bool Collision::testCollisions(sf::Sprite* playerSprite, int unit, sf::FloatRect& collisionRect)
{
	sf::FloatRect rect;
	sf::FloatRect playerRect=playerSprite->getGlobalBounds();
	playerRect.left-=1;
	playerRect.width+=2;
	playerRect.top-=1;
	playerRect.height+=2;

	sf::FloatRect objRect;
	if (mUnits[unit]->getSize()==sf::Vector2f(0,0))
	{
		objRect=mUnits[unit]->getSprite().getGlobalBounds();
		objRect.left+=mUnits[unit]->getOffset().x;
		objRect.top+=mUnits[unit]->getOffset().y;
	}
	else
	{
		objRect=sf::FloatRect(mUnits[unit]->getPosition()+mUnits[unit]->getOffset(), mUnits[unit]->getSize());
	}

	return playerRect.intersects(objRect, collisionRect);
}

void Collision::handleCollisions(int unit, const sf::FloatRect& collisionRect)
{
	sf::Vector2f moveDistance;
	const sf::Sprite* playerSprite=mPlayer->getCollisionSprite()[mPlayerPart];
	if (mUnits[unit]->isSolid())
	{
		//Collision from the above/below
		if (collisionRect.width>collisionRect.height)
		{
			if (!mMovedY)
			{
				//If player is above object
				if (playerSprite->getPosition().y<mUnits[unit]->getPosition().y)
				{
					if (collisionRect.width>Eric::getSpeed()+1.1 || ((mUnitsOnLeftTop.count(mUnits[unit])==0 && !isCollidedSide(RIGHT)) && (mUnitsOnRightTop.count(mUnits[unit])==0 && !isCollidedSide(LEFT))))
					{
						mMovedUp=true;
						moveDistance.y=-(collisionRect.height-1);
						mMovedY=true;
					}
					else
					{
						mCollidedSides.erase(mCollidedSides.find(BOTTOM));
					}
				}
				//If player is below object
				else
				{
					if (collisionRect.width>Eric::getSpeed()+1.1 || ((mUnitsOnLeftBottom.count(mUnits[unit])==0 && !isCollidedSide(RIGHT)) && (mUnitsOnRightBottom.count(mUnits[unit])==0 && !isCollidedSide(LEFT))))
					{
						mMovedDown=true;
						moveDistance.y=collisionRect.height-1;
						mMovedY=true;
					}
					else
					{
						mCollidedSides.erase(mCollidedSides.find(TOP));
					}
				}
			}
		}
		//Collision from the sides
		else
		{
			if (!mMovedX)
			{
				//If player is left of object
				if (playerSprite->getPosition().x<mUnits[unit]->getPosition().x)
				{
					if (collisionRect.height>Eric::getGravity()+1.1 || ((mUnitsOnTopRight.count(mUnits[unit])==0 && !isCollidedSide(BOTTOM)) && (mUnitsOnBottomRight.count(mUnits[unit])==0 && !isCollidedSide(TOP))))
					{
						mMovedLeft=true;
						moveDistance.x=-(collisionRect.width-1);
						mMovedX=true;
					}
					else
					{
						mCollidedSides.erase(mCollidedSides.find(LEFT));
					}

				}
				//If player is right of object
				else
				{
					if (collisionRect.height>Eric::getGravity()+1.1 || ((mUnitsOnTopLeft.count(mUnits[unit])==0 && !isCollidedSide(BOTTOM)) && (mUnitsOnBottomLeft.count(mUnits[unit])==0 && !isCollidedSide(TOP))))
					{
						mMovedRight=true;
						moveDistance.x=collisionRect.width-1;
						mMovedX=true;
					}
					else
					{
						mCollidedSides.erase(mCollidedSides.find(RIGHT));
					}
				}
			}
		}
	}
	//If the feet and body is connected, but head is away
	//std::cout << mPlayer->getCollisionSprite().size() << std::endl;
	if(mPlayerPart!=3){
		mPlayer->forceMove(mPlayerPart, moveDistance);
	}
	//if(mPlayer->getCollisionSprite().size()==3)
	//{
	//	if(mPlayerPart==1)
	//	{
	//		mPlayer->forceMove(2, moveDistance);
	//	}
	//	else if(mPlayerPart==0){
	//		mPlayer->forceMove(5, moveDistance);
	//	}
	//}
	////If the feet, body and head is connected
	//else if(mPlayer->getCollisionSprite().size()==1)
	//{
	//	mPlayer->forceMove(-1, moveDistance);
	//}
	//else
	//{
	//	if(mPlayerPart!=3)
	//	mPlayer->forceMove(mPlayerPart, moveDistance);
	//}
	//playerSprite->setPosition(moveDistance);

	if (mUnits[unit]->getId()=="Lava")
	{
		if (mPlayer->getId(mPlayerPart)!="PlayerPartHead")
		{
			killPlayer();
		}
		else
		{
			mPlayer->shootHead(sf::Vector2f(0,0));
		}
	}
	if(mUnits[unit]->getId()=="Door" && mPlayer->getTogether()==true && mPlayer->getId(mPlayerPart)=="PlayerPartBody")
	{
		mPlayer->win();
		//mPlayer->restartPlayer(sf::Vector2f(64, 384));
	}
	if (mUnits[unit]->getId()=="LaserRed")
	{
		if (mPlayer->getId(mPlayerPart)!="PlayerPartHead")
		{
			killPlayer();
		}
		else
		{
			mPlayer->shootHead(sf::Vector2f(0,0));
		}
	}
	if (mUnits[unit]->getId()=="LaserYellow")
	{
		if (mPlayer->getId(mPlayerPart)=="PlayerPartBody")
		{
			killPlayer();
		}
	}
	if (mUnits[unit]->getId()=="LaserBlue")
	{
		if (mPlayer->getId(mPlayerPart)=="PlayerPartFeet")
		{
			killPlayer();
		}
	}
	if (mUnits[unit]->getId()=="AntiMagnet")
	{
		if (mPlayer->getId(mPlayerPart)=="PlayerPartFeet")
		{
			mPlayer->dropFeet();
		}
		if (mPlayer->getId(mPlayerPart)=="PlayerPartHead")
		{
			mPlayer->shootHead(sf::Vector2f(0,0));
		}
	}
}

void Collision::killPlayer()
{
	mPlayer->restartPlayer();
	mResetted=true;
	for (std::vector<Unit*>::size_type i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->reset();
	}
}

void Collision::testCollidedSides(sf::Sprite* playerSprite, int unit, sf::FloatRect& collisionRect)
{
	if (mUnits[unit]->isSolid())
	{
		//Collision from above/below
		if (collisionRect.width>collisionRect.height)
		{
			//If player is above object
			if (playerSprite->getPosition().y<mUnits[unit]->getPosition().y)
			{
				mCollidedSides.insert(BOTTOM);
			}
			//If player is below object
			else
			{
				mCollidedSides.insert(TOP);
			}
		}
		else
		{
			//If player is left of object
			if (playerSprite->getPosition().x<mUnits[unit]->getPosition().x)
			{
				mCollidedSides.insert(LEFT);
			}
			//If player is right of object
			else
			{
				mCollidedSides.insert(RIGHT);
			}
		}
	}
}