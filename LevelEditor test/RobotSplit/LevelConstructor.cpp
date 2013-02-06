#include "LevelConstructor.h"
#include "Player.h"
#include "Platform.h"
#include "Unit.h"
using namespace sf;

LevelConstructor::LevelConstructor(void)
	:mPlayerExist(false)
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

void	LevelConstructor::deleteItem(int place)
{
	UnitVector::iterator	it=mObjects.begin()+place;
	delete	(*it);
	mObjects.erase(it);
}

void	LevelConstructor::addPlayer(Vector2f	Pos)
{
	delete mPlayer;
	mPlayer =new Player(Pos);
	mPlayerExist=true;
}

void	LevelConstructor::addPlatform(Vector2f	Pos,std::string sprite,int life)
{
	if(life!=0)
	{
		mObjects.push_back(new Platform(life,Pos,sprite));
	}
	else
	{
		mObjects.push_back(new Platform(Pos,sprite));
	}
}

void	LevelConstructor::addUnit(Vector2f	Pos,std::string	Id,std::string Sprite,bool Solid)
{
	mObjects.push_back(new Unit(Pos,Id,Sprite,Solid));
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