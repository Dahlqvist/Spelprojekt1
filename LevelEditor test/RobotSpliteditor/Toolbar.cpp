#include "Toolbar.h"
#include "Editor.h"
#include "UIText.h"

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer()
{
	mMenu.push_back(new UIText("Test",mPosition,"Param",Color(255,255,255,255),Color(0,0,0,255),15));
}

Toolbar::~Toolbar(void)
{
}

void	Toolbar::render(Editor* editor)
{
	RenderWindow&	window=editor->getWindow();
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	Vector2f	Size(mViewSize.x/window.getSize().x,mViewSize.y/window.getSize().y),
		Position(mPosition.x/window.getSize().x,mPosition.y/window.getSize().y);
	sf::RectangleShape	rect(mSize);
	rect.setPosition(mPosition);
	rect.setFillColor(mBackground);
	window.draw(rect);
	View	MiniView=window.getDefaultView();
	MiniView.setViewport(FloatRect(Position,Size));
	editor->renderLevel(MiniView);
	for(vector<UIItem*>::iterator it= mMenu.begin();it!=mMenu.end();it++)
	{
		(*it)->draw(window);
	}
}

void	Toolbar::setUnit(Unit*	Source)
{
	mCurrUnit.unInitiate();
	mCurrUnit.setPtr(Source);
	mCurrPlayer.unInitiate();
}

void	Toolbar::setPlayer(Player*	Source)
{
	mCurrPlayer.unInitiate();
	mCurrPlayer.setPtr(Source);
	mCurrUnit.unInitiate();
}

Vector2f	Toolbar::getPosition()
{
	return mPosition;
}

Vector2f	Toolbar::getSize()
{
	return mPosition;
}