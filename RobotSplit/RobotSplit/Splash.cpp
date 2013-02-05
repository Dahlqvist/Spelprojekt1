#include "Splash.h"
#include "StateInput.h"

Splash::Splash(sf::RenderWindow& window): mStateInput(StateInput::getInstance()),
	mWindow(window)
{}

Splash::~Splash()
{
	//std::cout << "Splash DELETE" << std::endl;
}

void Splash::update()
{
	//N�r Splash-screen �r klar skall menu visas
	mStateInput.changeState("Menu");	
}

void Splash::render()
{
	//std::cout << "Splash" << std::endl;
}