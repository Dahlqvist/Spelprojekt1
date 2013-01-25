#include "LevelLoader.h"

//Includefiles for objects
//#include "TestObject.h"

/*Inactive during development
#include "AntiMagnet.h"
#include "Button.h"
#include "Door.h"
#include "Laser.h"*/
#include "Platform.h"
#include "Player.h"
#include "PlayerPart.h"
/*#include "Lava.h"*/


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
	rapidxml::xml_node<>	*LevelNode,*Gameobject,*BackgroundNode;
	//Gets the Level Node
	LevelNode=		mDocument.first_node("Level");
	//Gets the first GameObject child node to level
	Gameobject=		LevelNode->first_node("Objects")->first_node("GameObject");
	//Initiation of level begins
	//Sets the level's name
	RetLevel.setName(getValue(LevelNode->first_node("Name")));
	//Sets the level's background
	int	Frames,Speed;
	string Filename;
	BackgroundNode=	LevelNode->first_node("Background");
	Frames=			atoi(getValue(BackgroundNode->first_node("Frames")).c_str());
	Speed=			atoi(getValue(BackgroundNode->first_node("Speed")).c_str());
	Filename=		getValue(BackgroundNode->first_node("SpriteName"));
/*	Background*BACK=new Background(Filename,Frames,Speed);
	RetLevel.setBackground(BACK);*/
	RetLevel.getBackgroundWrap().setFrames(Frames);
	RetLevel.getBackgroundWrap().setSpeed(Speed);
	RetLevel.getBackgroundWrap().setName(Filename);
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
		string type;
		type=	getValue(Gameobject->first_node("Type"));
		if(type=="Player")
		{
			addPlayer(RetLevel,Gameobject);
		}
		else if(type=="Door")
		{
			addDoor(RetLevel,Gameobject);
		}
		else if(type=="Button")
		{
			addButton(RetLevel,Gameobject);
		}
		else if(type=="Platform")
		{
			addPlatform(RetLevel,Gameobject);
		}
		else if(type=="Laser")
		{
			addLaser(RetLevel,Gameobject);
		}
		else if(type=="AntiMagnet")
		{
			addAntiMagnet(RetLevel,Gameobject);
		}
		else if(type=="Lava")
		{
			addLava(RetLevel,Gameobject);
		}
		else
		{
		}
	}
	while(Gameobject!=LevelNode->first_node("Objects")->last_node("GameObject"));
	return	RetLevel;
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
/*
void	LevelLoader::addLaser		(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Laser					*TempObject;
	sf::Vector2f			Position, Size;
	bool					Active;
	int						Color;

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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));
	
	//Initializes the Tigger bool
	CurrentChild=	Node->first_node("Trigger");
	CurrentValue=	getValue(CurrentChild);
	Active=(bool)atoi(CurrentValue.c_str());

	//Initializes the Color int
	CurrentChild=	Node->first_node("Color");
	CurrentValue=	getValue(CurrentChild);
	Color=			atoi(CurrentValue.c_str());

	//Creates a Platform object
	TempObject=		new Laser(Position,Size,Active,Color);
	//Puts the Platform object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addButton	(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Button					*TempObject;
	sf::Vector2f			Position, Size;
	bool					Trigger;

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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));
	
	//Initializes the Tigger Bool
	CurrentChild=	Node->first_node("Trigger");
	CurrentValue=	getValue(CurrentChild);
	Trigger=(bool)atoi(CurrentValue.c_str());

	//Creates a Platform object
	TempObject=		new Button(Position,Size,Trigger);
	//Puts the Platform object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}

void	LevelLoader::addDoor		(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Door					*TempObject;
	sf::Vector2f			Position, Size;
	
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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));

	//Creates a Door object
	TempObject=		new Door(Position,Size);
	//Puts the Door object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}
*/
void	LevelLoader::addPlatform	(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Platform				*TempObject;
	sf::Vector2f			Position, Size;

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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));

	//Creates a Platform object
	TempObject=		new Platform(Position,"");
	//Puts the Platform object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}
/*
void	LevelLoader::addAntiMagnet(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	AntiMagnet				*TempObject;
	sf::Vector2f			Position, Size;

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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));

	//Creates an AntiMagnet object
	TempObject=		new AntiMagnet(Position,Size);
	//Puts the AntiMagnet object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}
*/
/*
void	LevelLoader::addLava		(Level	&level,xml_node<>* Node)
{
	rapidxml::xml_node<>	*CurrentChild;
	string					CurrentValue;
	Lava					*TempObject;
	sf::Vector2f			Position, Size;

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
	CurrentValue=	getValue(CurrentChild->first_node("x"));
	Size.x=((float)atof(CurrentValue.c_str()));
	CurrentValue=	getValue(CurrentChild->first_node("y"));
	Size.y=((float)atof(CurrentValue.c_str()));

	//Creates an AntiMagnet object
	TempObject=		new Lava(Position,Size);
	//Puts the AntiMagnet object into the level's ObjectVector
	level.mObjects.push_back(TempObject);
}*/