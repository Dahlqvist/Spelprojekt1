#ifndef INC_PLAYER
#define INC_PLAYER
#include <SFML\Graphics.hpp>
#include "PlayerPartFeet.h"
#include "PlayerPartBody.h"
#include "PlayerPartHead.h"

class Player
{
public:
	typedef std::vector<PlayerPart*> PlayerParts;
	Player();
	void move(sf::Vector2f);
	void draw(sf::RenderWindow&);
	void update();
	bool getTogether();
	void setTogether(bool);
	bool getBodyActive();
	void setBodyActive(bool);
	bool getHeadless();
	void setHeadless(bool);
	void jump();
	sf::FloatRect getRect();
	std::vector<sf::Sprite*> getCollisionSprite();
	void resetAnimations();
	void shootHead(sf::Vector2f);
	void setAttachFeet(bool);
	bool getAttachFeet();
	void sprint();
private:
	PlayerPartFeet mFeet;
	PlayerPartBody mBody;
	PlayerPartHead mHead;
	PlayerParts mParts;
	float mSpeed, mJump;
	sf::Clock mSprintTimer;
	bool mHeadless, mTogether, mBodyActive, mFeetAttached;
	int mState;
};

#endif