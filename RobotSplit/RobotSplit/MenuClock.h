#ifndef INC_MENUCLOCK
#define INC_MENUCLOCK

#include <SFML/System/Clock.hpp>

class MenuClock
{
public:
	static MenuClock& getInstance();
	static sf::Clock& getClock();
	static void restartClock();

private:
	MenuClock();
	MenuClock(const MenuClock& Menuclock);
	MenuClock operator=(const MenuClock& Menuclock);
	~MenuClock();

	static sf::Clock mClock;

};

#endif