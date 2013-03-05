#ifndef INC_GAMEOBJECT
#define INC_GAMEOBJECT
#include <SFML/Graphics.hpp>
#include <string>


class GameObject{
public: 
	virtual ~GameObject(){};
	virtual void update()=0; 
	virtual void draw()=0; 
	virtual sf::Vector2f getPosition()=0; 
	virtual sf::Sprite getSprite()=0; 
	virtual std::string getId()=0;
	virtual void setPosition(sf::Vector2f)=0;
protected: 
	sf::Vector2f mPosition; 
	std::string mId;
};

#endif