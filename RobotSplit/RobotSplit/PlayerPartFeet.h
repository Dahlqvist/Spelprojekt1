#ifndef INC_PLAYERPARTFEET
#define INC_PLAYERPARTFEET
#include "PlayerPart.h"
#include "Animation.h"
#include "FeetExtensions.h"
#include "FeetWall.h"
#include "RocketFuel.h"

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
	virtual void jump(float);
	virtual void resetAnimation();
	virtual Unit* getUnit();
	virtual void forceMove(sf::Vector2f);
	virtual void winning();
	virtual int getFrame();

	float getFuel();
	
	void die();
	void setId(std::string);
	void activateRocketBoots();
	void reFuel();
	void jumpReset();
	int getWall();
	bool getAttachedWall();
	void setAttachedWall(bool, int i=0);
	void decideAnimation(sf::Vector2f);
	void restartAnimation();
	void aniTimer();
private: 
	bool mAttached, mAttachedWall;
	Unit* mUnit;
	Unit* mAUnit;
	FeetExtensions mFeetExt;
	RocketFuel mRocketFuel;
	FeetWall mRightWall;
	FeetWall mLeftWall;
	FeetWall mRoof;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	Animation mLeftMagnet;
	Animation mRightMagnet;
	Animation mLeftAnimationMagnet;
	Animation mRightAnimationMagnet;
	Animation mJumpAni;
	Animation mJumpAniLeft;
	Animation mWinningAni;
	Animation mDying;
	sf::Vector2f mPosition; 
	std::string mId;
	float mJump, mAniTime, mFuel, mRotation, mCounter;
	sf::Clock mJumpClock, mAnimationTimer;
	int mAO;
};


#endif