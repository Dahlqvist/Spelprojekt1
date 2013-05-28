#include "MovieState.h"
#include "Window.h"

MovieState::MovieState():
mStateInput(StateInput::getInstance())
{

}
void MovieState::update()
{
	if(mMovie->playing())
	{
		mMovie->update();
	}
	else
	{
		delete mMovie;
		mStateInput.changeState("Last");
		//Changestate("Last");
	}
}
void MovieState::render()
{
	if(mMovie->playing())
	{
		mMovie->draw();
	}
}
void MovieState::input()
{
	if(Window::getEvent().type == sf::Event::KeyPressed)
	{
		mMovie->countup();
	}
	if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Escape)
	{
		mMovie->endit();
	}
}
void MovieState::setMovie(std::string movieName)
{
	if(movieName=="Intro")
	mMovie=new IntroMovie;
	if(movieName=="Bank")
	mMovie=new BankMovie;
	if(movieName=="End")
	mMovie=new EndMovie;
}