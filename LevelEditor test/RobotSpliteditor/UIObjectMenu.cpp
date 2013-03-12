#include "UIObjectMenu.h"
#include "Platform.h"
#include "Trigger.h"
#include "DialogueBox.h"
#include "LaserHolder.h"
#include "LaserDeactivator.h"
#include "Meanix.h"
#include "MiniBot.h"
#include "Checkpoint.h"
#include <SFML\Graphics.hpp>

UIObjectMenu::UIObjectMenu(string Name,sf::Vector2f& Max,Toolbar* Holder,Color Back,int Size)
	:UIItem("z"+Name,true),mMaxSize(Max),mBackColor(Back),mSize(Size)
{
	mHolder=Holder;
	mBotRow=int(mMaxSize.y/64);
}


UIObjectMenu::~UIObjectMenu(void)
{
}

void	UIObjectMenu::draw(RenderWindow& window,sf::Vector2f Position)
{
	std::string	STRING(mName);
	STRING.erase(STRING.begin());
	sf::RectangleShape	BackGround;
	BackGround.setPosition(Position);
	BackGround.setFillColor(mBackColor);
	sf::Text	NAME(STRING);
	NAME.setPosition(Position);
	NAME.setCharacterSize(mSize);
	Position+=sf::Vector2f(0,NAME.getGlobalBounds().height);
	if(mSelected)
	{
		BackGround.setSize(mMaxSize+sf::Vector2f(0,NAME.getGlobalBounds().height));
		window.draw(BackGround);
		for(vector<int>::size_type i=0;i<mIcons.size();i++)
		{
			Vector2i	pos((i)%int(mMaxSize.x/64),((i)/int(mMaxSize.x/64)));
			if(pos.y<=mBotRow-1&&pos.y>=mBotRow-int(mMaxSize.y/64))
			{
				mIcons[i]->render(window,
				Vector2f(Position+
				Vector2f(64*pos.x,64*(pos.y-(mBotRow-int(mMaxSize.y/64)))
				)));
			}
		}
	}
	else
	{
		BackGround.setSize(sf::Vector2f(mMaxSize.x,NAME.getGlobalBounds().height+4));
		window.draw(BackGround);
	}
	window.draw(NAME);
}

void	UIObjectMenu::addIcon(UnitIcon	*Icon)
{
	mIcons.push_back(Icon);
}

FloatRect	UIObjectMenu::getHitBox(Vector2f Position)const
{
	std::string	STRING(mName);
	STRING.erase(STRING.begin());
	sf::Text	NAME(STRING);
	NAME.setPosition(Position);
	NAME.setCharacterSize(mSize);
	FloatRect RECT(Position,mMaxSize);
	if(!mSelected)
	{
		RECT.height=NAME.getGlobalBounds().height+4;
		RECT.width=mMaxSize.x;
	}
	return RECT;
}

void	UIObjectMenu::handleEvent(const sf::Event& Current,Vector2f	Position)
{
	sf::Text	NAME(mName);
	NAME.setPosition(Position);
	NAME.setCharacterSize(mSize);
	if(Current.type==sf::Event::EventType::MouseButtonPressed&&Current.mouseButton.button==sf::Mouse::Button::Left)
	{
		int i=0;
		for(IconVector::iterator it=mIcons.begin();it!=mIcons.end();it++)
		{
			Vector2i	pos((i)%int(mMaxSize.x/64),((i)/int(mMaxSize.x/64)));

			int	MaxRows=(mMaxSize.y/64);
			FloatRect	HITBOX=(*it)->getHitBox(Position+Vector2f(pos.x*64,(pos.y*64)+NAME.getGlobalBounds().height-((mBotRow-MaxRows)*64)));
			if(HITBOX.contains(Current.mouseButton.x,Current.mouseButton.y)
			&&pos.y>=mBotRow-int(mMaxSize.y/64))
			{
				if((*it)->getType()=="Player")
				{
					mHolder->setPlayer(new	Player(Vector2f(0,0)));
					mHolder->mChange=true;
				}
				else	
				{ 
					if((*it)->getType()=="Platform")
					{
						mHolder->setUnit(new Platform(Vector2f(0,0),(*it)->getSpriteName(),Vector2f(0,0),Vector2f(0,0)));
					}
					else if((*it)->getType()=="DialogueBox")
					{
						mHolder->setUnit(new DialogueBox(Vector2f(0,0),(*it)->getSpriteName(),"",true,true,"DialogueBox"));
					}
					else if((*it)->getType()=="Checkpoint")
					{
						mHolder->setUnit(new Checkpoint(Vector2f(0,0),Vector2f(64,64),Vector2f(64,64),new Animation((*it)->getSpriteName(),(*it)->getSpeed(),(*it)->getFrames())));
					}
					else if((*it)->getType()=="LaserHolder")
					{
						mHolder->setUnit(new LaserHolder(new Laser(Vector2f(0,0),"Blue",true,100,0),"LaserBlueId",Vector2f(200,300),Vector2f(-100,-100)));
					}
					else if((*it)->getType()=="Trigger")
					{
						mHolder->setUnit(new Trigger(Vector2f(0,0),Vector2f(0,0),Vector2f(0,0),(*it)->getType(),(*it)->getSpriteName(),0,""));
					}
					else if((*it)->getType()=="Meanix")
					{
						Player* play=0;
						if(mHolder->getPlayCont().isActive())
						{
							play = mHolder->getPlayCont().getObject();
						}
						else
						{
							play = new Player(Vector2f(0,0));
						}
						mHolder->setUnit(new Meanix(Vector2f(0,0),play));
					}
					else
					{
						if((*it)->getFrames()>1)
						{
							mHolder->setUnit(new Unit(Vector2f(0,0),(*it)->getType(),new Animation((*it)->getSpriteName(),(*it)->getSpeed(),(*it)->getFrames())));
						}
						else
						{
							mHolder->setUnit(new Unit(Vector2f(0,0),(*it)->getType(),(*it)->getSpriteName()));
						}
					}
					mHolder->mChange=true;
				}
				break;
			}
			i++;
			mSelected=false;
			mHolder->mChange=true;
		}
		if(!mHolder->mChange)
		{
			sf::FloatRect	RECT(Position,Vector2f(0,0));
			RECT.height=NAME.getGlobalBounds().height+4;
			RECT.width=mMaxSize.x;
			if(RECT.contains(Current.mouseButton.x,Current.mouseButton.y))
			{
				mSelected=false;
			}
			else
			{
				mSelected=true;
			}
		}
	}
	else if(Current.type==sf::Event::EventType::KeyPressed)
	{
		if(Current.key.code==sf::Keyboard::Up&&mBotRow>int(mMaxSize.y/64))
		{
			mBotRow--;
		}
		else if(Current.key.code==sf::Keyboard::Down&&mBotRow<int(mIcons.size()/2))
		{
			mBotRow++;
		}
	}
}