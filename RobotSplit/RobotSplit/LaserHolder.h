#ifndef INC_LASERHOLDER
#define INC_LASERHOLDER
#include "Laser.h"

class LaserHolder:public Unit
{
public:
	LaserHolder(Laser*, std::string id, sf::Vector2f size, sf::Vector2f offset, bool active=true);
	virtual ~LaserHolder();

	virtual sf::Vector2f getPosition();
	virtual void setPosition(sf::Vector2f position);

	virtual sf::Sprite getSprite();

	virtual sf::Vector2f getSize();

	virtual std::string getId();

	virtual bool isActive();

	virtual bool isSolid();
	virtual void rotate(float r);

	virtual	float getRotation();

	virtual void update();
	virtual void draw(){};
	virtual void hit();
	virtual void activate();
	virtual void deactivate();
	virtual void reset();
	virtual void setReset();

	virtual Laser* getLaser();

	virtual	void setVisibilityRange(float range);
	virtual	void setActive(bool);

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
	friend	class	Toolbar;
};

#endif