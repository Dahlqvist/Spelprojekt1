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

void StateInput::changeState(std::string state,std::string file,unsigned int inpar)
{
	if(state == "Last")
		mStateManager.last();
	else if(state == "Game")
		mStateManager.pushGame();
	else if(state == "High")
		mStateManager.pushHigh(file,inpar);
	else if(state == "Option")
		mStateManager.pushOption();
	else if(state == "InGameMenu")
		mStateManager.pushInGameMenu();
	else if(state == "Menu")
		mStateManager.pushMenu();
	else if(state == "QuitToMenu")
	{
		mStateManager.restart();
		mStateManager.pushMovie("End");
	}
	else if(state == "Audio")
		mStateManager.pushAudio();
	else if(state == "Controls")
		mStateManager.pushControls();
	else if(state == "Intro")
		mStateManager.pushMovie("Intro");
	else if(state == "Bank")
		mStateManager.pushMovie("Bank");
	else if(state == "End")
		mStateManager.pushMovie("End");
	else
		std::cout << "Error" << std::endl;
}

void StateInput::changeMenu()
{
	mMenuStatus = !mMenuStatus;
}

bool StateInput::getMenuStatus()
{
	return mMenuStatus;
}