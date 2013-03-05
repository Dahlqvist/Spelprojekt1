#include "StateManager.h"

#include "Game.h"
#include "Option.h"
#include "InGameMenu.h"
#include "Menu.h"
#include "Audio.h"
#include "Controls.h"
#include "Timer.h"

StateManager::StateManager()
	
{
	loadState();
	pushState(mMenu);
}

void StateManager::loadState()
{
	 mGame = new Game;
	 mOption = new Option;
	 mMenu = new Menu;
	 mInGameMenu = new InGameMenu;
	 mAudio = new Audio;
	 mControls = new Controls;

}
StateManager::~StateManager()
{
	void internalClear();
	delete mGame;
	delete mOption;
	delete mInGameMenu;
	delete mMenu;
	delete mAudio;
	delete mControls;
}

StateManager& StateManager::getInstance()
{
	static StateManager statemanager;
	return statemanager;
}

void StateManager::pushState(State* state)
{
	mStateStack.push(state);
	mStateStack.top() ->update();
}

void StateManager::popState()
{
	mStateStack.pop();
}

void StateManager::updateState()
{
	mStateStack.top()->update();
}

void StateManager::renderState()
{
	mStateStack.top()->render();
}

void StateManager::inputState()
{
	mStateStack.top()->input();
}

State* StateManager::getState()
{
	return mStateStack.top();
}

void StateManager::internalClear()
{
	while(!mStateStack.empty())
	{
		delete mStateStack.top();
		mStateStack.pop();
	}
}

void StateManager::last()
{
	popState();
}

void StateManager::pushOption()
{
	pushState(mOption);
}

void StateManager::pushGame()
{
	pushState(mGame);
}

void StateManager::pushInGameMenu()
{
	pushState(mInGameMenu);
}

void StateManager::pushMenu()
{
	pushState(mMenu);
}

void StateManager::restart()
{
	while(!mStateStack.empty())
		mStateStack.pop();
	delete mGame;
	mGame = new Game;
	pushState(mMenu);
}

void StateManager::pushAudio()
{
	pushState(mAudio);
}

void StateManager::pushControls()
{
	pushState(mControls);
}