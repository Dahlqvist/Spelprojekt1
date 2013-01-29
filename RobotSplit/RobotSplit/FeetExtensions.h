#ifndef INC_FEETEXTENSIONS
#define INC_FEETEXTENSIONS
#include "Unit.h"

class FeetExtensions:public Unit{
public:
	FeetExtensions(std::string spriteName);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position; mSprite.setPosition(mPosition);};

	virtual sf::Sprite getSprite(){return mSprite;};
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.setOrigin(sf::Vector2f(32, 32)); mSprite.rotate(r);}

	virtual void update(){};
	virtual void draw(){};
private:
	sf::Vector2f mSize;
	
	sf::Sprite mSprite;

	bool mSolid;
};

#endif
