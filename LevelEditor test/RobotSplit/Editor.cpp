#include "Editor.h"

using namespace sf;



Editor::Editor(void)
	:
	window(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default),level("Test.xml"),
	MTEXT(Color(1,1,1,255)),CurrView(window.getDefaultView())
{
}


Editor::~Editor(void)
{
}

void	Editor::run()
{
	bool once=false, PLAYER=false;
	CurrView.setViewport(FloatRect(Vector2f(0,0.1),Vector2f(0.9,0.9)));
//	miniView.setSize(200,1200);
//	miniView.zoom(20);
	Vector2f	Size(200.f/window.getSize().x,120.f/window.getSize().y);
	miniView.setViewport(FloatRect(Vector2f(),Size));
	while(window.isOpen())
	{
		window.setView(CurrView);
		sf::Event CurrentEvent;
		while(window.pollEvent(CurrentEvent))
		{
			eventHandler(CurrentEvent);
		}
		window.clear(Color(100,100,100,255));
		renderLevel(CurrView);
		window.draw(sf::Text(MTEXT.getString()));
		window.display();
	}
}

void	Editor::renderLevel(View& Target)
{
	UnitVector Units = level.getObjects();
	window.setView(Target);
	level.getPlayer()->draw(window);
	for(UnitVector::size_type i=0;i < Units.size();i++)
	{
		if(Units[i]!=selected.getObject())
			window.draw(Units[i]->getSprite());
	}
	if(selected.isActive())
	{
		window.draw(selected.getObject()->getSprite());		
	}
	window.setView(window.getDefaultView());
}

void	Editor::eventHandler(const Event& Current)
{
	Vector2f	Size,temp,point;
	sf::FloatRect hitbox;
	switch(Current.type)
	{
	case sf::Event::EventType::Closed:
		window.close();
		break;
	case sf::Event::EventType::Resized:
		Size.x=200.f/window.getSize().x;
		Size.y=120.f/window.getSize().y;
		miniView.setViewport(FloatRect(Vector2f(),Size));
		window.setView(CurrView);
		break;
	case sf::Event::MouseMoved:
		if(selected.isActive())
		{
			temp=window.convertCoords(Vector2i(Current.mouseMove.x,Current.mouseMove.y));
			selected.getObject()->setPosition(temp-selected.getOffset());
		}
		break;
	case sf::Event::EventType::MouseButtonPressed:
		point=window.convertCoords(Vector2i(Current.mouseButton.x,Current.mouseButton.y));
		std::cout<<"MousePosition: "<<point.y<<","<<point.y<<std::endl;
		if(Current.mouseButton.button==sf::Mouse::Button::Middle)
		{
			if(!selected.isActive())
			{
				selected.setPtr(new Unit(point,"Door","Exit"));
			}
		}
		else if(Current.mouseButton.button==sf::Mouse::Button::Right)
		{
			if(!selected.isActive())
			{
				for(UnitVector::size_type i=0;i < level.getObjects().size();i++)
				{
					sf::FloatRect hitbox(level.getObjects()[i]->getSprite().getGlobalBounds());
					if(hitbox.contains(point))
					{
						level.deleteItem(level.getObjects()[i]);
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
	
		else	if(Current.mouseButton.button==sf::Mouse::Button::Left)
		{
			if(!selected.isActive())
			{
				for(UnitVector::size_type i=0;i < level.getObjects().size();i++)
				{
					hitbox=FloatRect(level.getObjects()[i]->getSprite().getGlobalBounds());
					if(hitbox.contains(point))
					{
						selected.setPtr(level.accessObjects()[i],level.accessObjects()[i]->getPosition(),Vector2f(point-level.accessObjects()[i]->getPosition()),true);
						break;
					}
				}
			}
			else
			{
				if(collide(selected))
				{
					selected.getObject()->setPosition(selected.getOriginal());
				}
				if(!selected.fromLevel())
				{
					level.addUnit(selected.getObject());
				}
				selected.unInitiate();
			}
		}
		cout<<"Hitscan end!"<<endl;
		break;
	case sf::Event::EventType::TextEntered:
		std::cout<<int(Current.text.unicode)<<std::endl;
		MTEXT.insertCharacter(Current.text.unicode);
		break;
	case sf::Event::EventType::KeyReleased:
		if(Current.key.code==sf::Keyboard::Left)
		{
			int temp=MTEXT.getCurrentPosition();
			temp--;
			MTEXT.setCurrentPosition(temp);
		}
		else if(Current.key.code==sf::Keyboard::Right)
		{
			MTEXT.setCurrentPosition(MTEXT.getCurrentPosition()+1);
		}
		break;
	}
}

bool	Editor::collide(UnitContainer&	Other)
{
	for(UnitVector::iterator it=level.accessObjects().begin();it+1!=level.accessObjects().end();it++)
	{
		if(Other.getObject()!=(*it)
			&&Other.getObject()->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())
			&&Other.getObject()->isSolid()
			&&(*it)->isSolid())
		{
			 return true;
		}
	}
	return	level.getPlayer()->getCollisionSprite()[0]->getGlobalBounds().intersects(Other.getObject()->getSprite().getGlobalBounds());
}