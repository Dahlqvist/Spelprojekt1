#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
#include "Window.h"

using namespace std;

int main()
{
	Window window;
	StateManager& statemanager = StateManager::getInstance();
	StateInput& stateinput = StateInput::getInstance();
	sf::RenderWindow& mWindow = Window::getWindow();
	while(mWindow.isOpen())
	{
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mWindow.close();
		}
		statemanager.updateState();
		statemanager.renderState();
	}

	
	return 0;
}
