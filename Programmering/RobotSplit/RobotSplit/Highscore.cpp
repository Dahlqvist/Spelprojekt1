#include "Highscore.h"


Highscore::Highscore()
{
}

Highscore::Highscore(HighscoreSet	SET,string	LevelName,unsigned int size):
	mLevelName(LevelName),
	mEntries(SET),
	mMaxSize(size)
{
	mLevelName	=	LevelName;
	mEntries	=	SET;
}

Highscore::~Highscore()
{
}

void			Highscore::insertEntry(HighscoreEntry entry)
{
	mEntries.insert(entry);
	if(mEntries.size()>mMaxSize)
	{
		HighscoreSet::iterator	it=mEntries.end();
		it--;
		mEntries.erase(it);
	}
}

string			Highscore::getLevelName()const
{
	return	mLevelName;
}

HighscoreSet	Highscore::getEntries()const
{
	return	mEntries;
}

unsigned int	Highscore::getSize()const
{
	return mMaxSize;
}