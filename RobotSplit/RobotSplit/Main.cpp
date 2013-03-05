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
	sf::Clock testClock;

	mWindow.setFramerateLimit(60);
	while(mWindow.isOpen())
	{
		sf::Clock temp;
		while(mWindow.pollEvent(Window::getEvent()))
		{
			if(Window::getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				mWindow.close();
			
			statemanager.inputState();
		}
		if(testClock.getElapsedTime().asSeconds() < 3)
		{
			//splash.runSplash("StixSplashJump", 1, 1);
			splash.update();
			splash.render();
		}
		else
		{
			for(int i = 0; i<2; i++)
				statemanager.updateState();
			statemanager.renderState();	
		}
		//cout << temp.getElapsedTime().asSeconds() << endl;
	}	
	return 0;
}
