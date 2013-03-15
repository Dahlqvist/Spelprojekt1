#ifndef INC_ROCKETFUEL
#define INC_ROCKETFUEL
#include "Unit.h"
#include "Animation.h"

class RocketFuel:public Unit{
public:
	RocketFuel();
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position; mActiveAnimation->setPosition(mPosition);};

	virtual sf::Sprite getSprite(){return mActiveAnimation->getSprite();};
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){}

	virtual void update();
	virtual void draw(){};
private:
	Animation* mActiveAnimation;
	Animation mRocketFuel;
};

#endif
