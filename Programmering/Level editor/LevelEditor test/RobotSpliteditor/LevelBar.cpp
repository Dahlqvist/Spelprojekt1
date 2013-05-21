#include "LevelBar.h"
#include "UIDrop.h"
#include "UIText.h"
#include "UIButton.h"
#include "TextureManager.h"
#include "LevelSaver.h"

enum	Type
{
	Load,Save,Background,Name,ClearUnits,ClearBackground,SetSnap
};

LevelBar::LevelBar(LevelConstructor* LEVEL,Vector2f Position,Vector2f Size,Color BackColor)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mSnapTo(1)
{
	mLevel=LEVEL;
	UIDrop<Type>*Solid=new UIDrop<Type>("Action",Color(255,255,255,255),Color(0,0,0,255),20,2);
	Solid->addOption("Load File",Load);
	Solid->addOption("Save File",Save);
	Solid->addOption("Background",Background);
	Solid->addOption("Level Name",Name);
	Solid->addOption("Clear Units",ClearUnits);
	Solid->addOption("Clear Background",ClearBackground);
	Solid->addOption("Set Snaping Size",SetSnap);
	mUIItems.accessActive().insert(Solid);
	mUIItems.accessActive().insert(new UIText("NewName","TestBana",true,Color(255,255,255,255),Color(0,0,0,255),20));
	mUIItems.accessActive().insert(new UIButton("Update",20));
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
	int width=5;
	for(UISet::iterator	it=mUIItems.accessActive().begin();it!=mUIItems.accessActive().end();it++)
	{
		if(!mSelected)
		{
			(*it)->setSelect(false);
		}
		sf::Text	renderText((*it)->getName()+":");
		renderText.setPosition(Position);
		renderText.setCharacterSize(20);
		(*it)->draw(window,Vector2f(mPosition.x+width,mPosition.y));
		width+=(*it)->getHitBox(Vector2f(0,0)).width+renderText.getGlobalBounds().width+20;
	}
}

void	LevelBar::execute()
{
	LevelSaver	Saver;
	std::string	filename;
	if(mUIItems.getActivated("NewName")!=0)
	{
		filename=dynamic_cast<UIText*>(mUIItems.getActivated("NewName"))->getString();
	}
		BackgroundVector temp=mLevel->getBackground();
 	switch(dynamic_cast<UIDrop<Type>*>(mUIItems.getActivated("Action"))->getValue())
	{
	case	Background:
		mLevel->setBackground(filename);
		break;
	case	Save:
		Saver.saveLevel(*mLevel);
		Saver.setFilename("Saved/"+filename);
		Saver.createFile();
		break;
	case	Load:
		mLevel->loadNewLevel("Load/"+filename+".xml");
		break;
	case	Name:
		mLevel->setNewName(filename);
		break;
	case	SetSnap:
		mSnapTo=atoi(filename.c_str());
		break;
	case	ClearUnits:
		mLevel->deletePlayer();
		mLevel->deletePointers();
		mLevel->getBackgroundWrap().setBackground(temp);
		break;
	case	ClearBackground:
		mLevel->getBackgroundWrap().deletePointer();
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
		else if(Selected!=0)
		{
			if(Selected!=0)
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
					mUIItems.activate("NewName");
					char*	size=new char[10];
					if(dynamic_cast<UIDrop<Type>*>(Selected)!=0)
					{
						switch(dynamic_cast<UIDrop<Type>*>(Selected)->getValue())
						{
						case	Name:
							dynamic_cast<UIText*>(mUIItems.getActivated("NewName"))->setDefault(mLevel->getName());
							break;
						case	Background:
							dynamic_cast<UIText*>(mUIItems.getActivated("NewName"))->setDefault(mLevel->getBackgroundWrap().getName());
							break;
						case	SetSnap:
							itoa(mSnapTo,size,10);
							dynamic_cast<UIText*>(mUIItems.getActivated("NewName"))->setDefault(string(size));
							break;
						case	ClearBackground:
							mUIItems.deactivate("NewName");
							break;
						case	ClearUnits:
							mUIItems.deactivate("NewName");
							break;
						default:
							dynamic_cast<UIText*>(mUIItems.getActivated("NewName"))->setDefault(string("Default"));
							break;
						}
					}
					delete size;
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
					if((*it)->getName()=="Update")
					{
						execute();
						(*it)->handleEvent(Current,Vector2f(0,0));
					}
				}
				else
				{
					(*it)->setSelect(false);
				}
			}
			sf::Text	renderText((*it)->getName()+":");
			renderText.setPosition(mPosition);
			renderText.setCharacterSize(20);
			Width+=(*it)->getHitBox(Vector2f(0,0)).width+renderText.getGlobalBounds().width+20;
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

void	LevelBar::resize(sf::RenderWindow&	window)
{
	mSize.x=window.getSize().x;
}

Uint8	LevelBar::getSnap()const
{
	return mSnapTo;
}