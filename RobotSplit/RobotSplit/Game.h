#ifndef INC_GAME
#define INC_GAME

#include "State.h"
#include "Level.h"

class StateInput;
class Background;
class Level;
class Player;
class UnitManager;


class Game: public State
{
public:
	Game();
	virtual ~Game();
	virtual void update();
	virtual void render();
private:
	StateInput& mStateInput;
	Background *BG;
	Level mlevel;
	Player* mPlayer;
	UnitManager* Objects;
	sf::Clock lastUpdateClock;
	double lastUpdate;
	int loops;
	
};

#endif