#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "Unit.h"

int main(int numArgs, char Args)
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split Editor");
	Level level("Test.xml");
	while(window.isOpen())
	{
		sf::Event CurrentEvent;
		while(window.pollEvent(CurrentEvent))
		{
			if(CurrentEvent.type ==sf::Event::EventType::Closed)
			{
				window.close();
			}
		}
		window.clear();
		UnitVector Units = level.getObjects();
		for(UnitVector::size_type i=0;i < Units.size();i++)
		{
			window.draw(Units[i]->getSprite());
		}
		window.display();
	}
	return EXIT_SUCCESS;
}