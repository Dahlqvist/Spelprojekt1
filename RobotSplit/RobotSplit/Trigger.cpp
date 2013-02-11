#include "Trigger.h"

Trigger::Trigger(sf::Vector2f position, std::string id, std::string spriteName, std::string triggedObject)
	:Unit(position, id, spriteName)
	,mTriggedObject(triggedObject)
{

}