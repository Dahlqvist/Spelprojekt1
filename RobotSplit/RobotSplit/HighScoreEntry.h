#ifndef INC_HIGHSCOREENTRY
#define INC_HIGHSCOREENTRY
#include <string>
#include <time.h>

using namespace std;


class HighScoreEntry
{
public:
	HighScoreEntry(string Name,int Time,tm Date);
	~HighScoreEntry(void);
	string	getName()const;
	int		getTime()const;
	tm		getDate()const;
	bool	operator<(const	HighScoreEntry&)const;
	bool	operator>(const	HighScoreEntry&)const;
private:
	int		mTimeMilliSecs;
	string	mName;
	tm		mDate;
};


#endif