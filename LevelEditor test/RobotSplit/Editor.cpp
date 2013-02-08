#include "Editor.h"

using namespace sf;



Editor::Editor(void)
	:
	window(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default),level("Test.xml")
{
}


Editor::~Editor(void)
{
}

void	Editor::run()
{
	TextField	MTEXT(Color(1,1,1,255));
	bool once=false, PLAYER=false;
	sf::View	CurrView(window.getDefaultView()),miniView(window.getDefaultView());
	CurrView.setViewport(FloatRect(Vector2f(0,0.1),Vector2f(0.9,0.9)));
//	miniView.setSize(200,1200);
//	miniView.zoom(20);
	Vector2f	Size(200.f/1280.f,120.f/768.f);
	miniView.setViewport(FloatRect(Vector2f(),Size));
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
					selected.getObject()->setPosition(temp-selected.getOffset());
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
								selected.setPtr(level.accessObjects()[i],level.accessObjects()[i]->getPosition(),Vector2f(point-level.accessObjects()[i]->getPosition()),true);
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
		renderLevel(CurrView);
		renderLevel(miniView);
		window.clear(Color(100,100,100,255));
		window.draw(sf::Text(MTEXT.getString()));
		window.display();
	}
}

void	Editor::renderLevel(View Target)
{
	UnitVector Units = level.getObjects();
	window.setView(Target);
	level.getPlayer()->draw(window);
	for(UnitVector::size_type i=0;i < Units.size();i++)
	{
		window.draw(Units[i]->getSprite());
	}
	if(selected.isActive()&&!selected.fromLevel())
	{
		window.draw(selected.getObject()->getSprite());		
	}
	window.setView(window.getDefaultView());
}