#include "UIButton.h"
#include <SFML\Graphics.hpp>

UIButton::UIButton(std::string	Name,int Size,Color Back,Color TextCol)
	:UIItem(Name,false),mBack(Back),mSize(Size),mTextCol(TextCol)
{
}


UIButton::~UIButton(void)
{
}

void	UIButton::draw(sf::RenderWindow&	WINDOW,sf::Vector2f	Position)
{
	sf::Text	RenderString(mName);
	RenderString.setPosition(Position);
	RenderString.setColor(sf::Color::Black);
	RenderString.setCharacterSize(mSize);
	sf::RectangleShape	Rect(Vector2f(RenderString.getGlobalBounds().width+2,RenderString.getGlobalBounds().height+5)),
		Frame(Vector2f(RenderString.getGlobalBounds().width+1,RenderString.getGlobalBounds().height+4));
	Rect.setFillColor(mBack);
	Frame.setFillColor(sf::Color::Transparent);
	Rect.setPosition(Position);
	Frame.setPosition(Position);
	Frame.setOutlineThickness(1);
	Frame.setOutlineColor(Color::Black);
	WINDOW.draw(Rect);
	WINDOW.draw(RenderString);
	WINDOW.draw(Frame);
}

FloatRect	UIButton::getHitBox(Vector2f Position)const
{
	sf::Text	RenderString(mName);
	RenderString.setPosition(Position);
	RenderString.setColor(sf::Color::Black);
	RenderString.setCharacterSize(mSize);
	sf::Rect<float>	Rect(Position,Vector2f(RenderString.getGlobalBounds().width+2,RenderString.getGlobalBounds().height+5));
	FloatRect Return(Rect);
	return Return;
}

void	UIButton::handleEvent(const sf::Event&,Vector2f)
{
	setSelect(false);
}