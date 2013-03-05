#include "UnitManager.h"
#include "Collision.h"
#include <iostream>

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
		if (playerPart==4 && side==4)
		{
			int foo=0;
		}
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
}

void UnitManager::collide()
{
	mSidePairs.clear();
	Collision::resetCheckpointCollision();
	for (int i=0; i<mPlayer->getCollisionSprite().size(); i++)
	{
		Collision col(i, *mPlayer, mUnits);
		col.collide();
		for (int j=Collision::MIN_VALUE_SIDES+1; j<4+Collision::MIN_VALUE_SIDES+1; j++)
		{
			if (col.isCollidedSide(j))
			{
				mSidePairs.push_back(SidePair(i, j));
			}
		}
	}
}

void UnitManager::draw(sf::RenderWindow& window, bool inFrontOf)
{
	for (unitVector::size_type i=0; i<mUnits.size(); i++)
	{
		if (mUnits[i]->isBehind()==inFrontOf)
		{
			mUnits[i]->draw();
			window.draw(mUnits[i]->getSprite());
		}
	}
}

void UnitManager::reset()
{
	for (unitVector::size_type i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->reset();
	}
}