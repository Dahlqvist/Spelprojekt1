#ifndef INC_SPLASH
#define INC_SPLASH

#include "Animation.h"
#include "Window.h"

class TextureManager;

class Splash
{
public:
	static Splash& getInstance();

	void runSplash(std::string sprite, int timePerFrame, int nrFrames);
	static bool getStatus();

	void update();
	void render();
private:
	Splash();
	Splash(const Splash& splash);
	Splash operator=(const Splash& splash);
	~Splash();

	sf::Sprite& returnSprite();
	sf::Clock mTime;
	Animation *currentAnimation;
	Animation mSplash;

	/*std::string mSprite;
	int mTimePerFrame;
	int mNrFrames;*/

	sf::RenderWindow &mWindow;

	static bool mStatus;

};

#endif