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
	Collision();
	void collide(int playerPart, Player& player, const std::vector<Unit*> &objects);
	bool isCollidedSide(int side);
	static void unitAtSides(const std::vector<Unit*> &objects);

	enum sides{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT};

private:
	bool testCollisions(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect);
	void handleCollisions(Player& player, Unit* obj2, const sf::FloatRect& collisionRect);
	void testCollidedSides(sf::Sprite* playerSprite, Unit* obj2, sf::FloatRect& collisionRect);

	std::set<int> mCollidedSides;
	static std::set<Unit*> mUnitsOnTopLeft;
	static std::set<Unit*> mUnitsOnTopRight;
	static std::set<Unit*> mUnitsOnBottomLeft;
	static std::set<Unit*> mUnitsOnBottomRight;

	bool mMovedX, mMovedY;

	int mPlayerPart;
};

#endif