#ifndef	INC_UIDROP
#define	INC_UIDROP
#include"UIItem.h"
#include<map>
#include<string>
#include <SFML\Graphics.hpp>

using namespace std;

template<typename T>
class UIDrop: public UIItem
{
public:
	UIDrop	(string Name,Color Back=Color(255,255,255,255),Color Text=Color(0,0,0,255),int Size=10)
		:UIItem(Name,true),mSize(Size),mBack(Back),mTextColor(Text)
	{
		mCurrent=mOptions.begin();
	}
	
	void		setCurrent	(T	Value)
	{
		for(std::map<string,T>::iterator it=mOptions.begin();it!=mOptions.end();it++)
		{
			if(it->second==Value)
			{
				mCurrent=it;
				break;
			}
		}
	}

	void		draw	(sf::RenderWindow& window,sf::Vector2f Position)
	{
		sf::Text	renderText(mName+":");
		renderText.setPosition(Position);
		renderText.setColor(mTextColor);
		renderText.setCharacterSize(mSize);
		window.draw(renderText);
		sf::Vector2f	NewPos(Position);
		NewPos.x+=renderText.getGlobalBounds().width+10;
		if(!mSelected&&mCurrent!=mOptions.end())
		{
			renderText.setPosition(NewPos);
			renderText.setString(mCurrent->first);
			sf::RectangleShape	RECT(Vector2f(renderText.getGlobalBounds().width+2,renderText.getGlobalBounds().height+5))
				,Frame(Vector2f(renderText.getGlobalBounds().width+1,renderText.getGlobalBounds().height+4));
			RECT.setPosition(NewPos);
			RECT.setFillColor(mBack);
			Frame.setPosition(NewPos);
			Frame.setOutlineColor(sf::Color(0,0,0,255));
			Frame.setOutlineThickness(1);
			window.draw(RECT);
			window.draw(Frame);
			window.draw(renderText);
		}
		else
		{
			for(std::map<string,T>::iterator it=mOptions.begin();it!=mOptions.end();it++)
			{
				renderText.setPosition(NewPos);
				renderText.setString(it->first);
				sf::RectangleShape	RECT(Vector2f(renderText.getGlobalBounds().width+2,renderText.getGlobalBounds().height+5))
					,Frame(Vector2f(renderText.getGlobalBounds().width+1,renderText.getGlobalBounds().height+4));
				RECT.setPosition(NewPos);
				RECT.setFillColor(mBack);
				Frame.setPosition(NewPos);
				Frame.setOutlineColor(sf::Color(0,0,0,255));
				Frame.setOutlineThickness(1);
				window.draw(RECT);
				window.draw(Frame);
				window.draw(renderText);
				NewPos.y+=renderText.getGlobalBounds().height+5;
			}
		}
	}
	
	T			getValue	()
	{
		T	Value;
		if(mCurrent!=mOptions.end())
		{
			Value=mCurrent->second;
		}
		return Value;
	}
	
	void		addOption	(string Key,T Value)
	{
		mOptions[Key]=Value;
		if(mCurrent==mOptions.end())
		{
			mCurrent=mOptions.begin();
		}
	}

	FloatRect	getHitBox	(sf::Vector2f	Position)const
	{
		sf::Text	renderText(mName+":");
		renderText.setPosition(Position);
		renderText.setCharacterSize(mSize);
		sf::Vector2f	NewPos(Position);
		sf::Vector2f	Size;
		NewPos.x+=renderText.getGlobalBounds().width+10;
		if(!mSelected)
		{
			renderText.setString(mCurrent->first);
			Size.x=(renderText.getGlobalBounds().width+2);
			Size.y=(renderText.getGlobalBounds().height+5);
		}
		else
		{
			for(std::map<string,T>::const_iterator it=mOptions.begin();it!=mOptions.end();it++)
			{
				renderText.setString(it->first);
				Size.y+=renderText.getGlobalBounds().height+5;
				if(Size.x<renderText.getGlobalBounds().width)
				{
					Size.x=renderText.getGlobalBounds().width;
				}
			}
		}
		sf::FloatRect Rect(NewPos,Size);
		return Rect;
	}

	void		handleEvent	(const	sf::Event& Current,sf::Vector2f	Position)
	{
		if(Current.type==sf::Event::EventType::MouseButtonPressed)
		{
		sf::Text	renderText(mName+":");
		renderText.setPosition(Position);
		renderText.setCharacterSize(mSize);
		sf::Vector2f	NewPos(Position);
		sf::Vector2f	Size;
		NewPos.x+=renderText.getGlobalBounds().width+10;
			for(std::map<string,T>::iterator it=mOptions.begin();it!=mOptions.end();it++)
			{
				renderText.setString(it->first);
				Size.x=(renderText.getGlobalBounds().width+2);
				Size.y=(renderText.getGlobalBounds().height+5);
				sf::FloatRect Rect(NewPos,Size);
				if(Rect.contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					mCurrent=it;
					mSelected=false;
					break;
				}
				NewPos.y+=renderText.getGlobalBounds().height+5;
			}
		}
	}

	~UIDrop()
	{
	}
private:
	Color							mBack,
									mTextColor;
	int								mSize;
	std::map<string,T>				mOptions;
typename	std::map<string,T>::iterator	mCurrent;
};




#endif