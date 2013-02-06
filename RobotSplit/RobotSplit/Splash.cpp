#include "Splash.h"
#include "StateInput.h"
#include "Window.h"

Splash::Splash(): mStateInput(StateInput::getInstance())
{}

Splash::~Splash()
{
	//std::cout << "Splash DELETE" << std::endl;
}

void Splash::update()
{
	//När Splash-screen är klar skall menu visas
	mStateInput.changeState("Menu");	
}

void Splash::render()
{
	//std::cout << "Splash" << std::endl;
}