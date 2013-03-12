#include <stdlib.h>
#include "Toolbar.h"
#include "Editor.h"
#include "UIText.h"
#include "UIDrop.h"
#include "DialogueBox.h"
#include "Laser.h"
#include "LaserDeactivator.h"
#include "UIObjectMenu.h"
#include "LevelLoader.h"
#include "XmlSaver.h"
#include "Platform.h"
#include "Meanix.h"
#include "ObjectLoader.h"
#include "LaserHolder.h"
#include "Checkpoint.h"

Toolbar::Toolbar(Vector2f Position,Vector2f Size,Color BackColor,Vector2f MiniViewSize)
	:mPosition(Position),mSize(Size),mBackground(BackColor),mViewSize(MiniViewSize)
	,mCurrUnit(),mCurrPlayer(),mNewPos(false),mChange(false)
{
	ObjectLoader	Loader("OtherMenu.xml");
	UIObjectMenu *meny=Loader.getObject(this);
	UIDrop<bool>*Solid=new UIDrop<bool>("Solid",Color(255,255,255,255),Color(0,0,0,255),15);
	Solid->addOption("Yes",true);
	Solid->addOption("No",false);
	UIDrop<bool>*Behined=new UIDrop<bool>("Behined Player",Color(255,255,255,255),Color(0,0,0,255),15);
	Behined->addOption("Yes",true);
	Behined->addOption("No",false);
	UIDrop<bool>*Fade=new UIDrop<bool>("Fade In",Color(255,255,255,255),Color(0,0,0,255),15);
	Fade->addOption("Yes",true);
	Fade->addOption("No",false);
	UIDrop<bool>*Visible=new UIDrop<bool>("Visible",Color(255,255,255,255),Color(0,0,0,255),15);
	Visible->addOption("Yes",true);
	Visible->addOption("No",false);
	UIDrop<bool>*Active=new UIDrop<bool>("Active",Color(255,255,255,255),Color(0,0,0,255),15);
	Active->addOption("Yes",true);
	Active->addOption("No",false);
	UIDrop<string>*color=new UIDrop<string>("Color",Color(255,255,255,255),Color(0,0,0,255),15);
	color->addOption("Red","Red");
	color->addOption("Yellow","Yellow");
	color->addOption("Blue","Blue");
	UIDrop<int>*Rotation=new UIDrop<int>("Rotation",Color(255,255,255,255),Color(0,0,0,255),15);
	Rotation->addOption("Down",0);
	Rotation->addOption("Left",90);
	Rotation->addOption("Up",180);
	Rotation->addOption("Right",270);
	UIDrop<Unit*>*UTargets=new UIDrop<Unit*>("UnitTarget",Color(255,255,255,255),Color(0,0,0,255),15);
	UIDrop<Unit*>*LTargets=new UIDrop<Unit*>("LaserTarget",Color(255,255,255,255),Color(0,0,0,255),15);
	mUIItems.accessInactive().insert(Solid);
	mUIItems.accessInactive().insert(Behined);
	mUIItems.accessInactive().insert(Fade);
	mUIItems.accessInactive().insert(Visible);
	mUIItems.accessInactive().insert(Rotation);
	mUIItems.accessInactive().insert(Active);
	mUIItems.accessInactive().insert(color);
	mUIItems.accessInactive().insert(UTargets);
	mUIItems.accessInactive().insert(LTargets);
	mUIItems.accessInactive().insert(new UIText("Name","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Sprite","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Lives","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Position x","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Position y","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Target Id","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Sound","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Length","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("Range of visibility","",true,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("SpriteOn","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessInactive().insert(new UIText("SpriteOff","",false,Color(255,255,255,255),Color(0,0,0,255),15));
	mUIItems.accessActive().insert(meny);
	Loader.loadFile("PlatFormMenu.xml");
	meny=Loader.getObject(this);
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
		setTargets(editor->mLevel);
		mChange=false;
	}
	//Change UIItems
	if(mNewPos)
	{
		if(editor->collide(mCurrUnit))
		{
			mCurrUnit.getObject()->setPosition(mCurrUnit.getOriginal());
		}
		else
		{
			mCurrUnit.setOriginal(mCurrUnit.getObject()->getPosition());
		}
		mNewPos=false;
		setTargets(editor->mLevel);
	}
	if(!mSelected)
	{
		setUIActives();
	}
	//Renders stuff
	RenderWindow&	window=editor->getWindow();
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	Vector2f	Size(mViewSize.x/window.getSize().x,mViewSize.y/window.getSize().y),
				Position(mPosition.x/window.getSize().x,mPosition.y/window.getSize().y);
	sf::RectangleShape	Bar(mSize),Frame(mSize),Indicator;
	Bar.setPosition(mPosition);
	Frame.setPosition(mPosition);
	Frame.setOutlineThickness(2);
	Frame.setOutlineColor(Color(0,0,0,255));
	Frame.setFillColor(sf::Color::Transparent);
	Bar.setFillColor(mBackground);
	window.draw(Bar);
	//Renders the minimap
	View	MiniView=window.getDefaultView();
	MiniView.setViewport(FloatRect(Position,Size));
	float	scale=window.convertCoords(Vector2i(mPosition+mViewSize),MiniView).x/editor->mLevel.getSize().x;
	if(scale>window.convertCoords(Vector2i(mPosition+mViewSize),MiniView).y/editor->mLevel.getSize().y)
	{
		scale=window.convertCoords(Vector2i(mPosition+mViewSize),MiniView).y/editor->mLevel.getSize().y;
	}
	if(scale>1)
	{
		MiniView.zoom(scale);
	}
	editor->renderLevel(MiniView);
	//Renders the rect showing your view on the minimap
	Position=window.convertCoords(Vector2i(0,editor->mLevelTool.getSize().y),editor->mCurrView)+Vector2f(10,10);
	Size=window.convertCoords(Vector2i(editor->mCurrView.getViewport().width*window.getSize().x,
		editor->mCurrView.getViewport().height*window.getSize().y+editor->mLevelTool.getSize().y),editor->mCurrView)-Position-Vector2f(10,10);
	Indicator.setSize(Size);
	Indicator.setPosition(Position);
	Indicator.setFillColor(sf::Color::Transparent);
	Indicator.setOutlineColor(sf::Color(255,0,0,255));
	Indicator.setOutlineThickness(10);
	window.setView(MiniView);
	window.draw(Indicator);
	//Renders the Frame
	window.setView(View(FloatRect(Vector2f(0,0),Vector2f(window.getSize()))));
	window.draw(Frame);
	//Draws	the UIItems
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
	setUIActives();
}

void	Toolbar::setPlayer(Player*	Source)
{
	mCurrPlayer.unInitiate();
	mCurrPlayer.setPtr(Source,Source->getCollisionSprite()[0]->getPosition(),Vector2f(0,0),true);
	mCurrUnit.unInitiate();
	setUIActives();
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
			update();
		}
		else if(Selected!=0)
		{
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
				}
				else
				{
					(*it)->setSelect(false);
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
	mUIItems.deactivateAll();
	mUIItems.activate("zOther");
	mUIItems.activate("zPlatform");
}

void	Toolbar::unIniPlayer()
{
	mCurrPlayer.unInitiate();
}

void	Toolbar::resize(RenderWindow&	window)
{
	mPosition.x=window.getSize().x-mSize.x;
	mSize.y=window.getSize().y-mPosition.y;
}

void	Toolbar::setTargets	(Level& level)
{
	UIDrop<Unit*>	*Units,*Lasers;
	if(dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("UnitTarget"))!=0)
	{
		Units=dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("UnitTarget"));
	}
	else
	{
		Units=dynamic_cast<UIDrop<Unit*>*>(mUIItems.getDeactivated("UnitTarget"));
	}
	if(dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("LaserTarget"))!=0)
	{
		Lasers=dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("LaserTarget"));
	}
	else
	{
		Lasers=dynamic_cast<UIDrop<Unit*>*>(mUIItems.getDeactivated("LaserTarget"));
	}
	Units->DeleteAllItems();
	Lasers->DeleteAllItems();
	for(UnitVector::size_type it=0;it<level.getObjects().size();it++)
	{
		if(dynamic_cast<DialogueBox*>(level.getObjects()[it])!=0)
		{
			Units->addOption((level.getObjects()[it])->getId(),(level.getObjects()[it]));
		}
		else if(dynamic_cast<LaserHolder*>(level.getObjects()[it])!=0)
		{
			Lasers->addOption((level.getObjects()[it])->getId(),(level.getObjects()[it]));
		}
	}
}

void	Toolbar::setUIActives()
{
	if(mCurrUnit.isActive())
	{
		mUIItems.deactivateAll();
		mUIItems.activate("Name");
		mUIItems.activate("Sprite");
		mUIItems.activate("Position x");
		mUIItems.activate("Position y");
		mUIItems.activate("zOther");
		mUIItems.activate("zPlatform");
		char*	temp=new char[10];
		string	NEW=TextureManager::getSpriteName(mCurrUnit.getObject()->getSprite());
		itoa(mCurrUnit.getObject()->getPosition().x,temp,10);
		dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(mCurrUnit.getObject()->getId());
		dynamic_cast<UIText*>(mUIItems.getActivated("Sprite"))->setDefault(NEW);
		dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
		itoa(mCurrUnit.getObject()->getPosition().y,temp,10);
		dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
		if(dynamic_cast<Platform*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("Lives");
			char*	temp=new	char[10];
			itoa(dynamic_cast<Platform*>(mCurrUnit.getObject())->getLives(),temp,10);
			dynamic_cast<UIText*>(mUIItems.getActivated("Lives"))->setDefault(string(temp));
			delete temp;
		}
		//Sets the laser's uiitems
		else if(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("Color");
			mUIItems.activate("Rotation");
			mUIItems.activate("Length");
			mUIItems.activate("Range of visibility");
			mUIItems.activate("Active");
			mUIItems.activate("Target Id");
		dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->mLaser->mId);
		//Sets target ID
			dynamic_cast<UIText*>(mUIItems.getActivated("Target Id"))->setDefault(mCurrUnit.getObject()->getId());
		//Get Visibility range, length and rotaiton angle.
			int		angle=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getRotation();
			float	visibility;
			float	length=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getLength();
			switch(angle)
			{
			case 0:
				visibility=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getSize().x;
				break;
			case 90:
				visibility=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getSize().y;
				break;
			case 180:
				visibility=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getSize().x;
				break;
			case 270:
				visibility=dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getSize().y;
				break;
			default:
				visibility=0;
				break;
			}
			visibility=visibility/2;
		//Sets the length		
			temp=new	char[10];
			itoa(length,temp,10);
			dynamic_cast<UIText*>(mUIItems.getActivated("Length"))->setDefault(string(temp));
			delete temp;
		//Sets the visibility
			temp=new	char[10];
			itoa(visibility,temp,10);
			dynamic_cast<UIText*>(mUIItems.getActivated("Range of visibility"))->setDefault(string(temp));
			delete temp;
		//Sets the rotation
			dynamic_cast<UIDrop<int>*>(mUIItems.getActivated("Rotation"))->setCurrent(angle);
		//Sets the rotation
			dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Active"))->setCurrent(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->isActive());
			if(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().find("Red")<dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().length())
			{		
				dynamic_cast<UIDrop<std::string>*>(mUIItems.getActivated("Color"))->setCurrent("Red");
			}
			else if(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().find("Blue")<dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().length())
			{
				dynamic_cast<UIDrop<std::string>*>(mUIItems.getActivated("Color"))->setCurrent("Blue");
			}
			else if(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().find("Yellow")<dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->getId().length())
			{
				dynamic_cast<UIDrop<std::string>*>(mUIItems.getActivated("Color"))->setCurrent("Yellow");
			}
		}
		else if(dynamic_cast<Meanix*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.deactivate("Sprite");
		}
		else if(dynamic_cast<Checkpoint*>(mCurrUnit.getObject())!=0)
		{
			
		}
		else if(dynamic_cast<DialogueBox*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("Fade In");
			mUIItems.activate("Visible");
			mUIItems.activate("Target Id");
			dynamic_cast<UIText*>(mUIItems.getActivated("Target Id"))->setDefault(dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->getId());
			dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Visible"))->setCurrent(dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->getVisible());
			dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Fade In"))->setCurrent(dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->getFadeIn());
		}
		else if(dynamic_cast<LaserDeactivator*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("LaserTarget");
			mUIItems.activate("Rotation");
			dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("LaserTarget"))->setCurrent(dynamic_cast<Trigger*>(mCurrUnit.getObject())->mTriggedObject);
			dynamic_cast<UIDrop<int>*>(mUIItems.getActivated("Rotation"))->setCurrent(int(dynamic_cast<LaserDeactivator*>(mCurrUnit.getObject())->getRotation()+180)%360);
		}
		else if(dynamic_cast<Trigger*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("UnitTarget");
			mUIItems.activate("Sound");
			dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("UnitTarget"))->setCurrent(dynamic_cast<Trigger*>(mCurrUnit.getObject())->mTriggedObject);
			dynamic_cast<UIText*>(mUIItems.getActivated("Sound"))->setDefault(dynamic_cast<Trigger*>(mCurrUnit.getObject())->getSound());
		}
		else
		{
			mUIItems.activate("Solid");
			dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Solid"))->setCurrent(mCurrUnit.getObject()->isSolid());
		}
	}
	else if(mCurrPlayer.isActive())
	{
		mUIItems.deactivateAll();
		mUIItems.activate("Name");
		mUIItems.activate("Position x");
		mUIItems.activate("Position y");
		mUIItems.activate("zOther");
		mUIItems.activate("zPlatform");
		char*	temp=new char[10];
		itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().x,temp,10);
		dynamic_cast<UIText*>(mUIItems.getActivated("Name"))->setDefault(string("Player"));
		dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->setDefault(string(temp));
		itoa(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition().y,temp,10);
		dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->setDefault(string(temp));
	}
}

void	Toolbar::update()
{
	Vector2f	 temp;
	temp.x=atoi(dynamic_cast<UIText*>(mUIItems.getActivated("Position x"))->getString().c_str());
	temp.y=atoi(dynamic_cast<UIText*>(mUIItems.getActivated("Position y"))->getString().c_str());
	mNewPos=true;
	if(mCurrPlayer.isActive())
	{
		mCurrPlayer.getObject()->forceMove(0,temp-(mCurrPlayer.getObject()->getCollisionSprite()[0]->getPosition()+mCurrPlayer.getOffset())+sf::Vector2f(0,2));
		mCurrPlayer.getObject()->forceMove(0,Vector2f(0,-4));
		mCurrPlayer.getObject()->update();
	}
	else if(mCurrUnit.isActive())
	{
		mCurrUnit.getObject()->setPosition(temp);
		if(dynamic_cast<Platform*>(mCurrUnit.getObject())!=0)
		{
			mUIItems.activate("Lives");
			dynamic_cast<Platform*>(mCurrUnit.getObject())->mLives=atoi(dynamic_cast<UIText*>(mUIItems.getActivated("Lives"))->getString().c_str());

		}
		else if(dynamic_cast<LaserHolder*>(mCurrUnit.getObject())!=0)
		{
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->setId(dynamic_cast<UIText*>(mUIItems.getActivated("Target Id"))->getString());
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->rotate(dynamic_cast<UIDrop<int>*>(mUIItems.getActivated("Rotation"))->getValue());
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->setColor(dynamic_cast<UIDrop<std::string>*>(mUIItems.getActivated("Color"))->getValue());
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->getLaser()->setLength(atof(dynamic_cast<UIText*>(mUIItems.getActivated("Length"))->getString().c_str()));
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->setVisibilityRange(atof(dynamic_cast<UIText*>(mUIItems.getActivated("Range of visibility"))->getString().c_str()));
			dynamic_cast<LaserHolder*>(mCurrUnit.getObject())->setActive(dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Active"))->getValue());
		}
		else if(dynamic_cast<LaserDeactivator*>(mCurrUnit.getObject())!=0)
		{
			dynamic_cast<LaserDeactivator*>(mCurrUnit.getObject())->setTarget(dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("LaserTarget"))->getValue());
			dynamic_cast<LaserDeactivator*>(mCurrUnit.getObject())->setRotation(int(dynamic_cast<UIDrop<int>*>(mUIItems.getActivated("Rotation"))->getValue()+180)%360);
		}
		else if(dynamic_cast<Trigger*>(mCurrUnit.getObject())!=0)
		{
			dynamic_cast<Trigger*>(mCurrUnit.getObject())->setTarget(dynamic_cast<UIDrop<Unit*>*>(mUIItems.getActivated("UnitTarget"))->getValue());
			dynamic_cast<Trigger*>(mCurrUnit.getObject())->setSound(dynamic_cast<UIText*>(mUIItems.getActivated("Sound"))->getString());
		}
		else if(dynamic_cast<DialogueBox*>(mCurrUnit.getObject())!=0)
		{
			dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->setId(dynamic_cast<UIText*>(mUIItems.getActivated("Target Id"))->getString());
			dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->setFadeIn(dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Fade In"))->getValue());
			dynamic_cast<DialogueBox*>(mCurrUnit.getObject())->setVisible(dynamic_cast<UIDrop<bool>*>(mUIItems.getActivated("Visible"))->getValue());
		}
	}
}


PlayerContainer	Toolbar::getPlayCont()
{
	return mCurrPlayer;
}