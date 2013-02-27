#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
#include "Window.h"
#include "Splash.h"
#include "Game.h"
#include "Sound.h"
#include "Music.h"
#include "State.h"
#include "Timer.h"

using namespace std;

int main()
{
	Window& window = Window::getInstance();
	Sound& sound = Sound::getInstance();
	Music& music = Music::getInstance();
	Splash& splash = Splash::getInstance();
	StateManager& statemanager = StateManager::getInstance();
	StateInput& stateinput = StateInput::getInstance();
	sf::RenderWindow& mWindow = Window::getWindow();
	Splash::runSplash(false);

	Timer& timer = Timer::getInstance();

	mWindow.setFramerateLimit(60);
	while(mWindow.isOpen())
	{
		while(mWindow.pollEvent(Window::getEvent()))
		{
			if(Window::getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				mWindow.close();
			
			statemanager.inputState();
			timer.input();
		}


		if(Splash::getStatus())
		{
			splash.update();
			splash.render();
		}
		else
		{
			for(int i = 0; i<2; i++)
				statemanager.updateState();
			statemanager.renderState();			
		}
	}	
	return 0;
}
