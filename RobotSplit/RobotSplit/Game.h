#ifndef INC_GAME
#define INC_GAME

#include "State.h"
#include "Level.h"
#include "DialogueBox.h"
#include "MiniBot.h"

class StateInput;
class Background;
class Player;
class UnitManager;
class DialogueBox;
class Timer;



class Game: public State
{
public:
	Game();
	virtual ~Game();
	virtual void update();
	virtual void render();

	virtual void input();
	void changeMap(int);
private:
	void setMusic();

	void keyboardInput();
	void joystickInput();
	bool mJoystick;
	sf::Vector2i mousePos;
	float mCourseSpeed;

	void moveCamera();

	int mSecurityLevel;
	StateInput& mStateInput;
	Level mlevel;
	Player* mPlayer;
	UnitManager* Objects;
	bool mRenderGame;
	int loops;
	sf::RenderWindow& mWindow;
	sf::Clock TestTimer;
	float mTime;
	std::vector<DialogueBox*> diaBox;
	std::vector<Background*> BG;
	std::vector<std::string> mBanor;
	int mBana;
	//Sound& mSound;
	Timer* mTimer;
	
};

#endif