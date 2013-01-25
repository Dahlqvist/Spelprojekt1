#ifndef INC_UNIT
#define INC_UNIT

#include "GameObject.h"
#include "TextureManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Unit: public GameObject
{
public:
	Unit(sf::Vector2f position, std::string id, bool solid=true);

	virtual sf::Vector2f getPosition(){return mPosition;};
	virtual void setPosition(sf::Vector2f position){mPosition=position;};

	virtual sf::Sprite getSprite(){return mSprite;};
	virtual sf::Vector2f getSize(){return mSize;};

	virtual std::string getId(){return mId;};

	virtual bool isSolid(){return mSolid;};

	virtual void update(){};
	virtual void draw(){};

protected:
	sf::Vector2f mSize;
	
	sf::Sprite mSprite;

	bool mSolid;
};

#endif