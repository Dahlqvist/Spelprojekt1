#ifndef INC_TIMER
#define INC_TIMER

#include <SFML/System/Clock.hpp>
#include "Animation.h"

class Timer
{
public:
	static Timer& getInstance();
	static sf::Clock& getClock();
	static void restartClock();
	static void update();
	static void render();
	static void input();

private:
	Timer();
	Timer(const Timer& Timer);
	Timer operator=(const Timer& Timer);
	~Timer();

	static sf::Clock mClock;
	static sf::Clock mSecondClock;
	Animation mNumbers;
	static Animation* currentNr;
	static int mDec;
	static int mSek;
	static int mMin;
	static int mHour;


};

#endif