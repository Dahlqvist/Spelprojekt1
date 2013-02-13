#ifndef INC_PLATFORM
#define INC_PLATFORM

#include "Unit.h"

class Platform: public Unit
{
public:
	//Setting lives makes the platform destructible
	Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size);
	Platform(int lives, sf::Vector2f position, std::string spriteName, sf::Vector2f size);

	sf::Sprite getSprite(){return mSprite;};

	int getLives(){return mLives;};
	bool getDestructible(){return mDestructible;};

	void update();
	void draw();
	void hit();

private:
	int mLives;
	bool mDestructible;

	sf::Texture mTexture;
};

#endif