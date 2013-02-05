#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"

using namespace std;

int main()
{
	StateInput& stateinput = StateInput::getInstance();
	StateManager& statemanager = StateManager::getInstance();			

	statemanager.updateState();
	statemanager.renderState();
	
	
	return 0;
}
