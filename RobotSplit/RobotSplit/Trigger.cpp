#include "Trigger.h"

Trigger::Trigger(sf::Vector2f position, std::string id, std::string spriteName, Unit* triggedObject)
	:Unit(position, id, spriteName, false)
	,mTriggedObject(triggedObject)
{

}

void Trigger::hit()
{
	mTriggedObject->activate();
}