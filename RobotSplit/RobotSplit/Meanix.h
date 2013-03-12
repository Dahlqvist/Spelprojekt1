#ifndef INC_MEANIX
#define INC_MEANIX
#include "Unit.h"
#include "Player.h"



class Meanix:public Unit
{
public:
	Meanix(sf::Vector2f, Player*);
	void update();
	void facingStix();

	sf::Sprite getSprite(){return mAni->getSprite();};
private:
	Animation* mAni;
	Animation mRight;
	Animation mLeft;
	Player* mPlayer;
	bool mFacingRight;
	float move;
};


#endif