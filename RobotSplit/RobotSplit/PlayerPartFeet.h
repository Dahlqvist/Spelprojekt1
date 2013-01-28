#ifndef INC_PLAYERPARTFEET
#define INC_PLAYERPARTFEET
#include "PlayerPart.h"
#include "Animation.h"

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
	virtual GameObject* getObject();
	void activateRocketBoots();
	void reFuel(float);
private: 
	bool mAttached;
	GameObject* mObject;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	sf::Vector2f mPosition; 
	std::string mId;
	float mJump, mAniTime, mFuel;
	sf::Clock mJumpClock, mAnimationTimer;
};


#endif