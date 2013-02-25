#ifndef INC_UNITMANAGER
#define INC_UNITMANAGER

#include <vector>
#include "Unit.h"
#include "Player.h"

struct SidePair
{
	SidePair(int playerPart, int side):mPlayerPart(playerPart), mSide(side){};
	int mPlayerPart, mSide;
	bool isPair(int playerPart, int side){return playerPart==mPlayerPart && side==mSide;};
};

class UnitManager
{
public:
	UnitManager(Player* player);
	UnitManager(Player* player, std::vector<Unit*> units);

	void addUnit(Unit* unit);

	std::vector<Unit*> &getUnits(){return mUnits;};
	Player* getPlayer(){return mPlayer;};

	static bool isCollidedSide(int playerPart, int side);

	void update();
	void collide();
	void draw(sf::RenderWindow& window);
	void reset();

private:
	typedef std::vector<Unit*> unitVector;
	unitVector mUnits;
	Player* mPlayer;
	static std::vector<SidePair> mSidePairs;
};

#endif