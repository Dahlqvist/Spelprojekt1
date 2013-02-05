#include "StateManager.h"

#include "Game.h"
#include "Option.h"
#include "Splash.h"
#include "InGameMenu.h"
#include "Menu.h"

StateManager::StateManager(): mGame(new Game), mOption(new Option), mSplash(new Splash),
								mMenu(new Menu), mInGameMenu(new InGameMenu)
{
	pushState(mSplash);
}

StateManager::~StateManager()
{
	void internalClear();
	delete mGame;
	delete mOption;
	delete mSplash;
	delete mInGameMenu;
	delete mMenu;
}

StateManager& StateManager::getInstance()
{
	static StateManager statemanager;
	return statemanager;
}

void StateManager::pushState(State* state)
{
	mStateStack.push(state);
}

void StateManager::popState()
{
	mStateStack.pop();
}

void StateManager::updateState()
{
	mStateStack.top()->update();
}

void StateManager::renderState(sf::RenderWindow& window)
{
	mStateStack.top()->render(window);
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

void StateManager::pushSplash()
{
	pushState(mSplash);
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
	pushState(mSplash);
}