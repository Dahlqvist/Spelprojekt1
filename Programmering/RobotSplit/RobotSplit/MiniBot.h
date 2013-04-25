#ifndef INC_MINIBOT
#define INC_MINIBOT
#include "Unit.h"

class MiniBot:public Unit
{
public:
	MiniBot(sf::Vector2f position, float rotation, float length, bool sideways);

	sf::Sprite getSprite();
	void update();
	void hitOnce();
	void reset();
private:
	Animation* mAnimation;
	Animation mWalking;
	Animation mCharging;
	Animation mRelease;
	float mLength, mCharge, mMaxCharge, mRotation;
	sf::Vector2f mStartPosition;
	bool mGoingRight, mSideways;
	friend	class	LevelSaver;
};

#endif