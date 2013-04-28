#include "RocketFuel.h"

RocketFuel::RocketFuel():
	Unit(sf::Vector2f(100, 100), "RocketFuel", "RocketFuel"),
	mRocketFuel("StixRocketFuel", 100, 4)
{
	mActiveAnimation=&mRocketFuel;
}

void RocketFuel::update()
{
	mActiveAnimation->update();
}