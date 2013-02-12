#ifndef INC_STATEINPUT
#define INC_STATEINPUT

#include <string>

class StateManager;

class StateInput
{
public:
	static StateInput& getInstance();
	void changeState(std::string state);
	static void changeMenu();
	static bool getMenuStatus();

private:
	StateInput();
	StateInput(const StateInput& stateinput);
	StateInput operator=(const StateInput& stateinput);
	~StateInput();
	StateManager& mStateManager;
	static bool mMenuStatus;
};

#endif