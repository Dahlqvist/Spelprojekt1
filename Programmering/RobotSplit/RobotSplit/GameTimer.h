#pragma once
#include	<SFML\System\Clock.hpp>

class GameTimer
{
public:
	GameTimer	(float	TimeLimit=1.0);
	~GameTimer	(void);
	void	reset	();
	void	pause	();
	void	unPause	();
	void	setLimit(float TimeLimit);
	bool	getPause()const;
	float	getLimit()const;
	bool	isExpired	();
	float	getCurrentTime	()const;
private:
	bool		mPause;
	float		mLimit,mAddTime;
	sf::Clock*	mTimer;
};

