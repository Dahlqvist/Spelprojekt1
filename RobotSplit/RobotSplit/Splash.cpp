#include "Splash.h"
#include "StateInput.h"

Splash::Splash(): mStateInput(StateInput::getInstance())
{}

Splash::~Splash()
{
	std::cout << "Splash DELETE" << std::endl;
}

void Splash::update()
{
	//När Splash-screen är klar skall menu visas
	mStateInput.changeState("Menu");	
}

void Splash::render(sf::RenderWindow& window)
{
	std::cout << "Splash" << std::endl;
}