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
	Window& window = Window::getInstance();
	Sound& sound = Sound::getInstance();
	Music& music = Music::getInstance();
	Splash& splash = Splash::getInstance();
	StateManager& statemanager = StateManager::getInstance();
	StateInput& stateinput = StateInput::getInstance();
	sf::RenderWindow& mWindow = Window::getWindow();
	mWindow.setFramerateLimit(60);
	Splash::runSplash(false);

	sf::Clock lastUpdate;
	float nextUpdate = 0;

	while(mWindow.isOpen())
	{
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				mWindow.close();
		}

		if(Splash::getStatus())
		{
			splash.update();
			splash.render();
		}
		else
		{
			int loops = 0;
			bool render = false;
			while(lastUpdate.getElapsedTime().asSeconds() > nextUpdate && loops < 5)
			{
				loops++;
				nextUpdate +=1/60.0;
				render = true;
				statemanager.updateState();
			}
			if(render)
				statemanager.renderState();
			lastUpdate.restart();
			nextUpdate = 0;
		}
	}

	
	return 0;
}
