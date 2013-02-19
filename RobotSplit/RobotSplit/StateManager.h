#ifndef INC_STATEMANAGER
#define INC_STATEMANAGER

#include <SFML/Graphics.hpp>

#include "State.h"

#include <stack>
#include <vector>

class StateManager
{
public:
	static StateManager& getInstance();

	void pushState(State* state);
	void popState();

	void updateState();
	void renderState();

	void restart();

	void last();
	void pushGame();
	void pushOption();
	void pushInGameMenu();
	void pushMenu();
	void pushAudio();

	void loadState();
private:
	StateManager();
	StateManager(const StateManager& statemanager);
	StateManager operator=(const StateManager& statemanager);
	~StateManager();
	void internalClear();

	typedef std::stack<State*> StateStack;
	StateStack mStateStack;

	State* mGame;
	State* mOption;
	State* mMenu;
	State* mInGameMenu;
	State* mAudio;

};
#endif