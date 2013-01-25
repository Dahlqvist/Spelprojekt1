#include "Level.h"
#include "LevelLoader.h"

//BackgroundWrap Functions
Background*		BackgroundWrap::getBackground	()const
{
	return	mBackground;
}

string			BackgroundWrap::getName			()const
{
	return	mName;
}

int				BackgroundWrap::getFrames		()const
{
	return	mFrames;
}

int				BackgroundWrap::getSpeed		()const
{
	return	mSpeed;
}

void			BackgroundWrap::setBackground	(Background* Source)
{
	mBackground=Source;
}

void			BackgroundWrap::setName			(const string& NewName)
{
	mName.empty();
	mName=NewName;
}

void			BackgroundWrap::setFrames		(const int& Source)
{
	mFrames=Source;
}

void			BackgroundWrap::setSpeed		(const int& Source)
{
	mSpeed=Source;
}

void			BackgroundWrap::operator=		(const BackgroundWrap& Source)
{
	setName(Source.getName());
	setBackground(Source.getBackground());
	setFrames(Source.getFrames());
	setSpeed(Source.getSpeed());
}

//Level Functions
Level::Level(void)
{
}

Level::Level(string	FileName)
{
	loadNewLevel(FileName);
}

Level::~Level(void)
{
}


void	Level::loadNewLevel(string FileName)
{
	LevelLoader	Loader;
	Loader.loadFile(FileName);
	(*this)=Loader.getLevel();
}


void	Level::setObjects(const ObjectVector& Source)
{
	mObjects=Source;
}

void	Level::setName(const string& NewName)
{
	mName=NewName;
}

void	Level::setPlayer(Player* source)
{
	mPlayer	=	source;
}

void	Level::setBackground(Background* source)
{
	mBackground.setBackground(source);
}

void	Level::operator=(const Level& other)
{
	mObjects=other.getObjects();
	mBackground=other.mBackground;
	mName=other.getName();
	mPlayer=other.getPlayer();
}


std::string		Level::getName		()const
{
	return	mName;
}

ObjectVector	Level::getObjects	()const
{
	return	mObjects;
}

Background*		Level::getBackground()const
{
	return	mBackground.getBackground();
}

Player*			Level::getPlayer	()const
{
	return	mPlayer;
}

BackgroundWrap&	Level::getBackgroundWrap()
{
	return	mBackground;
}