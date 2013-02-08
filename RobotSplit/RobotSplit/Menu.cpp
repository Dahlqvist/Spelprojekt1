#include "Menu.h"
#include "StateInput.h"
#include "Window.h"

Menu::Menu(): mStateInput(StateInput::getInstance()),
			mBackground("Main", 1, 1),
			mNewGame("NewGame", 1, 1),
			mOptions("Options", 1, 1),
			mQuit("Quit", 1, 1),
			mWindow(Window::getWindow())

{
	mNewGame.setPosition(sf::Vector2f(150, 150));
	mOptions.setPosition(sf::Vector2f(150, 200));
	mQuit.setPosition(sf::Vector2f(150, 250));
}

Menu::~Menu()
{}

void Menu::update()
{
	choice();
}

void Menu::render()
{
	mWindow.draw(mBackground.getSprite());
	mWindow.draw(mNewGame.getSprite());
	mWindow.draw(mOptions.getSprite());
	mWindow.draw(mQuit.getSprite());
}

void Menu::choice()
{
	/*int p;
	std::cin >> p;
	if(p == 1)
		mStateInput.changeState("Game");
	else if(p == 2)
		mStateInput.changeState("Option");
	else
		mStateInput.changeState("Last");*/
}