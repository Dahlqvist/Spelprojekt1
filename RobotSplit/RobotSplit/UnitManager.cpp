#include "UnitManager.h"
#include "Collision.h"

std::vector<SidePair> UnitManager::mSidePairs;

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

bool UnitManager::isCollidedSide(int playerPart, int side)
{
	for (std::vector<SidePair>::size_type i=0; i<mSidePairs.size(); i++)
	{
		if (mSidePairs[i].isPair(playerPart, side))
			return true;
	}
	return false;
}

void UnitManager::update()
{
	for (unitVector::size_type i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->update();
	}

	mSidePairs.clear();
	Collision col[4];
	for (int i=0; i<mPlayer->getCollisionSprite().size(); i++)
	{
		int foo=mPlayer->getCollisionSprite().size();
		col[i].collide(i, *mPlayer, mUnits);
		for (int j=Collision::MIN_VALUE_SIDES+1; j<4+Collision::MIN_VALUE_SIDES+1; j++)
		{
			if (col[i].isCollidedSide(j))
			{
				mSidePairs.push_back(SidePair(i, j));
			}
		}
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