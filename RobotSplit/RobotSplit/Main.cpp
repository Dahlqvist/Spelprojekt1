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
	sf::Event event;

	while(mWindow.isOpen())
	{
		statemanager.updateState();
		statemanager.renderState();
	}

	
	return 0;
}
