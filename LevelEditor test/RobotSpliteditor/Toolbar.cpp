#include "Toolbar.h"
#include "Editor.h"

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer()
{
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