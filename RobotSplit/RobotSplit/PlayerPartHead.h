#ifndef INC_PLAYERPARTHEAD
#define INC_PLAYERPARTHEAD
#include "PlayerPart.h"
#include "Animation.h"
#include "BrainMagnet.h"

class PlayerPartHead:public PlayerPart
{
public:
	PlayerPartHead(PlayerPart* Body);
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
	void setShootVector(sf::Vector2f);
private: 
	bool mAttached;
	Unit* mUnit;
	BrainMagnet mMagnet;
	Animation* mActiveAnimation;
	Animation mLeftAnimation;
	Animation mRightAnimation;
	Animation mLeft;
	Animation mRight;
	PlayerPart* mBody;
	sf::Vector2f mPosition, mShootVector; 
	std::string mId;
	float mJump, mAniTime;
	sf::Clock mJumpClock, mAnimationTimer;
};


#endif