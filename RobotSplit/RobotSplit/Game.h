#ifndef INC_GAME
#define INC_GAME

#include "State.h"
#include "Level.h"
#include "DialogueBox.h"

class StateInput;
class Background;
class Player;
class UnitManager;
class DialogueBox;



class Game: public State
{
public:
	Game();
	virtual ~Game();
	virtual void update();
	virtual void render();
	void input();
private:
	void moveCamera();

	int mSecurityLevel;
	StateInput& mStateInput;
	Level mlevel;
	Player* mPlayer;
	UnitManager* Objects;
	sf::Clock lastUpdateClock;
	bool mRenderGame;
	double nextUpdate;
	int loops;
	sf::RenderWindow& mWindow;
	sf::Clock TestTimer;
	float mTime;
	std::vector<DialogueBox*> diaBox;
	std::vector<Background*> BG;
	//Sound& mSound;
	
};

#endif