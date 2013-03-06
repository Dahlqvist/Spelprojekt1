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

	float high = 0.0;
	float low = 0.0;
	float average = 0.0;
	float time = 0.0;

	mWindow.setFramerateLimit(60);
	while(mWindow.isOpen())
	{
		sf::Clock temp;
		while(mWindow.pollEvent(Window::getEvent()))
		{
			if(Window::getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				mWindow.close();
			
			statemanager.inputState();
			if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::T)
			{
				cout << "High: " << high << endl;
				cout << "Low: " << low << endl;
			}
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
		time = temp.getElapsedTime().asSeconds();
		if(high < time)
			high = time;
		if(low > time)
			low = time;
		//cout << temp.getElapsedTime().asSeconds() << endl;
	}	
	return 0;
}
