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
	void interact(int);

	std::vector<sf::Sprite*> getCollisionSprite();
	void forceMove(int, sf::Vector2f);
	void checkCollisionExt();
	void checkCollisionMagnet();
	void restartPlayer(sf::Vector2f);

	void jump();
	void shootHead(sf::Vector2f);
	void setAttachFeetExtension(bool);
	bool getAttachFeetExtension();
	void dash();
	void activateFeetRockets();
	void reFuel(float);
	//bool bodyStandningFeet();
private:
	PlayerPartFeet mFeet;
	PlayerPartBody mBody;
	PlayerPartHead mHead;
	PlayerPartBody* TempPart;
	PlayerParts mParts;
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Sprite mLjus;
	sf::Texture mLjus1;
	sf::Texture mLjus2;
	sf::Texture mLjus3;
	sf::Sprite* Temp1;
	sf::Sprite* Temp2;
	sf::Sprite* Temp3;
	sf::Sprite* Temp4;
	float mSpeed, mJump, mDash;
	sf::Clock mSprintTimer, mJumpTemp, mMagnetTimer;
	bool mHeadless, mTogether, mBodyActive, mFeetAttached, mDashing, mFacingRight;
	bool mAttachedMagnet, mBodyAttached, mHeadAttachedFeet, mBodyStandningFeet;
	int magnetSlot;
};

#endif