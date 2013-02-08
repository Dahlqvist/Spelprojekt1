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

Collision::Collision()
	:mMovedX(false)
	,mMovedY(false)
{

}

void Collision::collide(int playerPart, Player& player, const std::vector<Unit*> &objects)
{
	mPlayerPart=playerPart;
	sf::Sprite* playerSprite=player.getCollisionSprite()[playerPart];
	mResetted=false;
	for (int j=0; j<objects.size(); j++)
	{
		if (objects[j]->getId()!="PlayerPart")
		{
			sf::FloatRect collisionRect;
			if (!mResetted && testCollisions(playerSprite, objects[j], collisionRect))
			{
				//testCollidedSides(playerSprite, objects[j], collisionRect);
				handleCollisions(player, objects[j], collisionRect);
			}
		}
	}
}

bool Collision::isCollidedSide(int side)
{
	return (mCollidedSides.count(side)!=0);
}

void Collision::unitAtSides(const std::vector<Unit*> &objects)
{
	for (int i=0; i<objects.size(); i++)
	{
		for (int j=i+1; j<objects.size(); j++)
		{
			sf::FloatRect obj1=objects[i]->getSprite().getGlobalBounds();
			sf::FloatRect obj2=objects[j]->getSprite().getGlobalBounds();
			obj1.width+=1;
			obj2.width+=1;

			if (objects[i]->isSolid() && objects[j]->isSolid() && obj1.intersects(obj2))
			{
				//If the top sides are equal
				if (obj1.top==obj2.top)
				{
					if (obj1.left<obj2.left)
					{
						mUnitsOnTopLeft.insert(objects[i]);
						mUnitsOnTopRight.insert(objects[j]);
					}
					else
					{
						mUnitsOnTopLeft.insert(objects[j]);
						mUnitsOnTopRight.insert(objects[i]);
					}
				}
				//If the bottom sides are equal
				if (obj1.top+obj1.height==obj2.top+obj2.height)
				{
					if (obj1.left<obj2.left)
					{
						mUnitsOnBottomLeft.insert(objects[i]);
						mUnitsOnBottomRight.insert(objects[j]);
					}
					else
					{
						mUnitsOnBottomLeft.insert(objects[j]);
						mUnitsOnBottomRight.insert(objects[i]);
					}
				}
			}
			obj1.width-=1;
			obj2.width-=1;

			obj1.height+=1;
			obj2.height+=1;
			if (objects[i]->isSolid() && objects[j]->isSolid() && obj1.intersects(obj2))
			{

				//If the left sides are equal
				if (obj1.left==obj2.left)
				{
					if (obj1.top<obj2.top)
					{
						mUnitsOnLeftBottom.insert(objects[i]);
						mUnitsOnLeftTop.insert(objects[j]);
					}
					else
					{
						mUnitsOnLeftBottom.insert(objects[j]);
						mUnitsOnLeftTop.insert(objects[i]);
					}
				}
				//If the right sides are equal
				if (obj1.left+obj1.width==obj2.left+obj2.width)
				{
					if (obj1.top<obj2.top)
					{
						mUnitsOnRightBottom.insert(objects[i]);
						mUnitsOnRightTop.insert(objects[j]);
					}
					else
					{
						mUnitsOnRightBottom.insert(objects[j]);
						mUnitsOnRightTop.insert(objects[i]);
					}
				}

				obj1.height-=1;
				obj2.height-=1;
			}
		}
	}
}

bool Collision::testCollisions(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect)
{
	sf::FloatRect rect;
	sf::FloatRect playerRect=playerSprite->getGlobalBounds();
	playerRect.left-=1;
	playerRect.width+=2;
	playerRect.top-=1;
	playerRect.height+=2;
	sf::FloatRect objRect=obj2->getSprite().getGlobalBounds();

	return playerRect.intersects(objRect, collisionRect);
}

void Collision::handleCollisions(Player& player, Unit* obj2, const sf::FloatRect& collisionRect)
{
	sf::Vector2f moveDistance;
	const sf::Sprite* playerSprite=player.getCollisionSprite()[mPlayerPart];
	if (obj2->isSolid())
	{
		//Collision from the above/below
		if (collisionRect.width>collisionRect.height)
		{
			if (!mMovedY)
			{
				//If player is above object
				if (playerSprite->getPosition().y<obj2->getPosition().y)
				{
					if (collisionRect.width>5 || (mUnitsOnLeftTop.count(obj2)==0 && !isCollidedSide(RIGHT) || mUnitsOnRightTop.count(obj2)==0 && !isCollidedSide(LEFT)))
					{
						moveDistance.y=-(collisionRect.height-1);
						mCollidedSides.insert(BOTTOM);
						mMovedY=true;
					}
				}
				//If player is below object
				else
				{
					if (collisionRect.width>5 || (mUnitsOnLeftBottom.count(obj2)==0 && !isCollidedSide(RIGHT) || mUnitsOnRightBottom.count(obj2)==0 && !isCollidedSide(LEFT)))
					{
						moveDistance.y=collisionRect.height-1;
						mCollidedSides.insert(TOP);
						mMovedY=true;
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
				if (playerSprite->getPosition().x<obj2->getPosition().x)
				{
					if (collisionRect.height>5 || (mUnitsOnTopRight.count(obj2)==0 && !isCollidedSide(BOTTOM) || mUnitsOnBottomRight.count(obj2)==0 && !isCollidedSide(TOP)))
					{
						moveDistance.x=-(collisionRect.width-1);
						mCollidedSides.insert(LEFT);
						mMovedX=true;
					}
				}
				//If player is right of object
				else
				{
					if (collisionRect.height>5 || (mUnitsOnTopLeft.count(obj2)==0 && !isCollidedSide(BOTTOM) || mUnitsOnBottomLeft.count(obj2)==0 && !isCollidedSide(TOP)))
					{
						moveDistance.x=collisionRect.width-1;
						mCollidedSides.insert(RIGHT);
						mMovedX=true;
					}
				}
			}
		}
	}
	//If the feet and body is connected, but head is away
	//std::cout << player.getCollisionSprite().size() << std::endl;
	if(player.getCollisionSprite().size()==3)
	{
		if(mPlayerPart==1)
		{
			player.forceMove(2, moveDistance);
		}
		else if(mPlayerPart==0){
			player.forceMove(mPlayerPart, moveDistance);
		}
	}
	//If the feet, body and head is connected
	else if(player.getCollisionSprite().size()==1)
	{
		player.forceMove(-1, moveDistance);
	}
	else
	{
		if(mPlayerPart!=3)
		player.forceMove(mPlayerPart, moveDistance);
	}
	//playerSprite->setPosition(moveDistance);

	if (obj2->getId()=="Lava")
	{
		player.restartPlayer(sf::Vector2f(100, 100));
		mResetted=true;
	}
}

void Collision::testCollidedSides(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect)
{
	if (obj2->isSolid())
	{
		//Collision from above/below
		if (collisionRect.width>collisionRect.height)
		{
			//If player is above object
			if (playerSprite->getPosition().y<obj2->getPosition().y)
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
			if (playerSprite->getPosition().x<obj2->getPosition().x)
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