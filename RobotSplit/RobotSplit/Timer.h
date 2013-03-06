#ifndef INC_TIMER
#define INC_TIMER

#include <SFML/System/Clock.hpp>
#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>

class Timer
{
public:
	//static Timer& getInstance();
	Timer();
	~Timer();
	static sf::Clock& getClock();
	static void restartClock();
	static void input();
	static bool getStatus();
	static void changeStatus();
	static void start();
	static void stop();
	static void pause();
	
	void update();
	void render();
	

private:
	/*Timer();
	~Timer();
	Timer(const Timer& timer);
	Timer operator=(const Timer& timer);*/
	
	static void initialize();
	void load();
	void updateNumbers(int q);
	void setDot();
	void setColon();
	sf::Vector2f timerPos;
	
	//static float getSaveTime();
	static int mTimeSave;

	static sf::Clock mClock;
	
	sf::Sprite mDot;
	sf::Sprite mColon;
	Animation mFrame;

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

	static bool mShow;
	static bool mRun;


};

#endif