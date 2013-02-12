#ifndef INC_TRIGGER
#define INC_TRIGGER

#include "Unit.h"

class Trigger: public Unit
{
public:
	//Constuctor not final!
	Trigger(sf::Vector2f position, std::string id, std::string spriteName, Unit* triggedObject);

	void setTarget(Unit* target){mTriggedObject=target;};

	void hit();
	void activate();
private:
	Unit* mTriggedObject;
};

#endif