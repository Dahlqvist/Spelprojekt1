#ifndef INC_COLLISION
#define INC_COLLISION

#include <vector>
#include <set>
#include <map>
#include "GameObject.h"
#include "Player.h"
#include "Unit.h"

class Collision
{
public:
	void collide(sf::Sprite* playerSprite, std::vector<Unit*> objects);
	bool isCollidedSide(int side);

	enum sides{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT};

private:
	bool testCollisions(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect);
	void handleCollisions(sf::Sprite* playerSprite, Unit* obj2, const sf::FloatRect& collisionRect);
	void testCollidedSides(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect);

	std::set<int> mCollidedSides;
	std::set<Unit*> mUnitsOnTopLeft;
	std::set<Unit*> mUnitsOnTopRight;
};

#endif