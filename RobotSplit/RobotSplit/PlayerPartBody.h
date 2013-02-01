#ifndef INC_PLAYERPARTBODY
#define INC_PLAYERPARTBODY
#include "PlayerPart.h"
#include "Animation.h"
#include "PlayerPartFeet.h"

class PlayerPartBody:public PlayerPart
{
public:
	PlayerPartBody(PlayerPart* Feet);
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
	virtual void forceMove(sf::Vector2f);
	void jumpReset();
	void restartAnimation();
private: 
	bool mAttached;
	Unit* mUnit;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	PlayerPart* mFeet;
	sf::Vector2f mPosition; 
	std::string mId;
	float mJump, mAniTime;
 	sf::Clock mJumpClock, mAnimationTimer;
};


#endif