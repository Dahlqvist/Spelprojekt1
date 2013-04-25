#include	"GameTimer.h"
#include	<assert.h>


GameTimer::GameTimer(float	TimeLimit)
	:mLimit(TimeLimit),mAddTime(0.0f),mPause(false)
{
	mTimer	=	new	sf::Clock();
}

GameTimer::~GameTimer(void)
{
	delete mTimer;
}

void	GameTimer::pause()
{
	mPause=true;
	mAddTime=(mTimer->getElapsedTime().asSeconds()-mAddTime);
}

void	GameTimer::unPause()
{
	mPause=false;
	mAddTime=(mTimer->getElapsedTime().asSeconds()-mAddTime);
}

void	GameTimer::setLimit(float	TimeLimit)
{
	mLimit=TimeLimit;
}

void	GameTimer::reset()
{
	mTimer->restart();
}

bool	GameTimer::getPause()const
{
	return	mPause;
}

bool	GameTimer::isExpired()
{
	if(mTimer->getElapsedTime().asSeconds()>=mLimit+mAddTime&&!mPause)
	{
		mAddTime=0.0f;
		return true;
	}
	return false;
}

float	GameTimer::getCurrentTime()const
{
	if(mPause)
	{
		return	mAddTime;
	}
	return	mTimer->getElapsedTime().asSeconds();
}

float	GameTimer::getLimit()const
{
	return	mLimit;
}