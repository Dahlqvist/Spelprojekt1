#ifndef INC_UNIT
#define INC_UNIT

#include "GameObject.h"
#include "TextureManager.h"
#include "Animation.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Unit: public GameObject
{
public:
	Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid=true);
	Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid=true);
	Unit(sf::Vector2f position, sf::Vector2f size, std::string id, std::string spriteName, bool solid=true);
	Unit(sf::Vector2f position, sf::Vector2f size, std::string id, Animation* animation, bool solid=true);

	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position)
	{
		mPosition=position;
		mSprite.setPosition(mPosition);
	};

	virtual sf::Sprite getSprite(){return mSprite;};

	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};
	virtual void setId(std::string id){mId=id;};

	virtual bool isSolid(){return mSolid;};
	virtual void rotate(float r){mSprite.rotate(r);}

	virtual void update(){};
	virtual void draw();
	virtual void hit(){};
	virtual void activate(){};
	virtual void deactivate(){};

protected:
	sf::Vector2f mSize;
	
	sf::Sprite mSprite;
	Animation* mAnimation;

	bool mSolid;
};

#endif