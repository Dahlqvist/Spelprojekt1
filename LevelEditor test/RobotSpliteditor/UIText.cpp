#include "UIText.h"
#include <SFML\Graphics.hpp>

UIText::UIText(std::string Name,Vector2f Position,std::string Default,Color Back,Color Text,int Size)
	:mName(Name),mPosition(Position),mBack(Back),mTextColor(Text),mSize(Size)
{
	for(std::string::size_type i=0;i<Default.size();i++)
	{
		mEnter.insertCharacter(Default[i]);
	}
}


UIText::~UIText(void)
{
}

void	UIText::draw(RenderWindow& window,Uint8	alpha)
{
	sf::Text	renderString;
	Color	temp(mTextColor);
	temp.a=alpha;
	renderString.setColor(temp);
	renderString.setCharacterSize(mSize);
	renderString.setString(mName+": ");
	renderString.setPosition(mPosition);
	window.draw(renderString);
	Vector2f newPos=mPosition;
	newPos.x+=renderString.getGlobalBounds().width;
	renderString.setPosition(newPos);
	renderString.setString(mEnter.getString());
	sf::RectangleShape Back(Vector2f(renderString.getGlobalBounds().width+1,renderString.getGlobalBounds().height+10));
	Back.setFillColor(mBack);
	Back.setPosition(renderString.getPosition());
	window.draw(Back);
	window.draw(renderString);
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