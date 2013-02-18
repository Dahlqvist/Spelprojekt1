#include "Editor.h"

using namespace sf;



Editor::Editor(void)
	:mWindow(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default),mLevel("Test.xml"),mCurrView(mWindow.getDefaultView())
{
	Vector2f	size(mTools.getPosition().x/mWindow.getSize().x,mTools.getPosition().x/mWindow.getSize().x);
	mCurrView.setViewport(FloatRect(Vector2f(0,0.05),size));
}

Editor::~Editor(void)
{
}

void	Editor::run()
{
	bool once=false, PLAYER=false;
	while(mWindow.isOpen())
	{
		mWindow.setView(mCurrView);
		sf::Event CurrentEvent;
		while(mWindow.pollEvent(CurrentEvent))
		{
			eventHandler(CurrentEvent);
		}
		mWindow.clear(Color(100,100,100,255));
		renderLevel(mCurrView);
//		mWindow.draw(sf::Text(MTEXT.getString()));
		mTools.render(this);
		mWindow.display();
	}
}

void	Editor::renderLevel(View& Target)
{
	mWindow.setView(mWindow.getDefaultView());
	UnitVector Units = mLevel.getObjects();
	mWindow.setView(Target);
	if(mLevel.ifPlayerExist())
	{
		mLevel.getPlayer()->draw(mWindow);
	}
	for(UnitVector::size_type i=0;i < Units.size();i++)
	{
		if(Units[i]!=mSelectedUnit.getObject())
			mWindow.draw(Units[i]->getSprite());
	}
	if(mSelectedUnit.isActive())
	{
		mWindow.draw(mSelectedUnit.getObject()->getSprite());		
	}
	mWindow.setView(mWindow.getDefaultView());
}

void	Editor::eventHandler(const Event& Current)
{
	Vector2f	Size,temp,point;
	sf::FloatRect hitbox;
	switch(Current.type)
	{
	case sf::Event::EventType::Closed:
		mWindow.close();
		break;
	case sf::Event::EventType::Resized:
		Size.x=200.f/mWindow.getSize().x;
		Size.y=120.f/mWindow.getSize().y;
		miniView.setViewport(FloatRect(Vector2f(),Size));
		mWindow.setView(mCurrView);
		break;
	case sf::Event::MouseMoved:
		temp=mWindow.convertCoords(Vector2i(Current.mouseMove.x,Current.mouseMove.y));
		point	=Vector2f(Current.mouseMove.x,Current.mouseMove.y);
		mTools.setSelect(mTools.checkHit(point));
		if(mTools.isSelected())
		{
			if(mSelectedUnit.isActive())
			{
				mSelectedUnit.getObject()->setPosition(mSelectedUnit.getOriginal());
				if(!mSelectedUnit.fromLevel())
				{
					mSelectedUnit.deletePtr();
				}
					mSelectedUnit.unInitiate();
			}
			else if(mSelectedPlayer.isActive())
			{
				mSelectedPlayer.getObject()->forceMove(0,temp-(mSelectedPlayer.getOriginal()));
				mSelectedPlayer.getObject()->forceMove(0,Vector2f(0,-4));
				mSelectedPlayer.getObject()->update();
				if(!mSelectedPlayer.fromLevel())
				{
					mSelectedPlayer.deletePtr();
				}
				mSelectedPlayer.unInitiate();
			}
			mTools.eventHandle(Current);
		}
		else
		{
			if(mSelectedUnit.isActive())
			{
				mSelectedUnit.getObject()->setPosition(temp-mSelectedUnit.getOffset());
			}
			else if(mSelectedPlayer.isActive())
			{
				mSelectedPlayer.getObject()->forceMove(0,temp-(mSelectedPlayer.getObject()->getCollisionSprite()[0]->getPosition()+mSelectedPlayer.getOffset()));
				mSelectedPlayer.getObject()->forceMove(0,Vector2f(0,-4));
				mSelectedPlayer.getObject()->update();
			}
		}
		break;
	case sf::Event::EventType::MouseButtonPressed:
		temp=	mWindow.convertCoords(Vector2i(Current.mouseButton.x,Current.mouseButton.y));
		point=	Vector2f(Current.mouseButton.x,Current.mouseButton.y);
		std::cout<<"MousePosition: "<<temp.y<<","<<temp.y<<std::endl;
		mTools.setSelect(mTools.checkHit(point));
		if(mTools.isSelected())
		{
			mTools.eventHandle(Current);
		}
		else
		{
			if(Current.mouseButton.button==sf::Mouse::Button::Middle)
			{
				if(!mSelectedUnit.isActive())
				{
					mSelectedUnit.setPtr(new Unit(temp,"Door","Exit"));
					mTools.setUnit(mSelectedUnit.getObject());
				}
			}
			else if(Current.mouseButton.button==sf::Mouse::Button::Right)
			{
				if(!mSelectedUnit.isActive()&&!mSelectedPlayer.isActive())
				{
					for(UnitVector::size_type i=0;i < mLevel.getObjects().size();i++)
					{
						sf::FloatRect hitbox(mLevel.getObjects()[i]->getSprite().getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mLevel.deleteItem(mLevel.getObjects()[i]);
							break;
						}
					}
					if(mLevel.ifPlayerExist())
					{
						const sf::FloatRect hitbox(mLevel.getPlayer()->
							getCollisionSprite()[0]->getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mLevel.deletePlayer();
						}
					}
				}
				else
				{
					if(mSelectedPlayer.isActive())
					{
						mLevel.deletePlayer();
						mSelectedPlayer.unInitiate();
					}
					else
					{
						mLevel.deleteItem(mSelectedUnit.getObject());
						mSelectedUnit.unInitiate();
					}
				}
			}
	
			else	if(Current.mouseButton.button==sf::Mouse::Button::Left)
			{
				if(!mSelectedUnit.isActive()&&!mSelectedPlayer.isActive())
				{
					for(UnitVector::size_type i=0;i < mLevel.getObjects().size();i++)
					{
						hitbox=FloatRect(mLevel.getObjects()[i]->getSprite().getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mSelectedUnit.setPtr(mLevel.accessObjects()[i],mLevel.accessObjects()[i]->getPosition(),Vector2f(temp-mLevel.accessObjects()[i]->getPosition()),true);
							mTools.setUnit(mSelectedUnit.getObject());
							break;
						}
					}
					if(mLevel.ifPlayerExist())
					{
						const sf::FloatRect hitbox(mLevel.getPlayer()->
							getCollisionSprite()[0]->getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mSelectedPlayer.setPtr(mLevel.getPlayer(),mLevel.getPlayer()->getCollisionSprite()[0]->getPosition(),temp-mLevel.getPlayer()->getCollisionSprite()[0]->getPosition(),true);
							mTools.setPlayer(mSelectedPlayer.getObject());
						}
					}
				}
				else
				{
					if(mSelectedUnit.isActive())
					{
						if(collide(mSelectedUnit))
						{
							mSelectedUnit.getObject()->setPosition(mSelectedUnit.getOriginal());
							if(!mSelectedUnit.fromLevel())
							{
								mSelectedUnit.deletePtr();
							}
						}
						else if(!mSelectedUnit.fromLevel())
						{
							mLevel.addUnit(mSelectedUnit.getObject());
						}
						mSelectedUnit.unInitiate();
					}
					else
					{
						if(collide(mSelectedPlayer))
						{
							Vector2f	temp=mSelectedPlayer.getOriginal()-(mSelectedPlayer.getObject()->getCollisionSprite()[0]->getPosition()+mSelectedPlayer.getOffset());
							mSelectedPlayer.getObject()->forceMove(0,temp);
							mSelectedPlayer.getObject()->forceMove(0,Vector2f(0,-4));
							mSelectedPlayer.getObject()->update();
							if(!mSelectedPlayer.fromLevel())
							{
								mLevel.addPlayer(mSelectedPlayer.getObject());
							}
						}
						mSelectedPlayer.unInitiate();
					}
				}
			}
		}
		cout<<"Hitscan end!"<<endl;
		break;
	case sf::Event::EventType::TextEntered:
		mTools.eventHandle(Current);
	case sf::Event::EventType::KeyReleased:
		if(mTools.isSelected())
		{
			mTools.eventHandle(Current);
		}
		else
		{
			switch(Current.key.code)
			{
			case sf::Keyboard::Subtract:
				mCurrView.zoom(1.1);
				break;
			case sf::Keyboard::Add:
				mCurrView.zoom(0.9);
				break;
			case sf::Keyboard::Left:
				mCurrView.move(-10,0);
				break;
			case sf::Keyboard::Right:
				mCurrView.move(10,0);
				break;
			case sf::Keyboard::Up:
				mCurrView.move(0,-10);
				break;
			case sf::Keyboard::Down:
				mCurrView.move(0,10);
				break;
			}
		}
		break;
	default:
		mTools.eventHandle(Current);
		break;
	}
}

bool	Editor::collide(UnitContainer&	Other)
{
	for(UnitVector::iterator it=mLevel.accessObjects().begin();it+1!=mLevel.accessObjects().end();it++)
	{
		if(Other.getObject()!=(*it)
			&&Other.getObject()->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())
			&&Other.getObject()->isSolid()
			&&(*it)->isSolid())
		{
			 return true;
		}
	}
	
	if(mLevel.ifPlayerExist())
	{
		return	mLevel.getPlayer()->getCollisionSprite()[0]->getGlobalBounds().intersects(Other.getObject()->getSprite().getGlobalBounds());
	}
	return false;
}

bool	Editor::collide(PlayerContainer&	Other)
{
	for(UnitVector::iterator it=mLevel.accessObjects().begin();it+1!=mLevel.accessObjects().end();it++)
	{
		if(Other.getObject()->getCollisionSprite()[0]->getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds())
			&&(*it)->isSolid())
		{
			 return true;
		}
	}	
	return false;
}

RenderWindow&	Editor::getWindow()
{
	return	mWindow;
}