#ifndef INC_HIGHSCORE
#define INC_HIGHSCORE
#include	<set>
#include	"HighScoreEntry.h"

typedef	set<HighScoreEntry>	HighScoreSet;

class Highscore
{
public:
	Highscore();
	Highscore(HighScoreSet	SET,string	LevelName);
	void			insertEntry(HighScoreEntry);
	string			getLevelName()const;
	HighScoreSet	getEntries()const;
private:
	string			mLevelName;
	HighScoreSet	mEntries;
};

#endif