#include	<rapidxml_print.hpp>
#include	<fstream>
#include	<iostream>
#include	<stdlib.h>
#include	"XmlSaver.h"
#include	"Level.h"
#include	"Unit.h"
#include	"Player.h"
#include	"Platform.h"

using namespace rapidxml;

XmlSaver::XmlSaver(void)
	:mDocument()
{
}

XmlSaver::XmlSaver(string Filename)
	:mDocument()
{
	setFilename(Filename);
}


XmlSaver::~XmlSaver(void)
{
}

void	XmlSaver::setFilename(const string& NewName)
{
	mFilename=NewName+".xml";
}

void	XmlSaver::createFile()
{
	std::cout<<mDocument;
	system("PAUSE");
	std::ofstream	file(mFilename);
	//Sets the standard of xml on the file
	file<<"<?xml version=\"1.0\"?>"<<endl;
	file<<mDocument;
	file.close();
}

void	XmlSaver::saveLevel(Level &Source)
{
	xml_node<> *Level=mDocument.allocate_node(node_element,"Level");
	xml_node<> *Objects=mDocument.allocate_node(node_element,"Objects");
	char*	temp;
	string	tempValueS;
	//Sets the Name element
		tempValueS=modifyString(Source.getName());
		temp=new char[tempValueS.length()+1];
		strcpy(temp,tempValueS.c_str());
		xml_node<> *Name=mDocument.allocate_node(node_element,"Name",temp);
		Level->append_node(Name);

	//Sets the Background element's child elements and values
		xml_node<> *Background=mDocument.allocate_node(node_element,"Background");
	//Converts the amount of frames in the background to a c-string for the Elements value
		tempValueS=modifyInt(Source.getBackgroundWrap().getFrames());
		temp=new char[tempValueS.length()+1];
		strcpy(temp,tempValueS.c_str());
		xml_node<> *Frames=mDocument.allocate_node(node_element,"Frames",temp);
		Background->append_node(Frames);
	//Converts the speed of the background to c-string for the Element value
		tempValueS=modifyInt(Source.getBackgroundWrap().getSpeed());
		temp=new char[tempValueS.length()+1];
		strcpy(temp,tempValueS.c_str());
		xml_node<> *Speed=mDocument.allocate_node(node_element,"Speed",temp);
		Background->append_node(Speed);
	//Converts the Name into the Elements value
		tempValueS=modifyString(Source.getBackgroundWrap().getName());
		temp=new char[tempValueS.length()+1];
		strcpy(temp,tempValueS.c_str());
		xml_node<> *SpriteName=mDocument.allocate_node(node_element,"SpriteName",temp);
		Background->append_node(SpriteName);
	//Inserts the Background element into Level element
		Level->append_node(Background);
		
	//Enters the Units to Xml documents
		//Adds the Player to the Xml
		addPlayer(Source.getPlayer(),Objects);
		//Goes through the Objects
		UnitVector	VectorCopy;
		VectorCopy=		Source.getObjects();
		//Calls on the Unit adding functions
		for(UnitVector::size_type i=0;i<VectorCopy.size();i++)
		{
			if(VectorCopy[i]->getId()=="Platform")
			{
				addPlatform(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="Laser")
			{
				addLaser(VectorCopy[i],Objects);
			}
			else
			{
				addUnit(VectorCopy[i],Objects);
			}
		}
		Level->append_node(Objects);
	//Inserts the Level element into the XML document
	mDocument.append_node(Level);
}

string	XmlSaver::modifyString(const string &Source)
{
	string temp;
	temp="\""+Source+"\"";
	return temp;
}

string	XmlSaver::modifyInt(const int &Source)
{
	string	output;
	char	*tempValue=	new char[256];
	itoa(Source,tempValue,10);
	output=tempValue;
	return	output;
}

void	XmlSaver::addPlayer			(Player		*Source,xml_node<>* Parent)
{
	char	*temp;
	//Starts converting the vector to strings
	string	pY,pX;
	pX=	modifyInt((int)Source->getCollisionSprite()[0]->getPosition().x);
	pY=	modifyInt((int)Source->getCollisionSprite()[0]->getPosition().y);
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type","\"Player\"");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
	//Adds the x element into the Position element
		temp	=new char[pX.length()+1];
		strcpy	(temp,pX.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Position element
		temp	=new char[pY.length()+1];
		strcpy	(temp,pY.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the Position element to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Parent->	append_node(Gameobject);
	std::cout<<"Adds Player"<<endl;
}
void	XmlSaver::addLaser			(Unit *Source,xml_node<>* Parent)
{
	std::cout<<"Adds Laser"<<endl;
}
void	XmlSaver::addPlatform		(Unit *Source,xml_node<>* Parent)
{
	char	*temp;
	//Starts converting the vector to strings
	string	pY,pX,sX,sY,sType,sSprite;
	pX=	modifyInt((int)Source->getPosition().x);
	pY=	modifyInt((int)Source->getPosition().y);
	sX=	modifyInt((int)Source->getSize().x);
	sY=	modifyInt((int)Source->getSize().y);
	sType=modifyString(Source->getId());
	temp=new char[sType.size()+1];
	strcpy(temp,sType.c_str());
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",temp);
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		temp	=new char[pX.length()+1];
		strcpy	(temp,pX.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Position element
		temp	=new char[pY.length()+1];
		strcpy	(temp,pY.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the x element into the Position element
		temp	=new char[sX.length()+1];
		strcpy	(temp,sX.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Size element
		temp	=new char[sY.length()+1];
		strcpy	(temp,sY.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	std::cout<<"Adds Platform"<<endl;
}
void	XmlSaver::addUnit		(Unit *Source,xml_node<>* Parent)
{
	char	*temp;
	//Starts converting the vector to strings
	string	pY,pX,sX,sY,sSprite,sType;
	pX=	modifyInt((int)Source->getPosition().x);
	pY=	modifyInt((int)Source->getPosition().y);
	sX=	modifyInt((int)Source->getSize().x);
	sY=	modifyInt((int)Source->getSize().y);
	sType=modifyString(Source->getId());
	temp=new char[sType.size()+1];
	strcpy(temp,sType.c_str());
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"GameObject");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",temp);
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		temp	=new char[pX.length()+1];
		strcpy	(temp,pX.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Position element
		temp	=new char[pY.length()+1];
		strcpy	(temp,pY.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the x element into the Position element
		temp	=new char[sX.length()+1];
		strcpy	(temp,sX.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Size element
		temp	=new char[sY.length()+1];
		strcpy	(temp,sY.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	std::cout<<"Adds Unit"<<endl;
}
/*
void	XmlSaver::addButton			(Button *Source,xml_node<>* Parent)
{
	std::cout<<"Adds Button"<<endl;
}

void	XmlSaver::addDoor			(Door *Source,xml_node<>* Parent)
{
		char	*temp;
	//Starts converting the vector to strings
	string	pY,pX,sX,sY;
	pX=	modifyInt((int)Source->getPosition().x);
	pY=	modifyInt((int)Source->getPosition().y);
	sX=	modifyInt((int)Source->getSize().x);
	sY=	modifyInt((int)Source->getSize().y);
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type","\"Door\"");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		temp	=new char[pX.length()+1];
		strcpy	(temp,pX.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Position element
		temp	=new char[pY.length()+1];
		strcpy	(temp,pY.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the x element into the Position element
		temp	=new char[sX.length()+1];
		strcpy	(temp,sX.c_str());
		Size->	append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Size element
		temp	=new char[sY.length()+1];
		strcpy	(temp,sY.c_str());
		Size->	append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	std::cout<<"Adds Door"<<endl;
}

void	XmlSaver::addAntiMagnet		(AntiMagnet *Source,xml_node<>* Parent)
{
	std::cout<<"Adds AntiMagnet"<<endl;
}

void	XmlSaver::addLava			(Lava *Source,xml_node<>* Parent)
{	
	char	*temp;
	//Starts converting the vector to strings
	string	pY,pX,sX,sY;
	pX=	modifyInt((int)Source->getPosition().x);
	pY=	modifyInt((int)Source->getPosition().y);
	sX=	modifyInt((int)Source->getSize().x);
	sY=	modifyInt((int)Source->getSize().y);
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type","\"Lava\"");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		temp	=new char[pX.length()+1];
		strcpy	(temp,pX.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Position element
		temp	=new char[pY.length()+1];
		strcpy	(temp,pY.c_str());
		Position->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the x element into the Position element
		temp	=new char[sX.length()+1];
		strcpy	(temp,sX.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"x",temp));
	//Adds the y element into the Size element
		temp	=new char[sY.length()+1];
		strcpy	(temp,sY.c_str());
		Size->append_node(mDocument.allocate_node(node_element,"y",temp));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	std::cout<<"Adds Lava"<<endl;
}*/