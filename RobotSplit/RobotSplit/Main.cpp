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
		timer.update();
		timer.render();


		if(Splash::getStatus())
		{
			splash.update();
			splash.render();
		}
		else
		{
			int loops = 0;
			//bool render = false;
			

			while(/*lastUpdate.getElapsedTime().asSeconds() > nextUpdate && */loops < 2)
			{
				loops++;
				//nextUpdate +=1/60.0;
				//render = true;
				statemanager.updateState();
				//temp = lastUpdate.getElapsedTime().asSeconds();
				//cout << "Time: " << temp << endl;
			}
			
			//if(render)
			//{
				statemanager.renderState();
				//lastUpdate.restart();
				//nextUpdate = 1/60.0;
				//cout << "Loops: " << loops << endl;
			//}
			//cout << "Time: " << lastUpdate.getElapsedTime().asSeconds() << endl;
			
			
		}
	}

	
	return 0;
}
