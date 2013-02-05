#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
//#include "Window.h"

using namespace std;

int main()
{
	//Window window;
	StateInput& stateinput = StateInput::getInstance();
	StateManager& statemanager = StateManager::getInstance();
	//Window::getWindow().setFramerateLimit(60);

	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split")

	while(
	{
		statemanager.updateState();
		statemanager.renderState();
	}

	
	return 0;
}
