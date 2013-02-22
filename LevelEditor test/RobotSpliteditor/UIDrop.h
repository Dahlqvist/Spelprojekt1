#ifndef	INC_UIDROP
#define	INC_UIDROP
#include"UIItem.h"
#include<map>
#include<string>

using namespace std;

template<class T>
class UIDrop: public UIItem
{
public:
	UIDrop	(string Name);
	void		draw	(sf::RenderWindow&,Vector2f);
	T			getValue	();
	void		addOption	(string Key,T Value);
	FloatRect	getHitBox	(Vector2f	Position)const;
	void		HandleEvent	(const	sf::Event&,Vector2f	Position);
private:	
	map<string,T>::iterator		mCurrent;
	map<string,T>				mOptions;
};


template<class T>
void	UIDrop::draw(sf::RenderWindow& window,Vector2f position)
{
	sf::Text	renderText;
	
	if(!mSelected)
	{
		
	}
}

template<class T>
T	UIDrop::getValue()
{
}

template<class T>
void	UIDrop::addOption(string Key,T Value)
{
}

template<class T>
FloatRect	UIDrop::getHitBox(Vector2f	Position)const
{
	FloatRect Rect;
	return Rect;
};

template<class T>
void	UIDrop::HandleEvent(const sf::Event& Current,Vector2f Position)
{
}

#endif