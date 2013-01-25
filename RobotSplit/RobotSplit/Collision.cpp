#include "Collision.h"

void Collision::collide(sf::Sprite* playerSprite, std::vector<Unit*> objects)
{
	//Check if two objects are on top of eachother (bugfix)
	for (int i=0; i<objects.size(); i++)
	{
		for (int j=i+1; j<objects.size(); j++)
		{
			sf::FloatRect obj1=objects[i]->getSprite().getGlobalBounds();
			sf::FloatRect obj2=objects[j]->getSprite().getGlobalBounds();
			obj1.height+=1;
			obj2.height+=1;
			if (obj1.intersects(obj2) && objects[i]->isSolid() && objects[j]->isSolid())
			{
				obj1.height-=1;
				obj2.height-=1;

				//If the left sides are equal
				if (obj1.left==obj2.left)
				{
					//If obj1 is below obj2
					if (obj1.top>obj2.top)
					{
						mUnitsOnTopLeft.insert(objects[j]);
					}
					//If obj2 is above obj1
					else
					{
						mUnitsOnTopLeft.insert(objects[i]);
					}
				}
				//If the right sides are equal
				if (obj1.left+obj1.width==obj2.left+obj2.width)
				{
					//If obj1 is above obj2
					if (obj1.top>obj2.top)
					{
						mUnitsOnTopRight.insert(objects[j]);
					}
					//If obj2 is above obj1
					else
					{
						mUnitsOnTopRight.insert(objects[i]);
					}
				}
			}
		}
	}

	for (int j=0; j<objects.size(); j++)
	{
		if (objects[j]->getId()!="PlayerPart")
		{
			sf::FloatRect collisionRect;
			if (testCollisions(playerSprite, objects[j], collisionRect))
			{
				testCollidedSides(playerSprite, objects[j], collisionRect);
				handleCollisions(playerSprite, objects[j], collisionRect);
			}
		}
	}
}

bool Collision::isCollidedSide(int side)
{
	return (mCollidedSides.count(side)!=0);
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

void Collision::handleCollisions(sf::Sprite* playerSprite, Unit* obj2, const sf::FloatRect& collisionRect)
{
	sf::Vector2f moveDistance;
	if (obj2->isSolid())
	{
		//Collision from the side
		if (collisionRect.width<collisionRect.height)
		{
			//If player is left of object
			if (playerSprite->getPosition().x<obj2->getPosition().x)
			{
				moveDistance=-sf::Vector2f(collisionRect.width-1, 0);
			}
			//If player is right of object
			else
			{
				moveDistance=sf::Vector2f(collisionRect.width-1, 0);
			}
		}
		//Collision from above/below
		else
		{
			//If player is above object
			if (playerSprite->getPosition().y<obj2->getPosition().y)
			{
				int foo=mUnitsOnTopLeft.count(obj2);
				int foo2=mUnitsOnTopRight.count(obj2);
				bool foo3=isCollidedSide(RIGHT);
				bool foo4=isCollidedSide(LEFT);
				if (mUnitsOnTopLeft.count(obj2)==0 && !isCollidedSide(RIGHT) || mUnitsOnTopRight.count(obj2)==0 && !isCollidedSide(LEFT))
				{
					moveDistance=-sf::Vector2f(0, collisionRect.height-1);
					mCollidedSides.insert(BOTTOM);
				}
			}
			//If player is below object
			else
			{
				moveDistance=sf::Vector2f(0, collisionRect.height-1);
				mCollidedSides.insert(TOP);
			}
		}
	}

	//playerSprite->setPosition(moveDistance);
}

void Collision::testCollidedSides(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect)
{
	if (obj2->isSolid())
	{
		//Collision from the side
		if (collisionRect.width<collisionRect.height)
		{
			//If player is left of object
			if (playerSprite->getPosition().x<obj2->getPosition().x)
			{
				mCollidedSides.insert(RIGHT);
			}
			//If player is right of object
			else
			{
				mCollidedSides.insert(LEFT);
			}
		}
	}
}