#ifndef INC_BRAINMAGNET
#define INC_BRAINMAGNET
#include "Unit.h"
#include "Animation.h"
#include <iostream>

class BrainMagnet:public Unit{
public:
	BrainMagnet(std::string spriteName);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position; mActiveAnimation->setPosition(mPosition);};

	virtual sf::Sprite getSprite();
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	void setSolid(bool);
	virtual void rotate(float r){mSprite.setRotation(r);}
	void setOrigin(){mBrainAni.restart(); mTimer.restart(); mActiveAnimation=&mBrainAni;};

	virtual void update();
	virtual void draw(){};

private:
	Animation* mActiveAnimation;
	Animation mBrain;
	Animation mBrainAni;
	sf::Vector2f mSize;
	sf::Clock mTimer;
	
	sf::Sprite mSprite;

	bool mSolid;
};

#endif