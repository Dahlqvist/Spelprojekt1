#include "Trigger.h"

Trigger::Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject)
	:Unit(position, size, offset, id, spriteName, false)
	,mTriggedObject(triggedObject)
{

}

void Trigger::hit()
{
	
}

void Trigger::hitOnce()
{
	activate();
}

void Trigger::activate()
{
	mTriggedObject->activate();
}

void Trigger::deactivate()
{
	mTriggedObject->deactivate();
}