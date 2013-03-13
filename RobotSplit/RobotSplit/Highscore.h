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
	~Highscore();

	void update();
	void render();
	void input();

	void display();
	
	

	void			insertEntry(HighScoreEntry);

	string			getLevelName()const;
	HighScoreSet	getEntries()const;

private:
	string			mLevelName;
	HighScoreSet	mEntries;
};

#endif