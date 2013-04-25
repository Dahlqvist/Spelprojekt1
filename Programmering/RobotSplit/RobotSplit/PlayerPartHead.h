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
	virtual void jump(float);
	virtual void resetAnimation();
	virtual Unit* getUnit();
	virtual void forceMove(sf::Vector2f);
	virtual void winning();
	virtual int getFrame();

	void setShootVector(sf::Vector2f);
	void setMagnetSolid(bool);
	void setMagnetCollided(bool);
private: 
	bool mAttached, mMagnetCollided;
	Unit* mUnit;
	BrainMagnet mMagnet;
	Animation* mActiveAnimation;
	Animation mBrain;
	Animation mBrainStuck;
	Animation mBrainLowered;
	PlayerPart* mBody;
	sf::Vector2f mPosition, mShootVector; 
	std::string mId;
	float mJump, mAniTime;
	sf::Clock mJumpClock, mAnimationTimer;
};


#endif