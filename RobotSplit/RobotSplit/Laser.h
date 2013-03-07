#ifndef INC_LASER
#define INC_LASER
#include"Unit.h"

class Laser:public Unit
{
public:
	Laser(sf::Vector2f, std::string, bool, float, float rotate=0);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position;};

	virtual sf::Sprite getSprite();

	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual float getLength(){return mMaxLength;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mRotation=r;};
	float getRotation(){return mRotation;}
	void setLength(float l);
	void setSpeed(float s){mSpeed=s;};

	virtual void update();
	virtual void draw(){};
	virtual void hit(){};
	virtual void activate(){mActive=true;};
	void deactivate(){mActive=false;};

protected:
	sf::Vector2f mSize;
	float mRotation, mLength, mMaxLength;
	bool mActive;
	float mSpeed;
	
	sf::Sprite mSprite;
	Animation* mAnimation;
	Animation mRedLaser;
	Animation mBlueLaser;
	Animation mYellowLaser;
	friend class Editor;
};

#endif