#ifndef INC_LASERHOLDER
#define INC_LASERHOLDER
#include "Laser.h"

class LaserHolder:public Unit
{
public:
	LaserHolder(Laser*, std::string id, sf::Vector2f size, sf::Vector2f offset, bool active=true);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position)
	{
		mPosition=position;
		mSprite.setPosition(mPosition);
	};

	virtual sf::Sprite getSprite(){mActiveSprite->setRotation(mRotation);mActiveSprite->setPosition(mPosition);return *mActiveSprite;};

	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.rotate(r);}

	virtual void update(){if(mActive==true){mActiveSprite=&mStandby;};};
	virtual void draw(){};
	virtual void hit();
	virtual void activate(){mActiveSprite=&mOn;};
	virtual void deactivate(){mActiveSprite=&mOff;};

protected:
	float mRotation;

	sf::Sprite* mActiveSprite;
	sf::Sprite mOn;
	sf::Sprite mStandby;
	sf::Sprite mOff;

	Animation* mAnimation;
	bool mActive;

	Laser* mLaser;
};

#endif