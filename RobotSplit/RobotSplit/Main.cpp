#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
//#include "Window.h"

using namespace std;

int main()
{
	//Window window;
	StateManager& statemanager = StateManager::getInstance();
	StateInput& stateinput = StateInput::getInstance();
	
	//Window::getWindow().setFramerateLimit(60);

	
	while(true)
	{
		statemanager.updateState();
		statemanager.renderState();
	}

	
	return 0;
}
