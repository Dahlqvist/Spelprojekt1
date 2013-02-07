#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "LevelConstructor.h"
#include "Unit.h"
#include "Player.h"
#include "TextField.h"
#include <SFML/Window/WindowHandle.hpp>
using namespace sf;


int main(int numArgs, char Args)
{
	sf::WindowHandle	s;
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default);
	s=window.getSystemHandle();
	Vector2f	AR(5,3);
	LevelConstructor level("Test.xml");
	TextField	MTEXT(Color(1,1,1,255));
	bool once=false;
	sf::View	CurrView(window.getDefaultView());
	while(window.isOpen())
	{
		sf::Event CurrentEvent;
		while(window.pollEvent(CurrentEvent))
		{
			if(CurrentEvent.type == sf::Event::EventType::Closed)
			{
				window.close();
			}
			else if(CurrentEvent.type==sf::Event::EventType::Resized)
			{
				float	xDif,yDif;
				xDif=CurrView.getSize().x/window.getSize().x;
				yDif=CurrView.getSize().y/window.getSize().y;
				CurrView.setSize(window.getSize().x,window.getSize().y);
				if(xDif<yDif)
				{
					CurrView.zoom(yDif);
				}
				else
				{
					CurrView.zoom(xDif);
				}
				window.setView(CurrView);
			}
			else if(CurrentEvent.type == sf::Event::EventType::MouseButtonPressed)
			{
				Vector2f point(CurrentEvent.mouseButton.x,CurrentEvent.mouseButton.y);
				std::cout<<"MousePosition: "<<point.y<<","<<point.y<<std::endl;
				UnitVector Units = level.getObjects();
				for(UnitVector::size_type i=0;i < Units.size();i++)
				{
					sf::FloatRect hitbox(Units[i]->getSprite().getGlobalBounds());
					if(hitbox.contains(point))
					{
						if(CurrentEvent.mouseButton.button==sf::Mouse::Button::Right)
						{
							level.deleteItem(i);
						}
					}
				}
				cout<<"Hitscan end!"<<endl;
			}
			else if(CurrentEvent.type ==	sf::Event::EventType::TextEntered)
			{
				std::cout<<int(CurrentEvent.text.unicode)<<std::endl;
				MTEXT.insertCharacter(CurrentEvent.text.unicode);
			}
			else if(CurrentEvent.type ==	sf::Event::EventType::KeyReleased)
			{
				if(CurrentEvent.key.code==sf::Keyboard::Left)
				{
					int temp=MTEXT.getCurrentPosition();
					temp--;
					MTEXT.setCurrentPosition(temp);
				}
				else if(CurrentEvent.key.code==sf::Keyboard::Right)
				{
					MTEXT.setCurrentPosition(MTEXT.getCurrentPosition()+1);
				}
			}
		}
		window.clear(Color(100,100,100,255));
//		std::cout<<MTEXT.getCurrentPosition()<<std::endl;
		UnitVector Units = level.getObjects();
		level.getPlayer()->draw(window);
		if(!once)
		{
			level.getPlayer()->update();
			once=true;
		}
		for(UnitVector::size_type i=0;i < Units.size();i++)
		{
				window.draw(Units[i]->getSprite());
		}
		window.draw(sf::Text(MTEXT.getString()));
		window.display();
	}
	return EXIT_SUCCESS;
}