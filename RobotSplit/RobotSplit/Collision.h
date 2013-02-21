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
	Collision(int playerPart, Player& player, std::vector<Unit*> &objects);
	void collide();
	bool isCollidedSide(int side);
	static void unitAtSides(const std::vector<Unit*> &objects);

	enum sides{
		MIN_VALUE_SIDES,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		MAX_VALUE_SIDES};

private:
	bool testCollisions(sf::Sprite* playerSprite, int unit, sf::FloatRect& collisionRect);
	void handleCollisions(int unit, const sf::FloatRect& collisionRect);
	void testCollidedSides(sf::Sprite* playerSprite, int unit, sf::FloatRect& collisionRect);
	void killPlayer();

	std::set<int> mCollidedSides;
	//Objects at the sides
	static std::set<Unit*> mUnitsOnTopLeft;
	static std::set<Unit*> mUnitsOnTopRight;
	static std::set<Unit*> mUnitsOnBottomLeft;
	static std::set<Unit*> mUnitsOnBottomRight;

	//Objects on top/bottom
	static std::set<Unit*> mUnitsOnLeftTop;
	static std::set<Unit*> mUnitsOnLeftBottom;
	static std::set<Unit*> mUnitsOnRightTop;
	static std::set<Unit*> mUnitsOnRightBottom;

	bool mMovedX, mMovedY;
	bool mResetted;
	bool mMovedLeft, mMovedRight, mMovedUp, mMovedDown;

	int mPlayerPart;

	Player* mPlayer;
	std::vector<Unit*> &mUnits;
};

#endif