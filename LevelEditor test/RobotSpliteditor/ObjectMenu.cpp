#include "ObjectMenu.h"
#include <SFML\Graphics.hpp>

ObjectMenu::ObjectMenu(string Name,sf::Vector2f& Max,Toolbar* Holder,Color Back,int Size)
	:UIItem("z"+Name,true),mMaxSize(Max),mBackColor(Back),mSize(Size)
{
	mHolder=Holder;
	mBotRow=int(mMaxSize.y/64);
}


ObjectMenu::~ObjectMenu(void)
{
}

void	ObjectMenu::draw(RenderWindow& window,sf::Vector2f Position)
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
		for(int i=0;i<mIcons.size();i++)
		{
			Vector2i	pos((i)%int(mMaxSize.x/64),((i)/int(mMaxSize.x/64)));
			if(pos.y<=mBotRow&&pos.y>=mBotRow-int(mMaxSize.y/64))
			{
				mIcons[i]->render(window,
				Vector2f(Position+
				Vector2f(64*pos.x,64*pos.y
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

void	ObjectMenu::addIcon(UnitIcon	*Icon)
{
	mIcons.push_back(Icon);
}

FloatRect	ObjectMenu::getHitBox(Vector2f Position)const
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

void	ObjectMenu::handleEvent(const sf::Event& Current,Vector2f	Position)
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
			if((*it)->getHitBox(Position+Vector2f(pos.x*64,(pos.y*64)+NAME.getGlobalBounds().height)).contains(Current.mouseButton.x,Current.mouseButton.y))
			{
				if((*it)->getType()=="Player")
				{
					mHolder->setPlayer(new	Player(Vector2f(0,0)));
					mHolder->mChange=true;
				}
				else
				{ 
 					mHolder->setUnit(new Unit(Vector2f(0,0),(*it)->getType(),(*it)->getSpriteName()));
					mHolder->mChange=true;
				}
				break;
			}
			i++;
			mSelected=false;
		}
		if(!mHolder->mChange)
		{
			sf::FloatRect	RECT(Position,Vector2f(0,0));
			RECT.height=NAME.getGlobalBounds().height+4;
			RECT.width=mMaxSize.x;
			if(RECT.contains(Current.mouseButton.x,Current.mouseButton.y))
			{
				mSelected=!mSelected;
			}
		}
	}
}