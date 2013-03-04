#ifndef INC_CHECKPOINT
#define INC_CHECKPOINT

#include "Unit.h"

class Checkpoint: public Unit
{
public:
	Checkpoint(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string spriteOn, std::string spriteOff);

	void activate();
	void deactivate();

private:
	sf::Sprite mSpriteOn, mSpriteOff;
	bool mActive;
	friend	class	XmlSaver;
};

#endif