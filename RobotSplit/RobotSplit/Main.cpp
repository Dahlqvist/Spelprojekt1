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
int main()
{

	//window.setFramerateLimit(60);
	std::vector<Background*> BG;
	BG=level.getBackground();
	window.setKeyRepeatEnabled(false);

		if(renderGame)
		{
			for (vector<Background*>::size_type i=0; i<BG.size(); i++)
			{
				window.draw(BG[i]->draw());
				BG[i]->update();
			}

	
	while(true)
	{
		statemanager.updateState();
		statemanager.renderState();
	}

	
	return 0;
}
