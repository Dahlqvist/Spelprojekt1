#ifndef INC_PLATFORM
#define INC_PLATFORM

#include "Unit.h"

class Platform: public Unit
{
public:
	//Setting lives makes the platform destructible
	Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size, sf::Vector2f offset);
	Platform(int lives, sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset);
	~Platform();

	sf::Sprite getSprite(){return mSprite;};

	int getLives(){return mLives;};
	bool getDestructible(){return mDestructible;};

	void draw();
	void hitOnce();
	void reset();

private:
	int mLives;
	int mStartLives;
	bool mDestructible;

	sf::Texture mTexture;
};

#endif