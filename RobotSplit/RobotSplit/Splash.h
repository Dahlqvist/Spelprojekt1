#ifndef INC_SPLASH
#define INC_SPLASH

#include "State.h"

class StateInput;
class TextureManager;
class Animation;

class Splash: public State
{
public:
	Splash();
	virtual ~Splash();
	virtual void update();
	virtual void render();
private:
	sf::Sprite& returnSprite();
	StateInput& mStateInput;
	sf::Clock mTime;
	Animation *currentSprite;
	Animation mWatermelon;
	Animation mConcept1;

	sf::RenderWindow &mWindow;
};

#endif