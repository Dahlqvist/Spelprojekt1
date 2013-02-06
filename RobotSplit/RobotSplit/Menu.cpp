#include "Menu.h"
#include "StateInput.h"

Menu::Menu(): mStateInput(StateInput::getInstance())
{}

Menu::~Menu()
{}

void Menu::update()
{
	choice();
}

void Menu::render()
{}

void Menu::choice()
{
	int p;
	std::cin >> p;
	if(p == 1)
		mStateInput.changeState("Game");
	else if(p == 2)
		mStateInput.changeState("Option");
	else
		mStateInput.changeState("Last");
}