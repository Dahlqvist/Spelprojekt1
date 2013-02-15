#include "Toolbar.h"
#include "Editor.h"
#include "UIText.h"

set<UIItem*>&	UIItemContainer::accessActive()
{
	return	mActive;
}

set<UIItem*>&	UIItemContainer::accessInactive()
{
	return	mInactive;
}

UIItem*	UIItemContainer::getActivated(std::string Name)
{
	for(UISet::iterator	it=mActive.begin();it!=mActive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			return	*it;
		}
	}
	return	0;
}

UIItem*	UIItemContainer::getDeactivated(std::string Name)
{
	for(UISet::iterator	it=mInactive.begin();it!=mInactive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			return	*it;
		}
	}
	return	0;
}

void	UIItemContainer::deactivate(std::string Name)
{
	for(UISet::iterator	it=mActive.begin();it!=mActive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			mInactive.insert(*it);
			mActive.erase(it);
			break;
		}
	}
}

void	UIItemContainer::activate(std::string Name)
{
	for(UISet::iterator	it=mInactive.begin();it!=mInactive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			mActive.insert(*it);
			mInactive.erase(it);
			break;
		}
	}
}

UIItemContainer::UIItemContainer()
{
}

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer()
{
	mUIItems.accessActive().insert(new UIText("Name","Param",true,Color(255,255,255,255),Color(0,0,0,255),15));
	(*mUIItems.accessActive().begin())->setSelect(true);
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
	mUIItems.activate("Name");
	dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(mCurrUnit.getObject()->getId());
}

void	Toolbar::setPlayer(Player*	Source)
{
	mCurrPlayer.unInitiate();
	mCurrPlayer.setPtr(Source);
	mCurrUnit.unInitiate();
	mUIItems.activate("Name");
	dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(string("Player"));
}

Vector2f	Toolbar::getPosition()
{
	return mPosition;
}

Vector2f	Toolbar::getSize()
{
	return mPosition;
}

bool	Toolbar::checkHit(const Vector2f& Point)const
{
	FloatRect	Test(mPosition,mSize);
	return	Test.contains(Point);
}

void	Toolbar::eventHandle(const	Event&	Current)
{
	UIItem*	Selected=0;
	for(UISet::iterator	it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		if((*it)->selected())
		{
			Selected=(*it);
			break;
		}
	}
	switch(Current.type)
	{
	case sf::Event::EventType::TextEntered:
		Selected->handleEvent(Current);
	}
}

void	Toolbar::setSelect(const bool&	Select)
{
	mSelected=Select;
}

bool	Toolbar::isSelected()const
{
	return	mSelected;
}