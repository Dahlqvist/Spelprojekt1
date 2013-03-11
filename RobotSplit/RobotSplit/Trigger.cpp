#include "Trigger.h"
#include "Sound.h"

Trigger::Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, Unit* triggedObject, std::string triggerSound)
	:Unit(position, size, offset, id, spriteName, false)
	,mTriggedObject(triggedObject)
	,mSound(triggerSound)
{

}

Trigger::Trigger(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, Unit* triggedObject, std::string triggerSound)
	:Unit(position, size, offset, id, animation, false)
	,mTriggedObject(triggedObject)
	,mSound(triggerSound)
{

}

void Trigger::hit()
{
	mTriggedObject->activate();
}

void Trigger::hitOnce()
{
	activate();
}

void Trigger::activate()
{
	mTriggedObject->activate();
	Sound::playSound(mSound);
}

void Trigger::deactivate()
{
	mTriggedObject->deactivate();
}
