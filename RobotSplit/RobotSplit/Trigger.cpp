#include "Trigger.h"

Trigger::Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject)
	:Unit(position, size, offset, id, spriteName, false)
	,mTriggedObject(triggedObject)
{

}

Trigger::Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, Unit* triggedObject)
	:Unit(position, size, offset, id, animation, false)
	,mTriggedObject(triggedObject)
{

}

void Trigger::hit()
{
	mTriggedObject->activate();
}

void Trigger::hitOnce()
{
}

void Trigger::activate()
{
	mTriggedObject->activate();
}

void Trigger::deactivate()
{
	mTriggedObject->deactivate();
}