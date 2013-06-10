#include "HighscoreEntry.h"


HighscoreEntry::HighscoreEntry(string Name,int Time,tm Date)
	:mTimeMilliSecs(Time),mName(Name),mDate(Date)
{
}


HighscoreEntry::~HighscoreEntry(void)
{
}

tm	HighscoreEntry::getDate()const
{
	return	mDate;
}

unsigned int	HighscoreEntry::getTime()const
{
	return	mTimeMilliSecs;
}

string	HighscoreEntry::getName()const
{
	return	mName;
}

bool	HighscoreEntry::operator<(const HighscoreEntry&	other)const
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
		else if(getDate().tm_mon<other.getDate().tm_mon&&getDate().tm_year==other.getDate().tm_year)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_mday<other.getDate().tm_mday&&getDate().tm_mon==other.getDate().tm_mon)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_hour<other.getDate().tm_hour&&getDate().tm_mday==other.getDate().tm_mday)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_min<other.getDate().tm_min&&getDate().tm_hour==other.getDate().tm_hour)
		{
			ReturnBool=true;
		}
		else if(getDate().tm_sec<other.getDate().tm_sec&&getDate().tm_min==other.getDate().tm_min)
		{
			ReturnBool=true;
		}
		else
		{
			if(getName().compare(other.getName())<0&&getDate().tm_sec==other.getDate().tm_sec)
			{
				ReturnBool=true;
			}
		}
	}
	return	ReturnBool;
}


bool	HighscoreEntry::operator>(const	HighscoreEntry& other)const
{
	return other<(*this);
}

void	HighscoreEntry::setName(string	name)
{
	mName	=	name;
}