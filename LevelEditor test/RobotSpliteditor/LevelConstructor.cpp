#include "LevelConstructor.h"
#include "Player.h"
#include "Platform.h"
#include "Unit.h"
#include "Background.h"
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

void		LevelConstructor::setNewName(const string& NEW)
{
	setName(NEW);	
}

sf::Vector2f	LevelConstructor::getSize()
{
	sf::Vector2f Size(0,0);
	for(vector<int>::size_type i=0;i<mBackground.getBackground().size();i++)
	{
		Size.x+=mBackground.getBackground()[i]->draw().getGlobalBounds().width;
	//	Size.y+=mBackground.getBackground()[i]->draw().getGlobalBounds().height;
	}
	return	Size;
}

void	LevelConstructor::setBackground(const std::string&	source)
{
	mBackground.setBackground(TextureManager::getBackground(source));
}