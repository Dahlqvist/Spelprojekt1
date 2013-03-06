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
	float low = 999.9;
	float counter = 0.0;
	float time = 0.0;
	float average = 0.0;
	float aTime = 0.0;
	float aHigh = 0.0;
	float aLow = 999.9;

	mWindow.setFramerateLimit(60);
	//mWindow.setVerticalSyncEnabled(true);
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
				cout << "Counter: " << counter << endl;
				cout << "Average: " << average << endl;
				cout << "aHigh: " << aHigh << endl;
				cout << "aLow: " << aLow << endl;
				cout << endl << endl << endl;
			}
			if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::U)
			{
				average = 0.0;
				counter = 0.0;
				high = 0.0;
				low = 999.9;
				time = 0.0;
				aHigh = 0.0;
				aLow = 999.9;
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
		aTime += time;
		counter++;
		
		if(counter >= 60)
		{
			average = aTime / counter;
			if(aHigh < average)
				aHigh = average;
			if(aLow > average)
				aLow = average;
			counter = 0.0;
			aTime = 0.0;			
		}
		if(high < time)
			high = time;		
		if(low > time)
			low = time;
		//cout << temp.getElapsedTime().asSeconds() << endl;
	}	
	return 0;
}
