#include "UnitManager.h"
#include "Collision.h"

UnitManager::UnitManager(Player* player)
	:mPlayer(player)
{

}

UnitManager::UnitManager(Player* player, std::vector<Unit*> units)
	:mPlayer(player)
	,mUnits(units)
{
	Collision::unitAtSides(units);
}

void UnitManager::addUnit(Unit* unit)
{
	mUnits.push_back(unit);
}

void UnitManager::update()
{
	for (unitVector::size_type i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->update();
	}

	Collision col[3];
	for (int i=0; i<mPlayer->getCollisionSprite().size() && i<3; i++)
	{
		col[i].collide(i, *mPlayer, mUnits);
	}
}

void UnitManager::draw(sf::RenderWindow& window)
{
	for (unitVector::size_type i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->draw();
		window.draw(mUnits[i]->getSprite());
	}
}