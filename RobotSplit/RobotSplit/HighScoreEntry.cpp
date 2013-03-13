#include "HighScoreEntry.h"


HighScoreEntry::HighScoreEntry(string Name,int Time,tm Date)
	:mTimeMilliSecs(Time),mName(Name),mDate(Date)
{
}


HighScoreEntry::~HighScoreEntry(void)
{
}

tm	HighScoreEntry::getDate()const
{
	return	mDate;
}

int	HighScoreEntry::getTime()const
{
	return	mTimeMilliSecs;
}

string	HighScoreEntry::getName()const
{
	return	mName;
}

bool	HighScoreEntry::operator<(const HighScoreEntry&	other)const
{
	bool	ReturnBool=false;
	if(getTime()<other.getTime())
	{
		ReturnBool=true;	
	}
	else if(getTime()==other.getTime())
	{
		if(getDate().tm_year<other.getDate().tm_year)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_mon<other.getDate().tm_mon)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_mday<other.getDate().tm_mday)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_hour<other.getDate().tm_hour)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_min<other.getDate().tm_min)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_sec<other.getDate().tm_sec)
		{
			ReturnBool=true;
		}
		else
		{
			if(getName().compare(other.getName())>0)
			{
				ReturnBool=true;
			}
		}
	}
	return	ReturnBool;
}