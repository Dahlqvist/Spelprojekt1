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
	UIDrop	(string Name,Color Back=Color(255,255,255,255),Color Text=Color(0,0,0,255),int Size=10,int Rows=0)
		:UIItem(Name,true),mSize(Size),mBack(Back),mTextColor(Text),mRows(Rows),mWidth(0),mBSize(0,0)
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
			sf::RectangleShape	RECT(mBSize+sf::Vector2f(2,5))
					,Frame(mBSize+sf::Vector2f(1,4));
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
			int	i=0;
			for(std::map<string,T>::iterator it=mOptions.begin();it!=mOptions.end();it++)
			{
				Vector2f	extraPos;
				Vector2i	intPos(0,i);
				if(mRows>0)
				{
					intPos=Vector2i(i/mRows,i%mRows);
				}
				extraPos.x=intPos.x*mBSize.x+2*intPos.x;
				extraPos.y=((intPos.y*mBSize.y)+5*intPos.y);
				renderText.setPosition(NewPos+extraPos);
				renderText.setString(it->first);
				sf::RectangleShape	RECT(mBSize+sf::Vector2f(2,5))
					,Frame(mBSize+sf::Vector2f(1,4));
				RECT.setPosition(NewPos+extraPos);
				RECT.setFillColor(mBack);
				Frame.setPosition(NewPos+extraPos);
				Frame.setOutlineColor(sf::Color(0,0,0,255));
				Frame.setOutlineThickness(1);
				window.draw(RECT);
				window.draw(Frame);
				window.draw(renderText);
				i++;
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
		sf::Text	SizeString;
		SizeString.setCharacterSize(mSize);
		SizeString.setPosition(0.f,0.f);
		for(map<std::string,T>::iterator	it=mOptions.begin();it!=mOptions.end();it++)
		{
			SizeString.setString(it->first);
			if(SizeString.getGlobalBounds().width>mBSize.x)
			{
				mBSize.x=SizeString.getGlobalBounds().width;
			}
			if(SizeString.getGlobalBounds().height>mBSize.y)
			{
				mBSize.y=SizeString.getGlobalBounds().height;
			}
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
			Size=mBSize+Vector2f(5,2);
		}
		else
		{
			int i=mOptions.size();
			if(i>(mRows))
			{
				Size.y=mRows*(mBSize.y+5);
				Size.x=mBSize.x*int(((i-1)/mRows)+1);
			}
			else
			{
				Size.x=mBSize.x+2;
				Size.y=i*(mBSize.y+5);
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
			int i=0;
			for(std::map<string,T>::iterator it=mOptions.begin();it!=mOptions.end();it++)
			{				Vector2f	extraPos;
				Vector2i	intPos(0,i);
				if(mRows>0)
				{
					intPos=Vector2i(i/mRows,i%mRows);
				}
				extraPos.x=intPos.x*(mBSize.x+2);
				extraPos.y=(intPos.y*(mBSize.y+5));
				sf::FloatRect Rect(NewPos+extraPos,mBSize+Vector2f(2,5));
				if(Rect.contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					mCurrent=it;
					mSelected=false;
					break;
				}
				i++;
			}
		}
	}

	~UIDrop()
	{
	}
private:
	Color							mBack,
									mTextColor;
	int								mSize,
									mRows,
									mWidth;
	std::map<string,T>				mOptions;
	sf::Vector2f					mBSize;
	typename	
	std::map<string,T>::iterator	mCurrent;
};




#endif