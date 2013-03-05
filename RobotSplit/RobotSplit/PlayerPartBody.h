#ifndef INC_PLAYERPARTBODY
#define INC_PLAYERPARTBODY
#include "PlayerPart.h"
#include "Animation.h"
#include "PlayerPartFeet.h"

class PlayerPartBody:public PlayerPart
{
public:
	PlayerPartBody(PlayerPartFeet* Feet);
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

	void die();
	void jumpReset();
	void restartAnimation();
	void decideAnimation(sf::Vector2f);
	void aniTimer();
private: 
	bool mAttached;
	Unit* mUnit;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	Animation mWinningAni;
	Animation mWalkingRight;
	Animation mWalkingLeft;
	Animation mJumpingRight;
	Animation mJumpingLeft;
	Animation mLeftPart;
	Animation mRightPart;
	Animation mSplitting;
	Animation mSplittingLeft;
	Animation mDying;
	PlayerPartFeet* mFeet;
	sf::Vector2f mPosition; 
	std::string mId;
	float mJump, mAniTime, mCounter;
 	sf::Clock mJumpClock, mAnimationTimer;
};


#endif