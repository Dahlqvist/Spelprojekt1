#include "LevelBar.h"
#include "UIDrop.h"
#include "UIText.h"
#include "TextureManager.h"
#include "XmlSaver.h"

enum	Type
{
	Load,Save,Background
};

LevelBar::LevelBar(Level* LEVEL,Vector2f Position,Vector2f Size,Color BackColor)
	:mPosition(Position),mSize(Size),mBackground(BackColor)
{
	mLevel=LEVEL;
	UIDrop<Type>*Solid=new UIDrop<Type>("Action",Color(255,255,255,255),Color(0,0,0,255),20);
	Solid->addOption("Load File",Load);
	Solid->addOption("Save File",Save);
	Solid->addOption("Background",Background);
	mUIItems.accessActive().insert(Solid);
	mUIItems.accessActive().insert(new UIText("FileName","TestBana",true,Color(255,255,255,255),Color(0,0,0,255),20));
}

LevelBar::~LevelBar(void)
{
}

void	LevelBar::render(RenderWindow& window)
{

	//Renders stuff
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	Vector2f	Position(mPosition.x/window.getSize().x,mPosition.y/window.getSize().y);
	sf::RectangleShape	Bar(mSize),Frame(mSize);
	Bar.setPosition(mPosition);
	Frame.setPosition(mPosition);
	Frame.setOutlineThickness(2);
	Frame.setOutlineColor(Color(0,0,0,255));
	Frame.setFillColor(sf::Color::Transparent);
	Bar.setFillColor(mBackground);
	window.draw(Bar);
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	window.draw(Frame);
	int i=0;
	for(UISet::iterator	it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		int width=5;
		for(UISet::iterator	et=mUIItems.accessActive().begin();et!=it;et++)
		{
			width+=200;
		}
		i++;
		(*it)->draw(window,Vector2f(mPosition.x+width,mPosition.y));
	}
}

void	LevelBar::execute()
{
	XmlSaver	Saver;
	std::string	filename=dynamic_cast<UIText*>(mUIItems.getActivated("FileName"))->getString();
	switch(dynamic_cast<UIDrop<Type>*>(mUIItems.getActivated("Action"))->getValue())
	{
	case	Background:
		break;
	case	Save:
		Saver.saveLevel(*mLevel);
		Saver.setFilename(filename);
		Saver.createFile();
		break;
	case	Load:
		mLevel->loadNewLevel(filename+".xml");
		break;
	default:
		break;
	}
}

Vector2f	LevelBar::getPosition()
{
	return mPosition;
}

Vector2f	LevelBar::getSize()
{
	return mSize;
}

bool	LevelBar::checkHit(const Vector2f& Point)const
{
	sf::Vector2f	SIZE=mSize;
	if(mSelected)
	{
		SIZE.y+=10;
	}
	FloatRect	Test(mPosition,SIZE);
	return	Test.contains(Point);
}

void	LevelBar::eventHandle(const	Event&	Current)
{
	UIItem*	Selected=0;
	int Width=5;
	for(UISet::iterator	it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		if((*it)->selected())
		{
			Selected=(*it);
			break;
		}
	}
	UISet::iterator	it;
	switch(Current.type)
	{
	case sf::Event::EventType::KeyPressed:
		if(Current.key.code==sf::Keyboard::Return)
		{
			execute();
		}
		else
		{
			Selected->handleEvent(Current,Vector2f(mPosition.x+Width,mPosition.y+5));
		}
		break;
	case sf::Event::EventType::MouseButtonPressed:
		for(it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
		{
			if(Selected==(*it))
			{
				if((*it)->getHitBox(Vector2f(mPosition.x+Width,mPosition.y+5)).contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					Selected->handleEvent(Current,Vector2f(mPosition.x+Width,mPosition.y+5));
				}
				else
				{
					(*it)->setSelect(false);
				}
			}
			else 
			{
				if((*it)->getHitBox(Vector2f(mPosition.x+Width,mPosition.y+5)).contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					(*it)->setSelect(true);
				}
				else
				{
					(*it)->setSelect(false);
				}
			}
			Width+=200;
		}
		break;
	default:
		if(Selected!=0)
		{
			Selected->handleEvent(Current,Vector2f(mPosition.x+Width,mPosition.y+5));
		}
		break;
	}
}

void	LevelBar::setSelect(const bool&	Select)
{
	mSelected=Select;
}

bool	LevelBar::isSelected()const
{
	return	mSelected;
}