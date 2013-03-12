#ifndef INC_TRIGGER
#define INC_TRIGGER

#include "Unit.h"

class Trigger: public Unit
{
public:
	Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject, std::string triggerSound);
	Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, Unit* triggedObject, std::string triggerSound);

	void setTarget(Unit* target);
	std::string	getSound();
	std::string	getTargetId();
	virtual void hit();
	virtual void hitOnce();
	virtual void activate();
	virtual void deactivate();
	
	virtual void setSound(std::string SoundName);
protected:
	friend class Toolbar;
	Unit* mTriggedObject;
	std::string mSound;
};

#endif