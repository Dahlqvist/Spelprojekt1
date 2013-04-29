#ifndef INC_LASER
#define INC_LASER
#include"Unit.h"

class Laser:public Unit
{
public:
	Laser(sf::Vector2f, std::string, bool, float, float rotate=0);
	virtual sf::Vector2f getPosition();
	virtual void setPosition(sf::Vector2f position);

	virtual sf::Sprite getSprite();

	virtual sf::Vector2f getSize();

	virtual std::string getId();

	virtual float getLength();

	virtual bool isSolid();
	virtual void rotate(float r);
	float getRotation();
	void setLength(float l);
	void setSpeed(float s);

	virtual void update();
	virtual void draw(){};
	virtual void hit(){};
	virtual void activate(){mActive=true;};
	void deactivate(){mActive=false;};
	void	setColor(std::string color);

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
	friend class Toolbar;
};

#endif