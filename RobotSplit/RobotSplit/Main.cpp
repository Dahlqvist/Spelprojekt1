#include <SFML\Graphics.hpp>
#include <iostream>

#include "StateInput.h"
#include "StateManager.h"

using namespace std;

int main()
{
	StateInput& stateinput = StateInput::getInstance();
	StateManager& statemanager = StateManager::getInstance();

	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split");

	statemanager.updateState();
	statemanager.renderState(sf::RenderWindow& window);
	

	return 0;
}