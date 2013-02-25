#include <stdlib.h>
#include "Toolbar.h"
#include "Editor.h"
#include "UIText.h"
#include "UIDrop.h"
#include "UIObjectMenu.h"
#include "LevelLoader.h"
#include "XmlSaver.h"

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer()
{
	UIObjectMenu *meny= new UIObjectMenu("Other",Vector2f(190,300),this,Color(100,100,100,255),15);
	meny->addIcon(new PlayerIcon());
	meny->addIcon(new UnitIcon("Platform","Tile1"));
	meny->addIcon(new UnitIcon("Platform","Tile2"));
	meny->addIcon(new UnitIcon("Platform","Tile3"));
	UIDrop<bool>*Solid=new UIDrop<bool>("Solid",Color(255,255,255,255),Color(0,0,0,255),15);
	Solid->addOption("Yes",true);
	Solid->addOption("No",false);
	mUIItems.accessInactive().insert(Solid);
	mUIItems.accessInactive().insert(new UIText("Name","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Sprite","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Position x","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Position y","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessActive().insert(meny);
	mUIItems.getActivated("zOther")->setSelect(true);
}

Toolbar::~Toolbar(void)
{
}

void	Toolbar::render(Editor* editor)
{
	//Checks if the selected units are the same
	if(mChange)
	{
		editor->setPlayer(mCurrPlayer);
		editor->setUnit(mCurrUnit);
		mChange=false;
	}
	//Change UIItems
	if(mCurrUnit.isActive())
	{
		char*	temp=new char[10];
		itoa(mCurrUnit.getObject()->getPosition().x,temp,10);
		if(!mUIItems.getActivated("Position x")->selected())
		{
			dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
		}
		itoa(mCurrUnit.getObject()->getPosition().y,temp,10);
		if(!mUIItems.getActivated("Position y")->selected())
		{
			dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
		}
	}
	else if(mCurrPlayer.isActive())
	{
		char*	temp=new char[10];
		itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().x,temp,10);
		if(!mUIItems.getActivated("Position x")->selected())
		{
			dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
		}
		itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().y,temp,10);
		if(!mUIItems.getActivated("Position y")->selected())
		{
			dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
		}
	}
	//Renders stuff
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
	int i=0;
	for(UISet::iterator	it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		int Height=mViewSize.y+5;
		for(UISet::iterator	et=mUIItems.accessActive().begin();et!=it;et++)
		{
			Height+=(*et)->getHitBox(Position).height;
		}
		i++;
		(*it)->draw(window,Vector2f(mPosition.x+5,mPosition.y+Height));
	}
}

void	Toolbar::setUnit(Unit*	Source)
{
	mCurrUnit.unInitiate();
	mCurrUnit.setPtr(Source);
	mCurrPlayer.unInitiate();
	mUIItems.deactivateAll();
	mUIItems.activate("Name");
	mUIItems.activate("Sprite");
	mUIItems.activate("Position x");
	mUIItems.activate("Position y");
	mUIItems.activate("Solid");
	mUIItems.activate("zOther");
	char*	temp=new char[10];
	string	NEW=TextureManager::getSpriteName(mCurrUnit.getObject()->getSprite());
	itoa(mCurrUnit.getObject()->getPosition().x,temp,10);
	dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(mCurrUnit.getObject()->getId());
	dynamic_cast<UIText*>(mUIItems.getActivated("Sprite"))->setDefault(NEW);
	dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
	itoa(mCurrUnit.getObject()->getPosition().y,temp,10);
	dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
	dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Solid"))->setCurrent(mCurrUnit.getObject()->isSolid());
}

void	Toolbar::setPlayer(Player*	Source)
{
	mCurrPlayer.unInitiate();
	mCurrPlayer.setPtr(Source);
	mCurrUnit.unInitiate();
	mUIItems.deactivateAll();
	mUIItems.activate("Name");
	mUIItems.activate("Position x");
	mUIItems.activate("Position y");
	mUIItems.activate("zOther");
	mUIItems.deactivate("Sprite");
	char*	temp=new char[10];
	itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().x,temp,10);
	dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(string("Player"));
	dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
	itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().y,temp,10);
	dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
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
	int Height=mViewSize.y+5;
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
			Vector2f	 temp;
			temp.x=atoi(dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->getString().c_str());
			temp.y=atoi(dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->getString().c_str());
			if(mCurrPlayer.isActive())
			{
				mCurrPlayer.getObject()->forceMove(0,temp-(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition()+mCurrPlayer.getOffset()));
				mCurrPlayer.getObject()->forceMove(0,Vector2f(0,-4));
				mCurrPlayer.getObject()->update();
			}
			else if(mCurrUnit.isActive())
			{
				mCurrUnit.getObject()->setSolid(dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Solid"))->getValue());
				mCurrUnit.getObject()->setPosition(temp);
			}
		}
		else
		{
			if(Selected!=0)
				Selected->handleEvent(Current,Vector2f(mPosition.x+5,mPosition.y+Height));
		}
		break;
	case sf::Event::EventType::MouseButtonPressed:
		for(it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
		{
			if(Selected==(*it))
			{
				if((*it)->getHitBox(Vector2f(mPosition.x+5,mPosition.y+Height)).contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					Selected->handleEvent(Current,Vector2f(mPosition.x+5,mPosition.y+Height));
					break;
				}
				else
				{
					(*it)->setSelect(false);
				}
			}
			else 
			{
				if((*it)->getHitBox(Vector2f(mPosition.x+5,mPosition.y+Height)).contains(Current.mouseButton.x,Current.mouseButton.y))
				{
					(*it)->setSelect(true);
//					mChange=true;
				}
				else
				{
					(*it)->setSelect(false);
//					mChange=true;
				}
			}
			Height+=(*it)->getHitBox(Vector2f()).height;
		}
		break;
	default:
		if(Selected!=0)
		{
			Selected->handleEvent(Current,Vector2f(mPosition.x+5,mPosition.y+Height));
		}
		break;
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

void	Toolbar::unIniUnit()
{
	mCurrUnit.unInitiate();
}

void	Toolbar::unIniPlayer()
{
	mCurrPlayer.unInitiate();
}