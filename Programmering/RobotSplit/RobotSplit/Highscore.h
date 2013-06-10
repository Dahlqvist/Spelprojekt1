#ifndef INC_HIGHSCORE
#define INC_HIGHSCORE
#include	<SFML\Graphics\Font.hpp>
#include	<set>
#include	"HighscoreEntry.h"

typedef	std::set<HighscoreEntry>	HighscoreSet;

class Highscore
{
public:
	Highscore();
	Highscore(HighscoreSet	SET,string	LevelName,unsigned int size = 1);
	~Highscore();
	void			insertEntry(HighscoreEntry);
	string			getLevelName()const;
	HighscoreSet	getEntries()const;
	unsigned int	getSize()const;
private:
	string			mLevelName;
	HighscoreSet	mEntries;
	unsigned int	mMaxSize;
};

#endif