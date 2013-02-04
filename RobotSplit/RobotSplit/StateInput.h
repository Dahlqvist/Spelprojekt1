#ifndef INC_STATEINPUT
#define INC_STATEINPUT

#include <string>

class StateManager;

class StateInput
{
public:
	static StateInput& getInstance();
	void changeState(std::string state);

private:
	StateInput();
	StateInput(const StateInput& stateinput);
	StateInput operator=(const StateInput& stateinput);
	~StateInput();
	StateManager& mStateManager;
};

#endif