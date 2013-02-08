#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
#include "Window.h"
#include "Splash.h"
#include "Sound.h"
#include "Music.h"

using namespace std;

int main()
{
	Window window;
	Splash& splash = Splash::getInstance();
	Sound& sound = Sound::getInstance();
	Music& music = Music::getInstance();
	StateManager& statemanager = StateManager::getInstance();
	StateInput& stateinput = StateInput::getInstance();
	sf::RenderWindow& mWindow = Window::getWindow();
	mWindow.setFramerateLimit(60);
	while(mWindow.isOpen())
	{
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mWindow.close();
		}

		if(Splash::getStatus())
		{
			splash.update();
			splash.render();
		}
		/*else
		{
			statemanager.updateState();
			statemanager.renderState();
		}*/
	}

	
	return 0;
}
