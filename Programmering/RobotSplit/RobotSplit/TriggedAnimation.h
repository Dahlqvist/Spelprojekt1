#ifndef INC_TRIGGEDANIMATION
#define INC_TRIGGEDANIMATION

#include "Unit.h"

class TriggedAnimation: public Unit
{
public:
	TriggedAnimation(sf::Vector2f position, std::string id, std::string spriteName, int speed, int frames);

	virtual void activate();
	virtual void draw();

private:
	bool mActivated;
	bool mDeactivated;
};

#endif