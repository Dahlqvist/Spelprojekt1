#include "Toolbar.h"
#include "Editor.h"
#include "UIText.h"

set<UIItem*>&	UIItemContainer::accessActive()
{
	return	mActive;
}

set<UIItem*>&	UIItemContainer::accessInactive()
{
	return	mActive;
}

UIItemContainer::UIItemContainer()
{
}

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer()
{
	mUIItems.accessActive().insert(new UIText("Test","Param",Color(255,255,255,255),Color(0,0,0,255),15));
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
	sf::RectangleShape	Bar(mSize),Frame(mSize);
	Bar.setPosition(mPosition);
	Frame.setPosition(mPosition);
	Frame.setOutlineThickness(2);
	Frame.setOutlineColor(Color(0,0,0,255));
	Frame.setFillColor(sf::Color::Transparent);
	Bar.setFillColor(mBackground);
	window.draw(Bar);
	View	MiniView=window.getDefaultView();
	MiniView.setViewport(FloatRect(Position,Size));
	editor->renderLevel(MiniView);
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	window.draw(Frame);
	for(set<UIItem*>::iterator it= mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		(*it)->draw(window,Vector2f(mPosition.x+5,mPosition.y+mViewSize.y+10));
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