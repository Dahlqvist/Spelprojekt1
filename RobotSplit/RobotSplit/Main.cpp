#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"
#include "Window.h"

using namespace std;

int main()
{
	Window window;
	StateInput& stateinput = StateInput::getInstance();
	StateManager& statemanager = StateManager::getInstance();			

	statemanager.updateState();
	statemanager.renderState();
	
	
	return 0;
}
