#ifndef INC_FEETEXTENSIONS
#define INC_FEETEXTENSIONS
#include "Unit.h"
#include "Animation.h"

class FeetExtensions:public Unit{
public:
	FeetExtensions();
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position; mActiveAnimation->setPosition(mPosition);};

	virtual sf::Sprite getSprite(){return mActiveAnimation->getSprite();};
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){}

	void setFacingRight(bool b){mFacingRight=b; mTimer.restart();};

	virtual void update();
	virtual void draw(){};
private:
	Animation* mActiveAnimation;
	Animation mRight;
	Animation mLeft;
	Animation mRightAni;
	Animation mLeftAni;
	bool mFacingRight;
	sf::Vector2f mSize;
	
	sf::Sprite mSprite;

	sf::Clock mTimer;
	bool mSolid;
};

#endif
