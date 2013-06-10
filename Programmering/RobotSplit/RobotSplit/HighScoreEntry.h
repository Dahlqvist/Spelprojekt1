#ifndef INC_HighscoreEntry
#define INC_HighscoreEntry
#include <string>
#include <time.h>

using namespace std;


class HighscoreEntry
{
public:
	HighscoreEntry(string Name,int Time,tm Date);
	~HighscoreEntry(void);
	void			setName(string);
	string			getName()const;
	tm				getDate()const;
	bool			operator<(const	HighscoreEntry&)const;
	bool			operator>(const	HighscoreEntry&)const;
	unsigned int	getTime()const;
private:
	int		mTimeMilliSecs;
	string	mName;
	tm		mDate;
};


#endif