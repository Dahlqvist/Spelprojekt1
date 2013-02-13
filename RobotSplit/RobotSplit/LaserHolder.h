#ifndef INC_LASERHOLDER
#define INC_LASERHOLDER
#include "Laser.h"

class LaserHolder:public Unit
{
public:
	LaserHolder(Laser*);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position)
	{
		mPosition=position;
		mSprite.setPosition(mPosition);
	};

	virtual sf::Sprite getSprite(){return *mActiveSprite;};

	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.rotate(r);}

	virtual void update(){};
	virtual void draw(){};
	virtual void hit(){};
	virtual void activate(){};

protected:
	sf::Vector2f mSize;
	float mRotation;

	sf::Sprite* mActiveSprite;
	sf::Sprite mOn;
	sf::Sprite mStandby;
	sf::Sprite mOff;

	Animation* mAnimation;

	bool mSolid;
};

#endif