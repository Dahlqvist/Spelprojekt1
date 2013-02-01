#ifndef INC_BRAINMAGNET
#define INC_BRAINMAGNET
#include "Unit.h"

class BrainMagnet:public Unit{
public:
	BrainMagnet(std::string spriteName);
	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position; mSprite.setPosition(mPosition);};

	virtual sf::Sprite getSprite(){return mSprite;};
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.setRotation(r);}
	void setOrigin(sf::Vector2f);

	virtual void update(){};
	virtual void draw(){};
private:
	sf::Vector2f mSize;
	
	sf::Sprite mSprite;

	bool mSolid;
};

#endif