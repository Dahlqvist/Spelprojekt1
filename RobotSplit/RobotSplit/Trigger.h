#ifndef INC_TRIGGER
#define INC_TRIGGER

#include "Unit.h"

class Trigger: public Unit
{
public:
	Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject, std::string triggerSound);
	Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, Unit* triggedObject, std::string triggerSound);

	void setTarget(Unit* target){mTriggedObject=target;}
	std::string	getSound(){return mSound;}
	std::string	getTargetId(){return mTriggedObject->getId();}
	virtual void hit();
	virtual void hitOnce();
	virtual void activate();
	virtual void deactivate();
protected:
	Unit* mTriggedObject;
	std::string mSound;
};

#endif