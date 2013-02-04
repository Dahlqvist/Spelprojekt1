#ifndef INC_PLAYERPART
#define INC_PLAYERPART
#include "GameObject.h"
#include "Animation.h"
#include "Unit.h"


class PlayerPart:public GameObject
{
public: 
	virtual void update()=0; 
	virtual void draw()=0; 
	virtual sf::Vector2f getPosition()=0; 
	virtual sf::Sprite getSprite()=0; 
	virtual std::string getId()=0;
	virtual void setPosition(sf::Vector2f)=0;
	virtual void restartTimer()=0;
	virtual bool getAttached()=0;
	virtual void setAttached(bool)=0;
	virtual void jump()=0;
	virtual void resetAnimation()=0;
	virtual Unit* getUnit()=0;
	virtual void forceMove(sf::Vector2f)=0;
private: 
	bool mAttached;
	sf::Vector2f mPosition; 
	std::string mId;
	float Jump;
	sf::Clock mJumpClock, mAnimationTimer;
	Unit* mUnit;
	/*
	GameObject* mObject;
	draw object;
	set object;
	getObject;
	bool objectActive;
	*/
};
//class PlayerPart:public GameObject{
//public:
//	PlayerPart(sf::Texture*, GameObject* Part=0);
//	virtual void update();
//	virtual void draw();
//	virtual sf::Vector2f getPosition();
//	virtual sf::Sprite getSprite();
//	virtual std::string getId();
//	void setPosition(sf::Vector2f);
//	void setAttached(bool);
//	bool getAttached();
//	void setActive(bool);
//	bool getActive();
//	void setMovable(bool);
//	bool getMovable();
//	void jump();
//	void resetJump();
//private:
//	Animation* mActiveAnimation;
//	Animation mLeftAnimation;
//	Animation mRightAnimation;
//	Animation mLeft;
//	Animation mRight;
//	GameObject* mAttachedPart;
//	bool mAttached, mActive, mMovable;
//	sf::Clock mClock;
//	float mJump;
//	sf::Vector2f mPosition;
//	std::string mId;
//	sf::Sprite mSprite;
//};

#endif