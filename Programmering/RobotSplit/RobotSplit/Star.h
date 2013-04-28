#ifndef INC_STAR
#define INC_STAR
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Star
{
public:
	Star(Animation ani, sf::Vector2f startPos, bool active, bool loop);
	void update();
	sf::Sprite getSprite();
	void setActive(bool);
	bool getActive();
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	bool getDone();
private:
	sf::Sprite mSprite;
	bool mActive, mLoop, mDone;
	sf::Vector2f mPosition;
	Animation mAnimation;
};

#endif