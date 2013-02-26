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
	void restartPlayer();
	void dropFeet();

	bool getWinning();

	void jump();
	void shootHead(sf::Vector2f);
	void setAttachFeetExtension(bool);
	bool getAttachFeetExtension();
	void dash();
	void activateFeetRockets();
	void reFuel(float);
	void win();
	std::string getId(int);
	//bool bodyStandningFeet();
private:
	PlayerPartFeet mFeet;
	PlayerPartBody mBody;
	PlayerPartHead mHead;
	PlayerPartBody* TempPart;
	PlayerParts mParts;
	sf::Sprite mSprite;
	sf::Texture mTexture;
	PlayerLight mLights;
	sf::Sprite* Temp1;
	sf::Sprite* Temp2;
	sf::Sprite* Temp3;
	sf::Sprite* Temp4;
	float mDash;
	sf::Vector2f mStartPosition;
	sf::Clock mSprintTimer, mJumpTemp, mMagnetTimer, mKeyTimer, mClock;
	bool mClockStart;
	bool mHeadless, mTogether, mBodyActive, mFeetAttached, mDashing, mFacingRight;
	bool mAttachedMagnet, mBodyAttached, mHeadAttachedFeet, mBodyStandingFeet;
	bool mKeys, mWinning;
	int magnetSlot, lastKey, thisKey;

	Courser* mCourser;

};

#endif