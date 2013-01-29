#include	<rapidxml_print.hpp>
#include	<fstream>
//#include	<iostream>
#include	<stdlib.h>
#include	"XmlSaver.h"
#include	"Level.h"
#include	"Unit.h"
#include	"Player.h"
#include	"Platform.h"
#include	"TextureManager.h"

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
	//Writes the Document for quick checking of it before the program closes
//	//std::cout<<mDocument;
//	system("PAUSE");
	//Creates the file to write to
	std::ofstream	file(mFilename);
	//Sets the standard of xml on the file
	file<<"<?xml version=\"1.0\"?>"<<endl;
	//Writes the document to the file
	file<<mDocument;
	file.close();
}

void	XmlSaver::saveLevel(Level &Source)
{
	xml_node<> *Level=mDocument.allocate_node(node_element,"Level");
	xml_node<> *Objects=mDocument.allocate_node(node_element,"Objects");
	//Sets the Name element
		xml_node<> *Name=mDocument.allocate_node(node_element,"Name",modifyString(Source.getName()));
		Level->append_node(Name);

	//Sets the Background element's child elements and values
		xml_node<> *Background=mDocument.allocate_node(node_element,"Background");
	//Converts the amount of frames in the background to a c-string for the Elements value
		xml_node<> *Frames=mDocument.allocate_node(node_element,"Frames",modifyInt(Source.getBackgroundWrap().getFrames()));
		Background->append_node(Frames);
	//Converts the speed of the background to c-string for the Element value
		xml_node<> *Speed=mDocument.allocate_node(node_element,"Speed",modifyInt(Source.getBackgroundWrap().getSpeed()));
		Background->append_node(Speed);
	//Converts the Name into the Elements value
		xml_node<> *SpriteName=mDocument.allocate_node(node_element,"SpriteName",modifyString(Source.getBackgroundWrap().getName()));
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

char*	XmlSaver::modifyString(const string &Source)
{
	string temp;
	temp="\""+Source+"\"";
	char *ret = new char[temp.size()+1];
	strcpy(ret,temp.c_str());
	return ret;
}

char*	XmlSaver::modifyInt(const int &Source)
{
	char	*tempValue=	new char[256];
	itoa(Source,tempValue,10);
	return	tempValue;
}

void	XmlSaver::addPlayer			(Player		*Source,xml_node<>* Parent)
{
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type","\"Player\"");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getCollisionSprite()[0]->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(64+Source->getCollisionSprite()[0]->getPosition().y))));
	//Adds the Position element to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Player"<<endl;
}

void	XmlSaver::addLaser			(Unit *Source,xml_node<>* Parent)
{
	//std::cout<<"Adds Laser"<<endl;
}

void	XmlSaver::addPlatform		(Unit *Source,xml_node<>* Parent)
{
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(Source->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Adds the x element into the Size element
		Size->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getSize().x))));
	//Adds the y element into the Size element
		Size->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getSize().y))));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Platform"<<endl;
}

void	XmlSaver::addUnit		(Unit *Source,xml_node<>* Parent)
{
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(Source->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Adds the x element into the Size element
		Size->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getSize().x))));
	//Adds the y element into the Size element
		Size->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getSize().y))));
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Unit"<<endl;
}
