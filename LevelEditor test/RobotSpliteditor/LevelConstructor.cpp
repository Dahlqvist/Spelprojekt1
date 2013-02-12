#include "LevelConstructor.h"
#include "Player.h"
#include "Platform.h"
#include "Unit.h"
using namespace sf;

LevelConstructor::LevelConstructor(void)
	:Level(),mPlayerExist(false)
{
}

LevelConstructor::LevelConstructor(const Level& Source)
	:Level(Source),mPlayerExist(false)
{
	if(mPlayer!=nullptr)
	{
		mPlayerExist=true;
	}
}

LevelConstructor::LevelConstructor(const string& Source)
	:Level(Source),mPlayerExist(true)
{
}

LevelConstructor::~LevelConstructor(void)
{
}

void	LevelConstructor::deleteItem(Unit*	Source)
{
	UnitVector::iterator it=mObjects.begin();
	int i=0;
	while((*it)!=Source&&it+1!=mObjects.end())
	{
		i++;
		it++;
	}
	if(*it==Source)
	{
		mObjects.erase(it);
	}
	delete	Source;
}

void	LevelConstructor::addPlayer(Player*	Source)
{
	if(mPlayerExist)
	{
		delete mPlayer;
	}
	mPlayer		=Source;
	mPlayerExist=true;
}


void	LevelConstructor::addUnit(Unit*		Source)
{
	mObjects.push_back(Source);
}

UnitVector&	LevelConstructor::accessObjects()
{
	return mObjects;
}

Level		LevelConstructor::getLevel()
{
	return	*this;
}

void		LevelConstructor::deletePlayer()
{
	if(mPlayerExist)
	{
		delete	mPlayer;
		mPlayerExist=false;
	}
}

bool&		LevelConstructor::ifPlayerExist()
{
	return	mPlayerExist;
}