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
	Player(sf::Vector2f);
	void move(sf::Vector2f);
	void draw(sf::RenderWindow&);
	void update();
	bool getTogether();
	void setTogether(bool);
	bool getBodyActive();
	void setBodyActive(bool);
	bool getHeadless();
	void setHeadless(bool);
	void resetAnimations();

	std::vector<sf::Sprite*> getCollisionSprite();
	void forceMove(int, sf::Vector2f);

	void jump();
	void shootHead(sf::Vector2f);
	void setAttachFeet(bool);
	bool getAttachFeet();
	void sprint();
	void activateFeetRockets();
	void reFuel(float);
private:
	PlayerPartFeet mFeet;
	PlayerPartBody mBody;
	PlayerPartHead mHead;
	PlayerParts mParts;
	float mSpeed, mJump;
	sf::Clock mSprintTimer;
	bool mHeadless, mTogether, mBodyActive, mFeetAttached;
};

#endif