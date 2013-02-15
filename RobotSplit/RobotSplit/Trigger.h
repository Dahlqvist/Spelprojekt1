#ifndef INC_TRIGGER
#define INC_TRIGGER

#include "Unit.h"

class Trigger: public Unit
{
public:
	//Constuctor not final!
	Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject);

	void setTarget(Unit* target){mTriggedObject=target;};

	virtual void hit();
	virtual void hitOnce();
	virtual void activate();
	virtual void deactivate();
private:
	Unit* mTriggedObject;
};

#endif