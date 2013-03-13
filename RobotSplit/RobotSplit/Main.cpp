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
#include "GameTimer.h"

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
	float limit=1.f/60;
	GameTimer	FPSLIMIT(limit);
	mWindow.setFramerateLimit(60);

	int count = 0;
	sf::Clock temp;

	while(mWindow.isOpen())
	{
		if(FPSLIMIT.isExpired())
		{
			FPSLIMIT.reset();	
			while(mWindow.pollEvent(Window::getEvent()))
			{
				if(Window::getEvent().type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
					mWindow.close();
			
				statemanager.inputState();
			}
			if(testClock.getElapsedTime().asSeconds() < 3)
			{
				splash.update();
				splash.render();
			}
			else
			{
				for(int i = 0; i<2; i++)
					statemanager.updateState();

				count++;
				if(count >= 60)
				{
					cout << temp.getElapsedTime().asSeconds() * 60 << endl;
					temp.restart();
					count = 0;
				}
				statemanager.renderState();	
			}
		}
	//	else
//			std::cout<<"Not updated: "<<FPSLIMIT.getCurrentTime()<<std::endl;
	}	
	return 0;
}
