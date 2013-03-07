#ifndef INC_LASERHOLDER
#define INC_LASERHOLDER
#include "Laser.h"

class LaserHolder:public Unit
{
public:
	LaserHolder(Laser*, std::string id, sf::Vector2f size, sf::Vector2f offset, bool active=true);
	virtual ~LaserHolder();

	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position)
	{
		sf::Vector2f	offset=mPosition-mLaser->getPosition();
		offset.x=abs(offset.x);
		offset.y=abs(offset.y);
		mPosition=position;
		switch(int(mLaser->getRotation()))
		{
		case 0:
			offset.x=abs(offset.x);
			offset.y=abs(offset.y);
			break;
		case 90:
			offset.x=abs(offset.x);
			offset.y=-abs(offset.y);
			break;
		case 180:
			offset.x=-abs(offset.x);
			offset.y=-abs(offset.y);
			break;
		case 270:
			offset.x=abs(offset.x);
			offset.y=-abs(offset.y);
			break;
		}
		mLaser->setPosition(position-offset);
		mSprite.setPosition(mPosition);
	};

	virtual sf::Sprite getSprite(){mActiveSprite->setRotation(mRotation);mActiveSprite->setPosition(mPosition);return *mActiveSprite;};

	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isActive(){return mActive;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.rotate(r);}

	virtual void update();
	virtual void draw(){};
	virtual void hit();
	virtual void activate();
	virtual void deactivate();
	virtual void reset();

protected:
	float mRotation;

	sf::Sprite* mActiveSprite;
	sf::Sprite mOn;
	sf::Sprite mStandby;
	sf::Sprite mOff;

	//Animation* mAnimation;
	bool mActive, mStartActive;

	Laser* mLaser;
	friend	class	LevelSaver;
	friend	class	Editor;
};

#endif