#ifndef INC_PLATFORM
#define INC_PLATFORM

#include "Unit.h"

class Platform: public Unit
{
public:
	//Setting lives makes the platform destructible
	Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size, sf::Vector2f offset, bool behind=false);
	Platform(int lives, sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string spriteName, bool behind=false);
	virtual ~Platform();

	sf::Sprite getSprite(){return mSprite;};

	int getLives(){return mLives;};
	bool getDestructible(){return mDestructible;};

	void update();
	void draw();
	void activate();
	void hitOnce();
	void reset();
	void setReset();

private:
	int mLives;
	int mStartLives;
	bool mDestructible;
	friend class Toolbar;
	sf::Texture mTexture;
	bool mHasCollided;

	Animation *mBreakAnim, *mNullAnim, *mStartAnimation;
};

#endif