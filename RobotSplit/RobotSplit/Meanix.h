#ifndef INC_MEANIX
#define INC_MEANIX
#include "Unit.h"

class Meanix:public Unit
{
public:
	Meanix(sf::Vector2f);
	void update(){mAnimation->update();};

	sf::Sprite getSprite(){return mAnimation->getSprite();};
};


#endif