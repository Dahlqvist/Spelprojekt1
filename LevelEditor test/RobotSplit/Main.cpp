#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "LevelConstructor.h"
#include "Unit.h"
#include "Player.h"
#include "TextField.h"
#include <SFML/Window/WindowHandle.hpp>
using namespace sf;

void	operator delete(void* ptr)
{
	(free)(ptr);
	ptr=nullptr;
}

template	<class	T>
class	Container
{
public:
	Container()
		:activated(false)
	{
	}
	Container(T*	input)
		:activated(true)
	{
		THIS=input;
	}
	bool	isActive()const
	{
		return	activated;
	}
	bool	fromLevel()const
	{
		return	inLevel;
	}
	T*		getObject()
	{
		return THIS;
	}
	void	deletePtr()
	{	
		activated=false;
		delete THIS;
	}
	void	unInitiate()
	{
		activated=false;
		THIS=0;
	}
	void	setPtr(T*	NEW,bool fromLevel=false)
	{
		if(isActive())
		{
			delete	THIS;
		}
		inLevel=fromLevel;
		activated=true;
		THIS=NEW;
	}
private:
	T*	THIS;
	bool	activated,inLevel;
};

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;


int main(int numArgs, char Args)
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default);
	LevelConstructor level("Test.xml");
	TextField	MTEXT(Color(1,1,1,255));
	bool once=false, PLAYER=false;
	sf::View	CurrView(window.getDefaultView()),miniView(window.getDefaultView());
	CurrView.setViewport(FloatRect(Vector2f(0,0.1),Vector2f(0.9,0.9)));
	miniView.setViewport(FloatRect(Vector2f(0.9,0),Vector2f(0.1,0.1)));
//	miniView.zoom(2.56);
	UnitContainer	selected;
	while(window.isOpen())
	{
		window.setView(CurrView);
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
				if(xDif<yDif&&xDif!=1)
				{
					CurrView.zoom(yDif);
				}
				else
				{
					CurrView.zoom(xDif);
				}
				window.setView(CurrView);
			}
			else if(CurrentEvent.type == sf::Event::MouseMoved)
			{
				if(selected.isActive())
				{
					Vector2f temp=window.convertCoords(Vector2i(CurrentEvent.mouseMove.x,CurrentEvent.mouseMove.y));
					selected.getObject()->setPosition(temp);
				}
			}
			else if(CurrentEvent.type == sf::Event::EventType::MouseButtonPressed)
			{
				UnitVector Units = level.getObjects();
				Vector2f point=window.convertCoords(Vector2i(CurrentEvent.mouseButton.x,CurrentEvent.mouseButton.y));
				std::cout<<"MousePosition: "<<point.y<<","<<point.y<<std::endl;
				if(CurrentEvent.mouseButton.button==sf::Mouse::Button::Middle)
				{
					if(!selected.isActive())
					{
						selected.setPtr(new Unit(point,"Door","Exit"));
					}
				}
				else if(CurrentEvent.mouseButton.button==sf::Mouse::Button::Right)
				{
					if(!selected.isActive())
					{
						for(UnitVector::size_type i=0;i < Units.size();i++)
						{
							sf::FloatRect hitbox(Units[i]->getSprite().getGlobalBounds());
							if(hitbox.contains(point))
							{
								level.deleteItem(Units[i]);
								break;
							}
						}
					}
					else
					{
						level.deleteItem(selected.getObject());
						selected.unInitiate();
					}
				}
	
				else	if(CurrentEvent.mouseButton.button==sf::Mouse::Button::Left)
				{
					if(!selected.isActive())
					{
						for(UnitVector::size_type i=0;i < Units.size();i++)
						{
							sf::FloatRect hitbox(Units[i]->getSprite().getGlobalBounds());
							if(hitbox.contains(point))
							{
								selected.setPtr(level.accessObjects()[i],true);
								break;
							}
						}
					}
					else
					{
						if(!selected.fromLevel())
						{
							level.addUnit(selected.getObject());
						}
						selected.unInitiate();
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
		window.setView(CurrView);
		if(!once)
		{
			level.getPlayer()->update();
			once=true;
		}
		level.getPlayer()->draw(window);
		for(UnitVector::size_type i=0;i < Units.size();i++)
		{
				window.draw(Units[i]->getSprite());
		}
		if(selected.isActive())
		{
			window.draw(selected.getObject()->getSprite());
		}
		window.draw(sf::Text(MTEXT.getString()));
		window.setView(miniView);
		level.getPlayer()->draw(window);
		for(UnitVector::size_type i=0;i < Units.size();i++)
		{
				window.draw(Units[i]->getSprite());
		}
		if(selected.isActive()&&!selected.fromLevel())
		{
			window.draw(selected.getObject()->getSprite());
		}
		window.display();
	}
	return EXIT_SUCCESS;
}