#include "Level.h"
#include "LevelLoader.h"

//BackgroundWrap Functions
vector<Background*>		BackgroundWrap::getBackground	()const
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

void			BackgroundWrap::setBackground	(vector<Background*> Source)
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
void		BackgroundWrap::deletePointer()
{
	for (vector<Background*>::size_type i=0; i<mBackground.size(); i++)
	{
		if(mBackground[i]==NULL)
		{
			delete mBackground[i];
		}
	}
	mBackground.clear();
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

void	Level::deletePointers()
{
	for(UnitVector::size_type i=0;i<mObjects.size();i++)
	{
		if(mPlayer==NULL)
		{
			delete mObjects[i];
		}
	}
	if(mPlayer==NULL)
	{
		delete mPlayer;
	}
	mObjects.clear();
	mBackground.deletePointer();
}

void	Level::loadNewLevel(string FileName)
{
	LevelLoader	Loader;
	Loader.loadFile(FileName);
	(*this)=Loader.getLevel();
}


void	Level::setObjects(const UnitVector& Source)
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

void	Level::addDialogueBox(DialogueBox* source)
{
	mDialogueBoxes.push_back(source);
}

void	Level::setBackground(vector<Background*> source)
{
	mBackground.setBackground(source);
}

void	Level::operator=(const Level& other)
{
	mObjects=other.getObjects();
	mBackground=other.mBackground;
	mName=other.getName();
	mPlayer=other.getPlayer();
	mDialogueBoxes=other.getDialogueBoxes();
}


std::string		Level::getName		()const
{
	return	mName;
}

UnitVector	Level::getObjects	()const
{
	return	mObjects;
}

vector<Background*>		Level::getBackground()const
{
	return	mBackground.getBackground();
}

Player*			Level::getPlayer	()const
{
	return	mPlayer;
}

vector<DialogueBox*> Level::getDialogueBoxes()const
{
	return mDialogueBoxes;
}

BackgroundWrap&	Level::getBackgroundWrap()
{
	return	mBackground;
}