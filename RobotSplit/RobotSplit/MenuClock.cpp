#include "MenuClock.h"

sf::Clock MenuClock::mClock;

MenuClock::MenuClock()
{}

MenuClock::~MenuClock()
{}

MenuClock& MenuClock::getInstance()
{
	MenuClock menuclock;
	return menuclock;
}

sf::Clock& MenuClock::getClock()
{
	return mClock;
}

void MenuClock::restartClock()
{
	mClock.restart();
}