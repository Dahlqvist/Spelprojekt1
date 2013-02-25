#include "UIText.h"
#include <SFML\Graphics.hpp>

UIText::UIText(std::string Name,std::string Default,bool Select,Color Back,Color Text,int Size)
	:UIItem(Name,Select),mBack(Back),mTextColor(Text),mSize(Size)
{
	setDefault(Default);
	mLineSwitch.setLimit(0.5);
	mEnter.setCurrentPosition(2);
}


UIText::~UIText(void)
{
}

void	UIText::draw(RenderWindow& window,Vector2f	Position)
{
	sf::Text	renderString;
	Uint8		alpha=255;
	if(!mChangeable)
	{
		alpha=100;
	}
	Color		temp(mTextColor);
	renderString.setColor(temp);
	renderString.setCharacterSize(mSize);
	renderString.setString(mName+": ");
	renderString.setPosition(Position);
	window.draw(renderString);
	Vector2f newPos=Position;
	newPos.x+=renderString.getGlobalBounds().width+10;
	renderString.setPosition(newPos);
	renderString.setString(mEnter.getString());
	sf::RectangleShape Back(Vector2f(renderString.getGlobalBounds().width+2,renderString.getGlobalBounds().height+5))
		,Frame(Vector2f(renderString.getGlobalBounds().width+1,renderString.getGlobalBounds().height+4))
		,Line(Vector2f(1.f,renderString.getCharacterSize()));
	Back.setFillColor(Color(mBack.r,mBack.g,mBack.b,alpha));
	Line.setFillColor(Color(0,0,0,255));
	Back.setPosition(renderString.getPosition());
	Line.setPosition(renderString.findCharacterPos(mEnter.getCurrentPosition()));
	window.draw(Back);
	window.draw(renderString);
	Frame.setFillColor(sf::Color::Transparent);
	Frame.setOutlineThickness(1);
	Frame.setOutlineColor(Color(0,0,0,255));
	Frame.setPosition(newPos);
	window.draw(Frame);
	if(mLineSwitch.isExpired())
	{
		mLineDraw=!mLineDraw;
		mLineSwitch.reset();
	}
	if(mLineDraw&&mSelected&&mChangeable)
	{
		window.draw(Line);
	}
}

void	UIText::handleEvent(const sf::Event& Current,Vector2f	Position)
{
	if(mChangeable)
	{
		switch(Current.type)
		{
		case sf::Event::EventType::TextEntered :
			if(Current.text.unicode>='0')
			{
				mEnter.insertCharacter(Current.text.unicode);
			}
			break;
		case sf::Event::EventType::KeyPressed :
			if(Current.key.code==sf::Keyboard::Left)
			{
				mEnter.setCurrentPosition(mEnter.getCurrentPosition()-1);
			}
			else if(Current.key.code==sf::Keyboard::Right)
			{
				mEnter.setCurrentPosition(mEnter.getCurrentPosition()+1);
			}
			else if(Current.key.code==sf::Keyboard::Back)
			{
				mEnter.deleteCharacter();
			}
			break;
		default:
			break;
		}
	}
}

void	UIText::setDefault(std::string&	Default)
{
	mEnter.clear();
	for(std::string::size_type i=0;i<Default.size();i++)
	{
		mEnter.insertCharacter(Default[i]);
	}
}

std::string	UIText::getString()
{
	return	mEnter.getString();
}

FloatRect	UIText::getHitBox(Vector2f	Position)const
{
	sf::Text	HitString;
	HitString.setCharacterSize(mSize);
	HitString.setString(mName+": ");
	Vector2f newPos=Position;
	newPos.x+=HitString.getGlobalBounds().width+10;
	HitString.setPosition(newPos);
	HitString.setString(mEnter.getString());
	return FloatRect(newPos,Vector2f(HitString.getGlobalBounds().width+2,HitString.getGlobalBounds().height+5));
}