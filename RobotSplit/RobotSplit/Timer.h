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
	static void input();
	static void initialize();
	virtual void update();
	virtual void render();
	void load();

private:
	Timer();
	~Timer();
	Timer(const Timer& timer);
	Timer operator=(const Timer& timer);
	

	static sf::Clock mClock;
	static sf::Clock mSecondClock;
	//Animation mNumbers;
	static Animation* mNumbers;
	static int mDec;
	static int mSek;
	static int mMin;
	static int mHour;

	static int m1Sek;
	static int m10Sek;
	static int m1Min;
	static int m10Min;
	static int m1Hour;
	static int m10Hour;


};

#endif