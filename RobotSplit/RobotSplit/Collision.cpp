#include "Collision.h"
#include <iostream>

std::set<Unit*> Collision::mUnitsOnTopLeft;
std::set<Unit*> Collision::mUnitsOnTopRight;
std::set<Unit*> Collision::mUnitsOnBottomLeft;
std::set<Unit*> Collision::mUnitsOnBottomRight;

Collision::Collision()
	:mMovedX(false)
	,mMovedY(false)
{

}

void Collision::collide(int playerPart, Player& player, const std::vector<Unit*> &objects)
{
	mPlayerPart=playerPart;
	sf::Sprite* playerSprite=player.getCollisionSprite()[playerPart];
	for (int j=0; j<objects.size(); j++)
	{
		if (objects[j]->getId()!="PlayerPart")
		{
			sf::FloatRect collisionRect;
			if (testCollisions(playerSprite, objects[j], collisionRect))
			{
				testCollidedSides(playerSprite, objects[j], collisionRect);
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
				if (obj1.top+obj1.height==obj2.top+obj2.height && obj1.left<obj2.left)
				{
					mUnitsOnBottomLeft.insert(objects[i]);
					mUnitsOnBottomRight.insert(objects[j]);
				}
				else
				{
					mUnitsOnBottomLeft.insert(objects[j]);
					mUnitsOnBottomRight.insert(objects[i]);
				}

				obj1.width-=1;
				obj2.width-=1;
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
		//Collision from the sides
		if (collisionRect.width<collisionRect.height)
		{
			if (!mMovedX)
			{
				//If player is left of object
				if (playerSprite->getPosition().x<obj2->getPosition().x)
				{
					double foo=collisionRect.width;
					if (collisionRect.height>10 || (mUnitsOnTopRight.count(obj2)==0 && !isCollidedSide(BOTTOM) || mUnitsOnBottomRight.count(obj2)==0 && !isCollidedSide(TOP)))
					{
						moveDistance.x=-(collisionRect.width-1);
						mCollidedSides.insert(LEFT);
						mMovedX=true;
					}
				}
				//If player is right of object
				else
				{
					if (collisionRect.height>10 || (mUnitsOnTopLeft.count(obj2)==0 && !isCollidedSide(BOTTOM) || mUnitsOnBottomLeft.count(obj2)==0 && !isCollidedSide(TOP)))
					{
						moveDistance.x=collisionRect.width-1;
						mCollidedSides.insert(RIGHT);
						mMovedX=true;
					}
				}
			}
		}
		//Collision from the above/below
		else
		{
			if (!mMovedY)
			{
				mMovedY=true;
				//If player is above object
				if (playerSprite->getPosition().y<obj2->getPosition().y)
				{
					moveDistance.y=-(collisionRect.height-1);
					mCollidedSides.insert(BOTTOM);
				}
				//If player is below object
				else
				{
					moveDistance.y=collisionRect.height-1;
					mCollidedSides.insert(TOP);
				}
			}
		}
	}
	//If the feet and body is connected, but head is away
	if(player.getCollisionSprite().size()==2 && mPlayerPart==1)
	{
		player.forceMove(2, moveDistance);
	}
	//If the feet, body and head is connected
	else if(player.getCollisionSprite().size()==1)
	{
		player.forceMove(3, moveDistance);
	}
	else
	{
		player.forceMove(mPlayerPart, moveDistance);
	}
	//playerSprite->setPosition(moveDistance);
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
	}
}