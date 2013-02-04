#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Level.h"
#include "Unit.h"
#include "TextField.h"

using namespace sf;
int main(int numArgs, char Args)
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split Editor");
//	Level level("Test.xml");
	TextField	MTEXT(Color(1,1,1,255));
	while(window.isOpen())
	{
		sf::Event CurrentEvent;
		while(window.pollEvent(CurrentEvent))
		{
			if(CurrentEvent.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			if(CurrentEvent.type ==	sf::Event::EventType::TextEntered)
			{
				std::cout<<int(CurrentEvent.text.unicode)<<std::endl;
				MTEXT.insertCharacter(CurrentEvent.text.unicode);
			}
			if(CurrentEvent.type ==	sf::Event::EventType::KeyReleased)
			{
				if(CurrentEvent.key.code==sf::Keyboard::Left)
				{
					int temp=MTEXT.getCurrentPosition();
					temp--;
					MTEXT.setCurrentPosition(temp);
				}
				if(CurrentEvent.key.code==sf::Keyboard::Right)
				{
					MTEXT.setCurrentPosition(MTEXT.getCurrentPosition()+1);
				}
			}
		}
		window.clear(Color(100,100,100,255));
		window.draw(sf::Text(MTEXT.getString()));
//		std::cout<<MTEXT.getCurrentPosition()<<std::endl;
/*		UnitVector Units = level.getObjects();
		for(UnitVector::size_type i=0;i < Units.size();i++)
		{
			window.draw(Units[i]->getSprite());
		}
*/		window.display();
	}
	return EXIT_SUCCESS;
}