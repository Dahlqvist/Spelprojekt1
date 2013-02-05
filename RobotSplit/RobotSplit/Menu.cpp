#include "Menu.h"
#include "StateInput.h"

Menu::Menu(): mStateInput(StateInput::getInstance())
{}

Menu::~Menu()
{
	std::cout << "Menu DELETE" << std::endl;
}

void Menu::update()
{
	choice();
}

void Menu::render(sf::RenderWindow& window)
{
	std::cout << "Menu" << std::endl;
}

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