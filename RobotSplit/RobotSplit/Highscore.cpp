#include "Highscore.h"

string	Highscore::getLevelName()const
{
	return	mLevelName;
}

HighScoreSet	Highscore::getEntries()const
{
	return	mEntries;
}

Highscore::Highscore()
{
}
Highscore::Highscore(HighScoreSet	SET,string	Level)
	:mLevelName(Level),mEntries(SET)
{
}

void	Highscore::insertEntry(HighScoreEntry	entry)
{
	mEntries.insert(entry);
}