#include "LevelLoader.h"

#include <vector>
#include <string>
#include <cassert>

//Includefiles for objects
//#include "TestObject.h"

/*Inactive during development*/
#include "Background.h"
#include "Platform.h"
#include "Player.h"
#include "PlayerPart.h"
#include "Unit.h"
#include "Animation.h"
#include "Line.h"
#include "DialogueBox.h"
#include "Trigger.h"
#include "Laser.h"
#include "LaserHolder.h"
#include "LaserDeactivator.h"
#include "Meanix.h"
#include "Checkpoint.h"
#include "MiniBot.h"

LevelLoader::LevelLoader(void)
{
}

LevelLoader::LevelLoader(string Filename):XmlLoader(Filename)
{
}

LevelLoader::~LevelLoader(void)
{
}

Level	LevelLoader::getLevel()
{
	Level					RetLevel;
	if(mFileOpen)
	{
		std::vector<Background*> backgrounds;
		std::vector<Trigger*> triggers;
		std::vector<std::string> triggerTargets;
		rapidxml::xml_node<>	*LevelNode,*Gameobject;
		//Gets the Level Node
		LevelNode=		mDocument.first_node("Level");
		//Gets the first GameObject child node to level
		Gameobject=		LevelNode->first_node("Objects")->first_node("Unit");
		//Initiation of level begins
		//Sets the level's name
		RetLevel.setName(getValue(LevelNode->first_node("Name")));
		addBackground(RetLevel);
		//Sets the level's background
		/*int	Frames,Speed;
		float PosX, PosY;
		string Filename;
		BackgroundNode=	LevelNode->first_node("Background");
		Frames=			atoi(getValue(BackgroundNode->first_node("Frames")).c_str());
		Speed=			atoi(getValue(BackgroundNode->first_node("Speed")).c_str());
		Filename=		getValue(BackgroundNode->first_node("SpriteName"));
		PosX=			atof(getValue(BackgroundNode->first_node("Position")->first_node("X")).c_str());
		PosY=			atof(getValue(BackgroundNode->first_node("Position")->first_node("Y")).c_str());
		Background*BACK=new Background(Filename,Speed,Frames, sf::Vector2f(PosX, PosY));
		RetLevel.setBackground(BACK);
		RetLevel.getBackgroundWrap().setFrames(Frames);
		RetLevel.getBackgroundWrap().setSpeed(Speed);
		RetLevel.getBackgroundWrap().setName(Filename);*/
		//Used to check when the loop looped once
		bool oneLoop=false;
		//Loop that adds GameObjects to the Level
		do
		{
			if(oneLoop)
			{
				Gameobject=Gameobject->next_sibling();
			}
			else
			{
				oneLoop=true;
			}
			/*if (type=="Background")
			{
				addBackground(RetLevel, Gameobject);
			}*/
			string type;
			type=	getValue(Gameobject->first_node("Type"));
		
			if(type=="Player")
			{
				addPlayer(RetLevel,Gameobject);
			}
			else if(type=="Platform")
			{
				addPlatform(RetLevel,Gameobject);
			}
			else if(type=="Laser")
			{
				addLaser(RetLevel,Gameobject);
			}
			else if(type=="Line")
			{
//				addLine(RetLevel,Gameobject);
			}
			else if(type=="DialogueBox")
			{
				addDialogueBox(RetLevel,Gameobject);
			}
			else if(type=="Trigger")
			{
				addTrigger(triggers,triggerTargets,Gameobject);
			}
			else if(type=="LaserDeactivator")
			{
				addLaserDeactivator(triggers,triggerTargets,Gameobject);
			}
			else if(type=="Meanix")
			{
				addMeanix(RetLevel,Gameobject);
			}
			else if(type=="MiniBot")
			{
				addMiniBot(RetLevel,Gameobject);
			}
			else if (type=="Checkpoint")
			{
				addCheckpoint(RetLevel,Gameobject);
			}
			else
			{
				addUnit(RetLevel,Gameobject);
			}
		}
		while(Gameobject!=LevelNode->first_node("Objects")->last_node("Unit"));

		//Sets the targets for the triggers
		for (std::vector<Trigger*>::size_type i=0; i<triggers.size(); i++)
		{
			Unit* tempUnit=0x0;
			for (std::vector<Unit*>::size_type j=0; j<RetLevel.getObjects().size(); j++)
			{
				std::string foo1=RetLevel.getObjects()[j]->getId();
				std::string foo2=triggerTargets[i];
				if (RetLevel.getObjects()[j]->getId()==triggerTargets[i])
				{
					tempUnit=RetLevel.getObjects()[j];
				}
			}
			assert(tempUnit!=0x0);
			triggers[i]->setTarget(tempUnit);
			RetLevel.mObjects.push_back(triggers[i]);
		}
	}
	else
	{
		RetLevel.setName("ERROR");
		RetLevel.setPlayer(0);
		RetLevel.setObjects(UnitVector());
	}
	return	RetLevel;
}

void	LevelLoader::addBackground(Level	&Source)
{
	rapidxml::xml_node<>	*CurrentChild, *Node;
	string					CurrentValue;
//	Background				*TempObject;
	sf::Vector2f			Position;
	int						Frames,Speed;
	string					SpriteName;
	vector<Background*>		retBackground;
	bool oneLoop=			false;

	Node=mDocument.first_node("Level")->first_node("Backgrounds")->first_node("Background");
	string foo=mDocument.first_node("Level")->first_node("Backgrounds")->first_node("Background")->name();

	do
	{
		if(oneLoop)
		{
			Node=Node->next_sibling();
		}
		else
		{
			oneLoop=true;
		}
		string foo=Node->name();
		//Gets the Position childnode from the GameObject node
		CurrentChild=	Node->first_node("Position");
		//Gets the x Value from CurrentChild
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		//Sets X to CurentValue's value
		Position.x=((float)atof(CurrentValue.c_str()));

		//Initializes Y's value
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Position.y=((float)atof(CurrentValue.c_str()));

		//Initializes the number of frames
		CurrentChild=	Node->first_node("Frames");
		CurrentValue=	getValue(CurrentChild);
		Frames=			atoi(CurrentValue.c_str());

		//Initializes the time per frame
		CurrentChild=	Node->first_node("Speed");
		CurrentValue=	getValue(CurrentChild);
		Speed=			atoi(CurrentValue.c_str());

		//Initializes the sprite name
		CurrentChild=	Node->first_node("SpriteName");
		CurrentValue=	getValue(CurrentChild);
		SpriteName=		CurrentValue.c_str();

		retBackground.push_back(new Background(SpriteName, Speed, Frames, Position));
	}
	while(Node!=mDocument.first_node("Level")->first_node("Backgrounds")->last_node("Background"));
	Source.setBackground(retBackground);
	Source.getBackgroundWrap().setFrames(Frames);
	Source.getBackgroundWrap().setSpeed(Speed);
}

void	LevelLoader::addPlayer	(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Player					*TempObject;
	sf::Vector2f			Position;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));

	//Initializes Y's value
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Position.y=((float)atof(CurrentValue.c_str()));

	//Adds the Player pointer to the Level object
	TempObject=	new Player(Position);
	level.setPlayer(TempObject);
}

void	LevelLoader::addLaser		(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Id,Color;
	Laser					*TempObject;
	LaserHolder				*Holder;
//	Trigger					*VisibilityBox;
	sf::Vector2f			Position, Size, Offset;
	float					VisibilityRange;
	bool					Active;
	float					Length, Rotation;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	CurrentChild=	Node->first_node("Size");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));
	}

	//Initiates the Offset vector
	CurrentChild=	Node->first_node("Offset");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Offset.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Offset.y=((float)atof(CurrentValue.c_str()));
	}

	//Initiates the SpriteName
	CurrentChild=	Node->first_node("Color");
	Color=getValue(CurrentChild);
	
	//Initilizes the Id string
	CurrentChild=	Node->first_node("Type");
	Id=getValue(CurrentChild);

	CurrentChild=	Node->first_node("Active");
	if (getValue(CurrentChild)=="true")
	{
		Active=true;
	}
	else
	{
		Active=false;
	}

	CurrentChild=	Node->first_node("Length");
	Length=float(atof(getValue(CurrentChild).c_str()));

	CurrentChild=	Node->first_node("Rotation");
	Rotation=float(atof(getValue(CurrentChild).c_str()));

	CurrentChild=	Node->first_node("VisibilityRange");
	VisibilityRange=float(atof(getValue(CurrentChild).c_str()));

	CurrentChild=	Node->first_node("Id");
	Id=getValue(CurrentChild);

	TempObject=		new Laser(Position, Color, Active, Length, Rotation);

	if (Rotation==0)
	{
		Holder=		new LaserHolder(TempObject, Id, sf::Vector2f(VisibilityRange*2, Length+VisibilityRange*2), sf::Vector2f(-VisibilityRange, -VisibilityRange), Active);
	}
	if (Rotation==90)
	{
		Holder=		new LaserHolder(TempObject, Id, sf::Vector2f(Length+VisibilityRange*2, VisibilityRange*2), sf::Vector2f(-Length-VisibilityRange, -VisibilityRange), Active);
	}
	if (Rotation==180)
	{
		Holder=		new LaserHolder(TempObject, Id, sf::Vector2f(VisibilityRange*2, Length+VisibilityRange*2), sf::Vector2f(-VisibilityRange, -Length-VisibilityRange), Active);
	}
	if (Rotation==270)
	{
		Holder=		new LaserHolder(TempObject, Id, sf::Vector2f(Length+VisibilityRange*2, VisibilityRange*2), sf::Vector2f(-VisibilityRange, -VisibilityRange), Active);
	}
	//Puts the AntiMagnet object into the level's UnitVector
	level.mObjects.push_back(TempObject);
	level.mObjects.push_back(Holder);
}

void	LevelLoader::addPlatform	(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue, Sprite;
	Platform				*TempObject;
	sf::Vector2f			Position, Size, Offset;
	int						Lives;
	bool					Behind=false;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	Size=sf::Vector2f(0,0);
	Offset=sf::Vector2f(0,0);
	CurrentChild=	Node->first_node("Size");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));

		
	}

	CurrentChild=Node->first_node("Offset");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Offset.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Offset.y=((float)atof(CurrentValue.c_str()));
	}
	
	//Initiates the SpriteName
	CurrentChild=	Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);

	Lives=-1;
	CurrentChild=	Node->first_node("Lives");
	if (CurrentChild!=0x0)
	{
		Lives=atoi(getValue(CurrentChild).c_str());
	}

	//Sets if behind
	CurrentChild=	Node->first_node("Behind");
	//If behind is given
	if (CurrentChild!=0x0)
	{
		if (getValue(CurrentChild)=="true")
			Behind=true;
		else if (getValue(CurrentChild)=="false")
			Behind=false;
	}

	//Creates a Platform object
	if (Lives==-1)
	{
		TempObject=		new Platform(Position,Sprite,Size,Offset, Behind);
	}
	else
	{
		TempObject=		new Platform(Lives,Position,Size,Offset, Sprite, Behind);
	}
	//Puts the Platform object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addMeanix	(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue, sprite, sprite2;
	Meanix					*TempObject;
	sf::Vector2f			Position;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	CurrentChild=	Node->first_node("SpriteName");
	sprite=getValue(CurrentChild);

	CurrentChild=	Node->first_node("SpriteName2");
	sprite2=getValue(CurrentChild);

	//Creates a Platform object
	TempObject=		new Meanix(Position, sprite, sprite2, level.getPlayer());
	//Puts the Platform object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}
void LevelLoader::addMiniBot(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	MiniBot					*TempObject;
	sf::Vector2f			Position;
	bool					SideWays;
	float					Length, Rotation;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	CurrentChild=	Node->first_node("Length");
	Length=float(atof(getValue(CurrentChild).c_str()));

	CurrentChild=	Node->first_node("Rotation");
	Rotation=float(atof(getValue(CurrentChild).c_str()));

	CurrentChild=	Node->first_node("SideWays");
	if (getValue(CurrentChild)=="true")
	{
		SideWays=true;
	}
	else
	{
		SideWays=false;
	}

	//Creates a Platform object
	TempObject=		new MiniBot(Position, Rotation, Length, SideWays);
	//Puts the Platform object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addDialogueBox(Level &level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Sprite,Text;
//	DialogueBox				*TempObject;
	sf::Vector2f			Position;
	bool					FadeIn,Visible;
	std::string				Id;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));
	
	//Initiates the SpriteName
	CurrentChild=	Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);

	//Initiates the text
	CurrentChild=	Node->first_node("Text");
	Text=getValue(CurrentChild);

	//Initiates whether to fade the box in or not
	CurrentChild=	Node->first_node("FadeIn");
	FadeIn=true;
	if (getValue(CurrentChild)=="false")
	{
		FadeIn=false;
	}

	//Initiates whether to to make the box invisible or not
	CurrentChild=	Node->first_node("Visible");
	Visible=true;
	if (getValue(CurrentChild)=="false")
	{
		Visible=false;
	}

	CurrentChild=	Node->first_node("Id");
	Id=getValue(CurrentChild);

	std::replace(Text.begin(), Text.end(), '#', '\n');

	//Puts the Dialogue box object into the level's vector
	DialogueBox* tempBox=new DialogueBox(Position,Sprite,Text,FadeIn,Visible, Id);
	level.addDialogueBox(tempBox);
	level.mObjects.push_back(tempBox);
}

void	LevelLoader::addUnit(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Id,Sprite;
	Unit					*TempObject;
	sf::Vector2f			Position, Size, Offset;
	bool					Solid=true, Behind=false;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	Size=sf::Vector2f(0,0);
	Offset=sf::Vector2f(0,0);
	CurrentChild=	Node->first_node("Size");
	if (!CurrentChild==0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));
	

		CurrentChild=	Node->first_node("Offset");
		if (!CurrentChild==0x0)
		{
			CurrentValue=	getValue(CurrentChild->first_node("x"));
			Offset.x=((float)atof(CurrentValue.c_str()));
			CurrentValue=	getValue(CurrentChild->first_node("y"));
			Offset.y=((float)atof(CurrentValue.c_str()));
		}
	}

	//Initiates the SpriteName
	CurrentChild=	Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);
	
	//Initilizes the Id string
	CurrentChild=	Node->first_node("Type");
	Id=getValue(CurrentChild);

	//Sets if solid
	CurrentChild=	Node->first_node("Solid");
	//If solid is given
	if (CurrentChild!=0x0)
	{
		if (getValue(CurrentChild)=="true")
			Solid=true;
		else if (getValue(CurrentChild)=="false")
			Solid=false;
	}

	//Sets if behind
	CurrentChild=	Node->first_node("Behind");
	//If behind is given
	if (CurrentChild!=0x0)
	{
		if (getValue(CurrentChild)=="true")
			Behind=true;
		else if (getValue(CurrentChild)=="false")
			Behind=false;
	}
	
	//Checks if the Unit Uses animation
	if(Node->first_node("Frames")!=0)
	{
		int Frames,Speed;
		Animation* ani;
		CurrentValue=	getValue(Node->first_node("Frames"));
		Frames=(atoi(CurrentValue.c_str()));
		CurrentValue=	getValue(Node->first_node("Speed"));
		Speed=(atoi(CurrentValue.c_str()));
		ani= new Animation(Sprite,Speed,Frames);
		TempObject=		new Unit(Position,Size,Offset,Id,ani, Solid, Behind);
	}
	else
	{
		//Creates an Unit object
		TempObject=		new Unit(Position, Size, Offset,Id,Sprite, Solid, Behind);
	}
	//Puts the Unit object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addCheckpoint(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Id,Sprite;
	Checkpoint				*TempObject;
	sf::Vector2f			Position, Size, Offset;
	bool					Solid=true, Behind=false;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	Size=sf::Vector2f(0,0);
	Offset=sf::Vector2f(0,0);
	CurrentChild=	Node->first_node("Size");
	if (!CurrentChild==0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));
	

		CurrentChild=	Node->first_node("Offset");
		if (!CurrentChild==0x0)
		{
			CurrentValue=	getValue(CurrentChild->first_node("x"));
			Offset.x=((float)atof(CurrentValue.c_str()));
			CurrentValue=	getValue(CurrentChild->first_node("y"));
			Offset.y=((float)atof(CurrentValue.c_str()));
		}
	}
	
	//Initilizes the Id string
	CurrentChild=	Node->first_node("Type");
	Id=getValue(CurrentChild);

	CurrentChild=	Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);

	//Sets if solid
	CurrentChild=	Node->first_node("Solid");
	//If solid is given
	if (CurrentChild!=0x0)
	{
		if (getValue(CurrentChild)=="true")
			Solid=true;
		else if (getValue(CurrentChild)=="false")
			Solid=false;
	}

	//Sets if behind
	CurrentChild=	Node->first_node("Behind");
	//If behind is given
	if (CurrentChild!=0x0)
	{
		if (getValue(CurrentChild)=="true")
			Behind=true;
		else if (getValue(CurrentChild)=="false")
			Behind=false;
	}
	
	//Creates an Unit object
	TempObject=		new Checkpoint(Position, Size, Offset, new Animation(Sprite, 100, 5));
	//Puts the Unit object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addLine(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Id,Sprite;
	Unit					*TempObject;
	sf::Vector2f			Position;
	int						Rotation=0;
	float					Size=0;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size
	CurrentValue=	getValue(Node->first_node("Size"));
	Size=			float(atof(CurrentValue.c_str()));

	//Initiates the Rotation variable
	CurrentValue=	getValue(Node->first_node("Rotation"));
	Rotation=		atoi(CurrentValue.c_str());

	//Creates an Unit object
	TempObject=		new Line(Position,Rotation,Size);
	//Puts the Unit object into the level's UnitVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addTrigger (std::vector<Trigger*> &triggers, std::vector<std::string> &targets,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Sprite;
	sf::Vector2f			Position, Size, Offset;
	std::string				Id;
	std::string				targetObject;
	std::string				Sound;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	Size=sf::Vector2f(0,0);
	Offset=sf::Vector2f(0,0);
	CurrentChild=	Node->first_node("Size");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));

		
	}

	CurrentChild=Node->first_node("Offset");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Offset.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Offset.y=((float)atof(CurrentValue.c_str()));
	}

	CurrentChild=Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);

	CurrentChild=Node->first_node("Id");
	Id=getValue(CurrentChild);

	CurrentChild=Node->first_node("Target");
	targetObject=getValue(CurrentChild);

	CurrentChild=Node->first_node("Sound");
	if (CurrentChild!=0x0)
	{
		Sound=getValue(CurrentChild);
	}

	triggers.push_back(new Trigger(Position, Size, Offset, Id, Sprite, 0x0, Sound));
	targets.push_back(targetObject);
}

void	LevelLoader::addLaserDeactivator (std::vector<Trigger*> &triggers, std::vector<std::string> &targets,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue,Sprite;
	sf::Vector2f			Position, Size, Offset;
	std::string				Id;
	std::string				targetObject;
	float					Rotation;

	//Gets the Position childnode from the GameObject node
	CurrentChild=	Node->first_node("Position");
	//Gets the x Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	//Sets X to CurentValue's value
	Position.x=((float)atof(CurrentValue.c_str()));
	//Gets the y Value from CurrentChild
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	//Sets Y to CurentValue's value
	Position.y=((float)atof(CurrentValue.c_str()));

	//Initiates the Size vector
	Size=sf::Vector2f(0,0);
	Offset=sf::Vector2f(0,0);
	CurrentChild=	Node->first_node("Size");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Size.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Size.y=((float)atof(CurrentValue.c_str()));

		
	}

	CurrentChild=Node->first_node("Offset");
	if (CurrentChild!=0x0)
	{
		CurrentValue=	getValue(CurrentChild->first_node("x"));
		Offset.x=((float)atof(CurrentValue.c_str()));
		CurrentValue=	getValue(CurrentChild->first_node("y"));
		Offset.y=((float)atof(CurrentValue.c_str()));
	}

	CurrentChild=Node->first_node("SpriteName");
	Sprite=getValue(CurrentChild);

	CurrentChild=Node->first_node("Id");
	Id=getValue(CurrentChild);

	CurrentChild=Node->first_node("Target");
	targetObject=getValue(CurrentChild);

	CurrentChild=Node->first_node("Rotation");
	Rotation=float(atof(getValue(CurrentChild).c_str()));

	triggers.push_back(new LaserDeactivator(new Trigger(Position, Size, Offset, Id, new Animation(Sprite, 100, 3), 0x0, ""), Rotation));
	targets.push_back(targetObject);
}