#include "InGameMenu.h"
#include "StateInput.h"

InGameMenu::InGameMenu(): mStateInput(StateInput::getInstance())
{}

InGameMenu::~InGameMenu()
{
	std::cout << "InGameMenu DELETE" << std::endl;
}

void InGameMenu::update()
{
	choice();
}

void InGameMenu::render()
{
	std::cout << "InGameMenu" << std::endl;
}

void InGameMenu::choice()
{
	int p;
	std::cin >> p;
	if(p == 1)
		mStateInput.changeState("Last");
	else if(p == 2)
		mStateInput.changeState("Option");
	else if(p == 3)
		mStateInput.changeState("Quit");
	else
		std::cout << "Error" << std::endl;
}