#ifndef INC_SPLASH
#define INC_SPLASH

#include "State.h"
#include "Animation.h"

class StateInput;
class TextureManager;

class Splash: public State
{
public:
	static Splash& getInstance();

	static void runSplash(bool status);
	static bool getStatus();

	virtual void update();
	virtual void render();
	virtual void input(){};
private:
	Splash();
	Splash(const Splash& splash);
	Splash operator=(const Splash& splash);
	virtual ~Splash();

	sf::Sprite& returnSprite();
	StateInput& mStateInput;
	sf::Clock mTime;
	Animation *currentAnimation;
	Animation mWatermelon;
	Animation mConcept1;

	sf::RenderWindow &mWindow;

	static bool mStatus;

};

#endif