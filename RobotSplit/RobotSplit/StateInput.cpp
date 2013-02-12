#include "StateInput.h"
#include "StateManager.h"

bool StateInput::mMenuStatus;

StateInput::StateInput(): mStateManager(StateManager::getInstance())
{
	mMenuStatus = true;
}

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
	else if(state == "InGameMenu")
		mStateManager.pushInGameMenu();
	else if(state == "Menu")
		mStateManager.pushMenu();
	else if(state == "Quit")
		mStateManager.restart();
	else
		std::cout << "Error" << std::endl;
}

void StateInput::changeMenu()
{
	mMenuStatus != mMenuStatus;
}

bool StateInput::getMenuStatus()
{
	return mMenuStatus;
}