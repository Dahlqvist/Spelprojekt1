#ifndef INC_CHECKPOINT
#define INC_CHECKPOINT

#include "Unit.h"

class Checkpoint: public Unit
{
public:
	Checkpoint(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, Animation* animation);

	void setCurrentFrame(int frame);

	void update();
	void draw();
	void activate();
	void deactivate();

private:
	bool mActive;
};

#endif