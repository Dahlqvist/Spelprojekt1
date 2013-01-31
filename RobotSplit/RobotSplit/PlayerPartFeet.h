#ifndef INC_PLAYERPARTFEET
#define INC_PLAYERPARTFEET
#include "PlayerPart.h"
#include "Animation.h"
#include "FeetExtensions.h"
#include "FeetWall.h"

class PlayerPartFeet:public PlayerPart
{
public:
	PlayerPartFeet();
	virtual void update(); 
	virtual void draw(); 
	virtual sf::Vector2f getPosition(); 
	virtual sf::Sprite getSprite(); 
	virtual std::string getId();
	virtual void setPosition(sf::Vector2f);
	virtual void restartTimer();
	virtual bool getAttached();
	virtual void setAttached(bool);
	virtual void jump();
	virtual void resetAnimation();
	virtual Unit* getUnit();
	void activateRocketBoots();
	void reFuel(float);
	void jumpReset();
	int getWall();
	bool getAttachedWall();
	void setAttachedWall(bool, int i=0);
private: 
	bool mAttached, mAttachedWall;
	Unit* mUnit;
	Unit* mAUnit;
	FeetExtensions mFeetExt;
	FeetWall mRightWall;
	FeetWall mLeftWall;
	FeetWall mRoof;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	sf::Vector2f mPosition; 
	std::string mId;
	float mJump, mAniTime, mFuel, mRotation;
	sf::Clock mJumpClock, mAnimationTimer;
	int mAO;
};


#endif