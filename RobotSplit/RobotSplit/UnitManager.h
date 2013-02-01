#ifndef INC_UNITMANAGER
#define INC_UNITMANAGER

#include <vector>
#include "Unit.h"
#include "Player.h"
#include <map>

class UnitManager
{
public:
	UnitManager(Player* player);
	UnitManager(Player* player, std::vector<Unit*> units);

	void addUnit(Unit* unit);

	std::vector<Unit*> &getUnits(){return mUnits;};
	Player* getPlayer(){return mPlayer;};

	void update();
	void draw(sf::RenderWindow& window);

private:
	typedef std::vector<Unit*> unitVector;
	unitVector mUnits;
	Player* mPlayer;
	std::map<int, int> mCollidedSides;
};

#endif