#pragma once
#include "UIItem.h"
class UIButton :
	public UIItem
{
public:
	UIButton(std::string Name,int Size=10,Color Back=Color(180,180,180,255),Color TextCol=Color(0,0,0,255));
	~UIButton(void);
	void		draw	(sf::RenderWindow&,sf::Vector2f Position);
	FloatRect	getHitBox	(Vector2f	Position)const;
	void		handleEvent	(const sf::Event&,Vector2f	Position);
private:
	int		mSize;
	Color	mBack,mTextCol;
};

