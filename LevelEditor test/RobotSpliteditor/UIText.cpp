#include "UIText.h"
#include <SFML\Graphics.hpp>

UIText::UIText(std::string Name,std::string Default,Color Back,Color Text,int Size)
	:UIItem(Name),mBack(Back),mTextColor(Text),mSize(Size)
{
	setDefault(Default);
	mLineSwitch.setLimit(0.5);
	mEnter.setCurrentPosition(2);
}


UIText::~UIText(void)
{
}

void	UIText::draw(RenderWindow& window,Vector2f	Position,Uint8	alpha)
{
	sf::Text	renderString;
	Color		temp(mTextColor);
	temp.a=alpha;
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
	Back.setFillColor(mBack);
	Line.setFillColor(Color(0,0,0,alpha));
	Back.setPosition(renderString.getPosition());
	Line.setPosition(renderString.findCharacterPos(mEnter.getCurrentPosition()));
	window.draw(Back);
	window.draw(renderString);
	Frame.setFillColor(sf::Color::Transparent);
	Frame.setOutlineThickness(1);
	Frame.setOutlineColor(Color(0,0,0,alpha));
	Frame.setPosition(newPos);
	window.draw(Frame);
	if(mLineSwitch.isExpired())
	{
		mLineDraw=!mLineDraw;
		mLineSwitch.reset();
	}
	if(mLineDraw&&mSelected)
	{
		window.draw(Line);
	}
}

void	UIText::handleEvent(Event&	Current)
{
	switch(Current.type)
	{
	case sf::Event::EventType::TextEntered :
		if(Current.text.unicode==sf::Keyboard::Key::Back)
		{
			mEnter.deleteCharacter();
		}
		else if(Current.text.unicode==sf::Keyboard::Key::Delete)
		{
			mEnter.setCurrentPosition(mEnter.getCurrentPosition()+1);
			mEnter.deleteCharacter();
		}
		else
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
		break;
	default:
		break;
	}
}

void	UIText::setDefault(std::string&	Default)
{
	while(mEnter.getLength()<0)
	{
		mEnter.deleteCharacter();
	}
	for(std::string::size_type i=0;i<Default.size();i++)
	{
		mEnter.insertCharacter(Default[i]);
	}
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