#ifndef INC_PLAYER
#define INC_PLAYER
#include <SFML\Graphics.hpp>
#include "PlayerPartFeet.h"
#include "PlayerPartBody.h"
#include "PlayerPartHead.h"
#include "PlayerLight.h"
#include "Courser.h"

class Player
{
public:
	typedef std::vector<PlayerPart*> PlayerParts;
	Player(sf::Vector2f);
	~Player();
	void initSprites();
	void move(sf::Vector2f);
	void draw(sf::RenderWindow&, bool);
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
	void restartPlayer();
	void dropFeet();

	bool getWinning();
	void setStartingPosition(sf::Vector2f);
	void die(int);

	bool getDying();
	void jump();
	void shootHead(sf::Vector2f);
	void setAttachFeetExtension(bool);
	bool getAttachFeetExtension();
	void dash();
	void activateFeetRockets();
	void reFuel();
	void win();
	std::string getId(int);
	//bool bodyStandningFeet();
private:
	PlayerPartFeet mFeet;
	PlayerPartBody mBody;
	PlayerPartHead mHead;
	PlayerPartFeet* TempPart;
	PlayerParts mParts;
	PlayerLight mLights;
	sf::Sprite* TempFeet;
	sf::Sprite* TempBody;
	sf::Sprite* TempHead;
	sf::Sprite* TempMagnet;
	sf::Sprite* TempExtension;
	sf::Sprite* TempWhole;
	sf::Sprite mRocketFuelBar;
	sf::Sprite mRocketFuel;
	float mDash, temporary;
	sf::Vector2f mStartPosition;
	sf::Clock mSprintTimer, mJumpTemp, mMagnetTimer, mKeyTimer, mClock, mDieTimer;
	bool mClockStart;
	bool mHeadless, mTogether, mBodyActive, mFeetAttached, mDashing, mFacingRight;
	bool mAttachedMagnet, mBodyAttached, mHeadAttachedFeet, mBodyStandingFeet;
	bool mKeys, mWinning, mRocketing, mDying, mBodyDied;
	int magnetSlot, lastKey, thisKey;

	Courser* mCourser;
};

#endif