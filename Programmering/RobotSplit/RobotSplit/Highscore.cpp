#include "Highscore.h"

Highscore::Highscore()
{}

Highscore::Highscore(HighScoreSet	SET,string	Level):
	mLevelName(Level),
	mEntries(SET)
{}

Highscore::~Highscore()
{}

string	Highscore::getLevelName()const
{
	return	mLevelName;
}

HighScoreSet	Highscore::getEntries()const
{
	return	mEntries;
}



void	Highscore::insertEntry(HighScoreEntry	entry)
{
	mEntries.insert(entry);
}
