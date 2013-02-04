#include "StateInput.h"
#include "StateManager.h"


StateInput::StateInput(): mStateManager(StateManager::getInstance())
{}

StateInput::~StateInput()
{}

StateInput& StateInput::getInstance()
{
	static StateInput stateinput;
	return stateinput;
}

void StateInput::changeState(std::string state)
{
	if(state == "Last")
		mStateManager.last();
	else if(state == "Game")
		mStateManager.pushGame();
	else if(state == "Option")
		mStateManager.pushOption();
	else if(state == "Splash")
		mStateManager.pushSplash();
	else if(state == "InGameMenu")
		mStateManager.pushInGameMenu();
	else if(state == "Menu")
		mStateManager.pushMenu();
	else if(state == "Quit")
		mStateManager.restart();
	else
		std::cout << "Error" << std::endl;
}