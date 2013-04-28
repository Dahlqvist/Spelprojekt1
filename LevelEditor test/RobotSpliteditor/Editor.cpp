#include "Editor.h"
#include "DialogueBox.h"
#include "Background.h"
#include "LaserHolder.h"
#include "DialogueBox.h"
#include "LaserDeactivator.h"
#include "Trigger.h"
#include "Platform.h"
using namespace sf;



Editor::Editor(void)
	:mWindow(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default),mLevel("Load/Bana6.xml"),mCurrView(mWindow.getDefaultView()),
	mLevelTool(&mLevel),mMouseHoldTimer(0.2f),mOpen(true)
{
	Vector2f	size(mTools.getPosition().x/mWindow.getSize().x,mTools.getPosition().x/mWindow.getSize().x);
	float		mjao=float(mLevelTool.getSize().y);
	Vector2f	position(0,float(float(mLevelTool.getSize().y)/float(mWindow.getSize().y)));
	mCurrView.setViewport(FloatRect(position,size));
	mLevel.getPlayer()->setTogether(true);
	mLevel.getPlayer()->setHeadless(false);
	mTools.setTargets(mLevel);
}
Editor::Editor(std::string loadlevel)
	:mWindow(sf::VideoMode(1280, 768), "Robot split Editor",sf::Style::Default),mLevel(),mCurrView(mWindow.getDefaultView()),
	mLevelTool(&mLevel),mMouseHoldTimer(0.2f),mOpen(true)
{
	if(!mLevel.loadNewLevel(loadlevel))
	{
		mLevel.loadNewLevel("Load/Bana6.xml");
	}
	Vector2f	size(mTools.getPosition().x/mWindow.getSize().x,mTools.getPosition().x/mWindow.getSize().x);
	float		mjao=float(mLevelTool.getSize().y);
	Vector2f	position(0,float(float(mLevelTool.getSize().y)/float(mWindow.getSize().y)));
	mCurrView.setViewport(FloatRect(position,size));
	mLevel.getPlayer()->setTogether(true);
	mLevel.getPlayer()->setHeadless(false);
	mTools.setTargets(mLevel);
}

Editor::~Editor(void)
{
}

void	Editor::run()
{
	bool once=false, PLAYER=false;
	while(mOpen)
	{
		mWindow.setView(mCurrView);
		sf::Event CurrentEvent;
		while(mWindow.pollEvent(CurrentEvent))
		{
			eventHandler(CurrentEvent);
		}
		renderLevel(mCurrView);
		mTools.render(this);
		mLevelTool.render(mWindow);
		mWindow.display();
		mWindow.clear(Color(100,100,100,255));
	}
}

void	Editor::renderLevel(View& Target)
{
	mWindow.setView(mWindow.getDefaultView());
	UnitVector Units = mLevel.getObjects();
	mWindow.setView(Target);
	for(int i=0;i<mLevel.getBackground().size();i++)
	{
		mWindow.draw(mLevel.getBackground()[i]->draw());
	}
	if(mLevel.ifPlayerExist())
	{
		mLevel.getPlayer()->draw(mWindow, false);
	}
	for(UnitVector::size_type i=0;i < Units.size();i++)
	{
		if(dynamic_cast<Laser*>(mLevel.getObjects()[i])!=0)
		{
			dynamic_cast<Laser*>(mLevel.getObjects()[i])->mLength=dynamic_cast<Laser*>(mLevel.getObjects()[i])->mMaxLength;
		}
		else if(dynamic_cast<DialogueBox*>(mLevel.getObjects()[i])!=0)
		{
			Uint8 alpha=200;
			if(dynamic_cast<DialogueBox*>(mLevel.getObjects()[i])->getVisible())
			{
				alpha=255;
			}
			dynamic_cast<DialogueBox*>(mLevel.getObjects()[i])->forceAlpha(alpha);
		}
		if(Units[i]!=mSelectedUnit.getObject())
		{
			mWindow.draw(Units[i]->getSprite());
		}
	}
	if(mSelectedUnit.isActive())
	{
		if(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())!=0)
		{
			dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->mLength=dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getLength();
			mWindow.draw(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getSprite());
		}
		else if(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())!=0)
		{
			Uint8 alpha=255;
			if(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getFadeIn())
			{
				alpha=200;
			}
			dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->forceAlpha(alpha);
		}
		mWindow.draw(mSelectedUnit.getObject()->getSprite());		
	}
	if(mSelectedPlayer.isActive()&&mSelectedPlayer.getObject()!=mLevel.getPlayer())
	{
		mSelectedPlayer.getObject()->draw(mWindow, false);		
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
		mOpen=false;
		break;
	case sf::Event::EventType::Resized:
		if(mWindow.getSize().x<500)
		{
			mWindow.setSize(Vector2u(600,mWindow.getSize().y));
		}
		if(mWindow.getSize().y<600)
		{
			mWindow.setSize(Vector2u(mWindow.getSize().x,600));
		}
		mTools.resize(mWindow);
		mLevelTool.resize(mWindow);
		mCurrView=sf::View(Vector2f(mWindow.getSize().x/2,mWindow.getSize().y/2),Vector2f(mWindow.getSize()));
		mCurrView.setViewport(sf::FloatRect(Vector2f(0,float(float(mLevelTool.getSize().y)/float(mWindow.getSize().y))),
			Vector2f(mTools.getPosition().x/mWindow.getSize().x,mTools.getPosition().x/mWindow.getSize().x)));
//		mCurrView.zoom(1+(1-mTools.getPosition().x/mWindow.getSize().x));
		break;
	case sf::Event::MouseMoved:
		temp=mWindow.convertCoords(Vector2i(Current.mouseMove.x,Current.mouseMove.y));
		if(mLevelTool.getSnap()>1)
		{
			temp=Vector2f(mLevelTool.getSnap()*int(temp.x/mLevelTool.getSnap()),mLevelTool.getSnap()*int(temp.y/mLevelTool.getSnap()));
		}
		point	=Vector2f(Current.mouseMove.x,Current.mouseMove.y);
		if(!mTools.checkHit(point)||!mLevelTool.checkHit(point))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				if(!mSelectedUnit.isActive()&&!mSelectedPlayer.isActive())
				{
					for(UnitVector::size_type i=0;i < mLevel.getObjects().size();i++)
					{
						sf::FloatRect hitbox(mLevel.getObjects()[i]->getSprite().getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mTools.unIniUnit();
							mTools.unIniPlayer();
							if(dynamic_cast<Laser*>(mLevel.getObjects()[i])!=0)
							{
								for(UnitVector::size_type j=0;j < mLevel.getObjects().size();j++)
								{
									if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])!=0)
									{
										if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])->mLaser==mLevel.getObjects()[i])
										{
											mLevel.deleteItem(mLevel.getObjects()[j]);
											break;
										}
									}
								}
							}
							mLevel.deleteItem(mLevel.getObjects()[i]);
							mTools.setTargets(mLevel);
							break;
						}
					}
					if(mLevel.ifPlayerExist())
					{
						sf::FloatRect hitbox(mLevel.getPlayer()->
							getCollisionSprite()[1]->getGlobalBounds());
						hitbox.height+=mLevel.getPlayer()->
							getCollisionSprite()[0]->getGlobalBounds().height;
						if(hitbox.contains(temp))
						{
							mTools.unIniUnit();
							mTools.unIniPlayer();
							mLevel.deletePlayer();
						}
					}
				}
				else
				{
					deleteSelected();
				}
				mTools.setTargets(mLevel);
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
		}
		break;
	case sf::Event::EventType::MouseButtonPressed:
		temp=	mWindow.convertCoords(Vector2i(Current.mouseButton.x,Current.mouseButton.y));
		if(mLevelTool.getSnap()>1)
		{
			temp=Vector2f(mLevelTool.getSnap()*int(temp.x/mLevelTool.getSnap()),mLevelTool.getSnap()*int(temp.y/mLevelTool.getSnap()));
		}
		point=	Vector2f(Current.mouseButton.x,Current.mouseButton.y);
		std::cout<<"MousePosition: "<<temp.y<<","<<temp.y<<std::endl;
		mTools.setSelect(mTools.checkHit(point));
		mLevelTool.setSelect(mLevelTool.checkHit(point));
		if(mTools.isSelected())
		{
			mSelectedUnit.unInitiate();
			mSelectedPlayer.unInitiate();
			mTools.eventHandle(Current);
		}
		else if(mLevelTool.isSelected())
		{
			mSelectedUnit.unInitiate();
			mSelectedPlayer.unInitiate();
			mTools.unIniUnit();
			mTools.unIniPlayer();
			mLevelTool.eventHandle(Current);
		}
		else
		{
			if(Current.mouseButton.button==sf::Mouse::Button::Right)
			{
				if(!mSelectedUnit.isActive()&&!mSelectedPlayer.isActive())
				{
					for(UnitVector::size_type i=0;i < mLevel.getObjects().size();i++)
					{
						sf::FloatRect hitbox(mLevel.getObjects()[i]->getSprite().getGlobalBounds());
						if(hitbox.contains(temp))
						{
							mTools.unIniUnit();
							mTools.unIniPlayer();
							if(dynamic_cast<Laser*>(mLevel.getObjects()[i])!=0)
							{
								for(UnitVector::size_type j=0;j < mLevel.getObjects().size();j++)
								{
									if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])!=0)
									{
										if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])->mLaser==mLevel.getObjects()[i])
										{
											mLevel.deleteItem(mLevel.getObjects()[j]);
											break;
										}
									}
								}
							}
							mLevel.deleteItem(mLevel.getObjects()[i]);
							mTools.setTargets(mLevel);
							break;
						}
					}
					if(mLevel.ifPlayerExist())
					{
						sf::FloatRect hitbox(mLevel.getPlayer()->
							getCollisionSprite()[1]->getGlobalBounds());
						hitbox.height+=mLevel.getPlayer()->
							getCollisionSprite()[0]->getGlobalBounds().height;
						if(hitbox.contains(temp))
						{
							mTools.unIniUnit();
							mTools.unIniPlayer();
							mLevel.deletePlayer();
						}
					}
				}
				else
				{
					deleteSelected();
				}
				mTools.setTargets(mLevel);
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
							mMouseHoldTimer.reset();
							if(dynamic_cast<Laser*>(mLevel.getObjects()[i])!=0)
							{
								for(UnitVector::size_type j=0;j < mLevel.getObjects().size();j++)
								{
									if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])!=0)
									{
										if(dynamic_cast<LaserHolder*>(mLevel.getObjects()[j])->mLaser==mLevel.getObjects()[i])
										{
											mSelectedUnit.setPtr(mLevel.accessObjects()[j],mLevel.accessObjects()[j]->getPosition(),Vector2f(temp-mLevel.accessObjects()[j]->getPosition()),true);
											mTools.setUnit(mSelectedUnit.getObject());
										}
									}
								}
							}
							else
							{
								mSelectedUnit.setPtr(mLevel.accessObjects()[i],mLevel.accessObjects()[i]->getPosition(),Vector2f(temp-mLevel.accessObjects()[i]->getPosition()),true);
								mTools.setUnit(mSelectedUnit.getObject());
							}
							break;
						}
					}
					if(mLevel.ifPlayerExist())
					{
						sf::FloatRect hitbox(mLevel.getPlayer()->
							getCollisionSprite()[1]->getGlobalBounds());
						hitbox.height+=mLevel.getPlayer()->
							getCollisionSprite()[0]->getGlobalBounds().height;
						if(hitbox.contains(temp))
						{
							mMouseHoldTimer.reset();
							mSelectedPlayer.setPtr(mLevel.getPlayer(),mLevel.getPlayer()->getCollisionSprite()[0]->getPosition(),temp-mLevel.getPlayer()->getCollisionSprite()[0]->getPosition(),true);
							mTools.setPlayer(mSelectedPlayer.getObject());
						}
					}
				}
				else
				{
					//Copying the unit with shift
					Unit*	copy=0;
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
					{
						if(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())!=0)
						{
							copy=new LaserHolder(new Laser(
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getPosition(),
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getId(),
								true,
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getLength(),
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getRotation()
								),
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getId(),
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getSize(),
								dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getOffset());
						}
						else if(dynamic_cast<LaserDeactivator*>(mSelectedUnit.getObject())!=0)
						{
							copy=new LaserDeactivator(new Trigger(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getPosition(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSize(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getOffset(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getId(),
								TextureManager::getSpriteName(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSprite()),
								0,
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSound())
								,dynamic_cast<LaserDeactivator*>(mSelectedUnit.getObject())->getRotation());
						}
						else if(dynamic_cast<Trigger*>(mSelectedUnit.getObject())!=0)
						{
							copy=new Trigger(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getPosition(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSize(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getOffset(),
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getId(),
								TextureManager::getSpriteName(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSprite()),
								0,
								dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSound());
						}
						else if(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())!=0)
						{
							copy=new DialogueBox(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getPosition(),
								TextureManager::getSpriteName(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getSprite()),
								dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getText().getString().toAnsiString(),
								dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getFadeIn(),
								dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getVisible(),
								dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getId()
								);
						}
						else if(dynamic_cast<Platform*>(mSelectedUnit.getObject())!=0)
						{
							if(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getLives()>0)
							{
								copy=new Platform(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getLives(),
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getPosition(),
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSize(),
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getOffset(),
									TextureManager::getSpriteName(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSprite())
									);
							}
							else
							{
								copy=new Platform(
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getPosition(),
									TextureManager::getSpriteName(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSprite()),
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSize(),
									dynamic_cast<Platform*>(mSelectedUnit.getObject())->getOffset()
									);
							}
								
						}
						else if(dynamic_cast<Unit*>(mSelectedUnit.getObject())!=0)
						{
							Unit temp=*dynamic_cast<Unit*>(mSelectedUnit.getObject());
							copy=new Unit(temp);
						}
					}
					if(mSelectedUnit.isActive())
					{
						if(collide(mSelectedUnit))
						{
							mSelectedUnit.getObject()->setPosition(mSelectedUnit.getOriginal());
							if(!mSelectedUnit.fromLevel())
							{
								mSelectedUnit.deletePtr();
								mTools.unIniUnit();
							}
						}
						else
						{
							if(!mSelectedUnit.fromLevel())
							{
								if(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())!=0)
								{
									mLevel.addUnit(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser());
								}
								mLevel.addUnit(mSelectedUnit.getObject());
								mTools.setTargets(mLevel);
							}
							mSelectedUnit.unInitiate();
						}
					}
					else
					{
						if(collide(mSelectedPlayer))
						{
							Vector2f	temp=mSelectedPlayer.getOriginal();
							mSelectedPlayer.getObject()->forceMove(0,temp-(mSelectedPlayer.getObject()->getCollisionSprite()[0]->getPosition())+sf::Vector2f(0,2));
							mSelectedPlayer.getObject()->forceMove(0,Vector2f(0,-4));
							mSelectedPlayer.getObject()->update();
							if(!mSelectedPlayer.fromLevel())
							{
								mSelectedPlayer.deletePtr();
								mTools.unIniPlayer();
							}
						}
						else
						{
							if(!mSelectedPlayer.fromLevel())
							{
								mLevel.addPlayer(mSelectedPlayer.getObject());
							}
						}
						mSelectedPlayer.unInitiate();
					}
					if(copy!=0)
					{
						mSelectedUnit.setPtr(copy);
						mTools.setUnit(copy);
					}
				}
			}
		}
		cout<<"Hitscan end!"<<endl;
		break;
	case sf::Event::MouseButtonReleased:
		if(mMouseHoldTimer.isExpired()&&!mTools.isSelected()&&!mLevelTool.isSelected())
		{
			if(mSelectedUnit.isActive())
			{
				Unit*	copy=0;
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)||sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
				{
					if(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())!=0)
					{
						copy=new LaserHolder(new Laser(
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getPosition(),
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getId(),
							true,
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getLength(),
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser()->getRotation()
							),
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getId(),
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getSize(),
							dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getOffset());
					}
					else if(dynamic_cast<LaserDeactivator*>(mSelectedUnit.getObject())!=0)
					{
						copy=new LaserDeactivator(new Trigger(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getPosition(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSize(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getOffset(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getId(),
							TextureManager::getSpriteName(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSprite()),
							0,
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSound())
							,dynamic_cast<LaserDeactivator*>(mSelectedUnit.getObject())->getRotation());
					}
					else if(dynamic_cast<Trigger*>(mSelectedUnit.getObject())!=0)
					{
						copy=new Trigger(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getPosition(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSize(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getOffset(),
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getId(),
							TextureManager::getSpriteName(dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSprite()),
							0,
							dynamic_cast<Trigger*>(mSelectedUnit.getObject())->getSound());
					}
					else if(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())!=0)
					{
						copy=new DialogueBox(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getPosition(),
							TextureManager::getSpriteName(dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getSprite()),
							dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getText().getString().toAnsiString(),
							dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getFadeIn(),
							dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getVisible(),
							dynamic_cast<DialogueBox*>(mSelectedUnit.getObject())->getId()
							);
					}
					else if(dynamic_cast<Platform*>(mSelectedUnit.getObject())!=0)
					{
						if(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getLives()>0)
						{
							copy=new Platform(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getLives(),
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getPosition(),
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSize(),
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getOffset(),
								TextureManager::getSpriteName(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSprite())
								);
						}
						else
						{
							copy=new Platform(
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getPosition(),
								TextureManager::getSpriteName(dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSprite()),
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getSize(),
								dynamic_cast<Platform*>(mSelectedUnit.getObject())->getOffset()
								);
						}
								
					}
					else if(dynamic_cast<Unit*>(mSelectedUnit.getObject())!=0)
					{
						Unit temp=*dynamic_cast<Unit*>(mSelectedUnit.getObject());
						copy=new Unit(temp);
					}
				}
				if(collide(mSelectedUnit))
				{
					mSelectedUnit.getObject()->setPosition(mSelectedUnit.getOriginal());
					if(!mSelectedUnit.fromLevel())
					{
						mSelectedUnit.deletePtr();
						mTools.unIniUnit();
					}
				}
				else if(!mSelectedUnit.fromLevel())
				{
					mLevel.addUnit(mSelectedUnit.getObject());
					mTools.setTargets(mLevel);
				}
				mSelectedUnit.unInitiate();
				if(copy!=0)
				{
					mSelectedUnit.setPtr(copy);
					mTools.setUnit(copy);
				}
			}
			else if(mSelectedPlayer.isActive())
			{
				if(collide(mSelectedPlayer))
				{
					Vector2f	temp=mSelectedPlayer.getOriginal();
					mSelectedPlayer.getObject()->forceMove(0,temp-(mSelectedPlayer.getObject()->getCollisionSprite()[0]->getPosition())+sf::Vector2f(0,2));
					mSelectedPlayer.getObject()->forceMove(0,Vector2f(0,-4));
					mSelectedPlayer.getObject()->update();
					if(!mSelectedPlayer.fromLevel())
					{
						mSelectedPlayer.deletePtr();
						mTools.unIniPlayer();
					}
				}
				mSelectedPlayer.unInitiate();
			}
		}
		mMouseHoldTimer.reset();
		break;
	case sf::Event::EventType::KeyReleased:
		if(mTools.isSelected())
		{
			mTools.eventHandle(Current);
		}
		else if(mLevelTool.isSelected())
		{
			mLevelTool.eventHandle(Current);
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
		if(mTools.isSelected())
		{
			mTools.eventHandle(Current);
		}
		else if(mLevelTool.isSelected())
		{
			mLevelTool.eventHandle(Current);
		}
		break;
	}
}

bool	Editor::collide(UnitContainer&	Other)
{
	for(UnitVector::iterator it=mLevel.accessObjects().begin();it!=mLevel.accessObjects().end();it++)
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
		sf::FloatRect hitbox(mLevel.getPlayer()->
		getCollisionSprite()[1]->getGlobalBounds());
		hitbox.height+=mLevel.getPlayer()->
		getCollisionSprite()[0]->getGlobalBounds().height;
		return	hitbox.intersects(Other.getObject()->getSprite().getGlobalBounds());
	}
	return false;
}

bool	Editor::collide(PlayerContainer&	Other)
{
	sf::FloatRect hitbox(Other.getObject()->
		getCollisionSprite()[1]->getGlobalBounds());
	hitbox.height+=Other.getObject()->
		getCollisionSprite()[0]->getGlobalBounds().height;
	for(UnitVector::iterator it=mLevel.accessObjects().begin();it!=mLevel.accessObjects().end();it++)
	{
		if(hitbox.intersects((*it)->getSprite().getGlobalBounds())
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

void	Editor::setPlayer(PlayerContainer&	Cont)
{
	if(Cont.isActive())
	{
		mSelectedPlayer.unInitiate();
		mSelectedPlayer.setPtr(Cont.getObject());
		mSelectedUnit.unInitiate();
	}
}

void	Editor::setUnit(UnitContainer&	Cont)
{
	if(Cont.isActive())
	{
		mSelectedUnit.unInitiate();
		mSelectedUnit.setPtr(Cont.getObject());
		mSelectedPlayer.unInitiate();
	}
}

void	Editor::deleteSelected()
{
	if(mSelectedPlayer.isActive())
	{
		mTools.unIniUnit();
		mTools.unIniPlayer();
		mLevel.deletePlayer();
		mSelectedPlayer.unInitiate();
	}
	else
	{
		mTools.unIniUnit();
		mTools.unIniPlayer();
		if(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())!=0)
		{
			mLevel.deleteItem(dynamic_cast<LaserHolder*>(mSelectedUnit.getObject())->getLaser());
		}
		mLevel.deleteItem(mSelectedUnit.getObject());
		mSelectedUnit.unInitiate();
	}
}