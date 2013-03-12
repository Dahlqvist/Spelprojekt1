#include "UnitManager.h"
#include "Collision.h"
#include <iostream>
#include "DialogueBox.h"

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

UnitManager::~UnitManager()
{
	while (!mUnits.empty() && mUnits.back()!=0x0)
	{
		delete mUnits.back();
		mUnits.pop_back();
	}
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
			if (DialogueBox* tempBox=dynamic_cast<DialogueBox*>(mUnits[i]))
			{
				window.draw(tempBox->getText());
			}
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