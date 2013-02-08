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
	input();
}

void Menu::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mBackground.getSprite());
	mWindow.draw(mNewGame.getSprite());
	mWindow.draw(mOptions.getSprite());
	mWindow.draw(mQuit.getSprite());
	mWindow.display();
}

void Menu::input()
{


	/*mStateInput.changeState("Game");
		mStateInput.changeState("Option");
		mStateInput.changeState("Last");*/
}