#include	<rapidxml_print.hpp>
#include	<fstream>
//#include	<iostream>
#include	<stdlib.h>
#include	<sstream>

#include	"XmlSaver.h"
#include	"Level.h"
#include	"Line.h"
#include	"Laser.h"
#include	"LaserHolder.h"
#include	"UnitWrap.h"
#include	"Player.h"
#include	"Platform.h"
#include	"Trigger.h"
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
		xml_node<> *Background=mDocument.allocate_node(node_element,"Backgrounds");
		addBackground(Source,Background);
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
			}
			else if(VectorCopy[i]->getId()=="LaserHolder")
			{
				addLaser(VectorCopy[i],VectorCopy,Objects);
			}
			else if(VectorCopy[i]->getId()=="Line")
			{
				addLine(VectorCopy[i],Objects);
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

void	XmlSaver::addBackground(Level&	Source,xml_node<>*	Parent)
{
	xml_node<>	*Background;
	for(int i=0;i<Source.getBackground().size();i++)
	{
		Background=mDocument.allocate_node(node_element,"Background");
		//Converts the Name into the Elements value
		xml_node<> *SpriteName=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(Source.getBackground()[i]->draw())));
		Background->append_node(SpriteName);
		//Converts the amount of frames in the background to a c-string for the Elements value
		xml_node<> *Frames=mDocument.allocate_node(node_element,"Frames",modifyInt(Source.getBackgroundWrap().getFrames()));
		Background->append_node(Frames);
		//Converts the speed of the background to c-string for the Element value
		xml_node<> *Speed=mDocument.allocate_node(node_element,"Speed",modifyInt(Source.getBackgroundWrap().getSpeed()));
		Background->append_node(Speed);
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source.getBackground()[i]->draw().getPosition().x))));
		//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source.getBackground()[i]->draw().getPosition().y))));
		Background->append_node(Position);
		Parent->append_node(Background);
	}
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

void	XmlSaver::addLaser			(Unit		*Source,UnitVector& vector,xml_node<>* Parent)
{
	LaserHolder*	laserholder=dynamic_cast<LaserHolder*>(Source);
	Laser*			laser=laserholder->mLaser;
	xml_node<> *Gameobject		=mDocument.allocate_node(node_element,"Unit");
	xml_node<> *Type			=mDocument.allocate_node(node_element,"Type","\"Laser\"");
	xml_node<> *Position		=mDocument.allocate_node(node_element,"Position");
	xml_node<> *Id				=mDocument.allocate_node(node_element,"Id", modifyString(laser->getId()));
	xml_node<> *Active			=mDocument.allocate_node(node_element,"Active");
	xml_node<> *Rotation		=mDocument.allocate_node(node_element,"Rotation");
	xml_node<> *Color			=mDocument.allocate_node(node_element,"Color");
	xml_node<> *VisibilityRange	=mDocument.allocate_node(node_element,"VisibilityRange");
	xml_node<> *Length			=mDocument.allocate_node(node_element,"Length", modifyInt(laser->getLength()));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(laser->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(laser->getPosition().y))));
	//Get Visibility range
		float	visibility=laserholder->getSize().x;
		float	length=visibility>laserholder->getSize().y;
		if(visibility>laserholder->getSize().y)
		{
			length=visibility;
			visibility>laserholder->getSize().y;
		}
		length-=visibility;
		length/=2;
		visibility/=2;
	//
	Gameobject->append_node(Position);
}

void	XmlSaver::addLine			(Unit *Source,xml_node<>* Parent)
{
	//Size needs seperate conversion due to float
	Line*	tSource	=dynamic_cast<Line*>(Source);
	string	sTemp;
	char*	cTemp= new char[5];
	itoa(tSource->getSize()*100,cTemp,10);
	sTemp+=cTemp;
	if(tSource->getSize()<1.0)
	{
		sTemp.insert(sTemp.begin(),'0');
	}
	sTemp.insert(sTemp.begin()+1,'.');
	delete cTemp;
	cTemp=	new	char[sTemp.size()+1];
	strcpy(cTemp,sTemp.c_str());
	//Allocates the Unit,Type,Position,Size and Rotation elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size		=mDocument.allocate_node(node_element,"Size",cTemp);
		xml_node<> *Rotation	=mDocument.allocate_node(node_element,"Roatation",modifyInt(tSource->getRotation()));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Adds the Type element to the Gameobject element
	Gameobject->append_node(Type);
	//Adds the Position, Size and Rotation elements to the Gameobject element
	Gameobject->append_node(Position);
	Gameobject->append_node(Size);
	Gameobject->append_node(Rotation);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Unit"<<endl;
}

void	XmlSaver::addPlatform		(Unit *Source,xml_node<>* Parent)
{
	Platform*	platform=dynamic_cast<Platform*>(Source);
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(platform->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(platform->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Size=0;
		xml_node<> *Offset=0;
		xml_node<> *Lives=0;
		xml_node<> *Behined=0;
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Checks if it should include Offset or Size in the Document
		if(platform->getSize()!=Vector2f(0,0))
		{
			Size		=mDocument.allocate_node(node_element,"Size");
			Size->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getSize().x))));
			Size->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getSize().y))));
		}
		Vector2f	null;
		if(platform->getOffset()!=null)
		{
			Offset		=mDocument.allocate_node(node_element,"Offset");
			Offset->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getOffset().x))));
			Offset->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getOffset().y))));
		}
		if(platform->getLives()>0)
		{
			Lives	=mDocument.allocate_node(node_element,"Lives",modifyInt(platform->getLives()));
		}
		if(platform->isBehind())
		{
			Behined	=mDocument.allocate_node(node_element,"Behind","true");
		}
	//Adds the Position,Type and Sprite elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Position);
	if(Size!=0)
	{
		Gameobject->append_node(Size);
	}
	if(Offset!=0)
	{
		Gameobject->append_node(Offset);
	}
	if(Lives!=0)
	{
		Gameobject->append_node(Lives);
	}
	if(Behined!=0)
	{
		Gameobject->append_node(Behined);
	}
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Platform"<<endl;
}

void	XmlSaver::addUnit			(Unit *Source,xml_node<>* Parent)
{
	string sSolid;
	if(Source->isSolid())
	{
		sSolid="true";
	}
	else
	{
		sSolid="false";
	}
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Frames=0;
		xml_node<> *Speed=0;
		if(UnitWrap(*Source).getAnimation()!=0)
		{
			Speed				=mDocument.allocate_node(node_element,"Speed",modifyInt(UnitWrap(*Source).getAnimation()->mTimePerFrame));
			Frames				=mDocument.allocate_node(node_element,"Frames",modifyInt(UnitWrap(*Source).getAnimation()->mNumFrames));
		}
		xml_node<> *Size=0;
		xml_node<> *Offset=0;
		if(Source->getSize()!=Vector2f(0,0))
		{
			Size		=mDocument.allocate_node(node_element,"Size");
			Size->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
			Size->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
		}
		Vector2f	null;
		if(Source->getOffset()!=null)
		{
			Offset		=mDocument.allocate_node(node_element,"Offset");
			Offset->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getOffset().x))));
			Offset->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getOffset().y))));
		}
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(Source->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Solid		=mDocument.allocate_node(node_element,"Solid",modifyString(sSolid));
		xml_node<> *Behined=0;
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Adds the Type and Sprite elements to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Sprite);
	//Adds the Speed and Frames elements incase of the unit using Animation
	if(UnitWrap(*Source).getAnimation()!=0)
	{
		Gameobject->append_node(Speed);
		Gameobject->append_node(Frames);
	}
	if(Source->isBehind())
	{
		Behined	=mDocument.allocate_node(node_element,"Behind","true");
	}
	//Adds the Position and Size elements to the Gameobject element
	Gameobject->append_node(Position);
	if(Size!=0)
	{
		Gameobject->append_node(Size);
	}
	if(Offset!=0)
	{
		Gameobject->append_node(Offset);
	}
	if(Behined!=0)
	{
		Gameobject->append_node(Behined);
	}
	Gameobject->append_node(Solid);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Unit"<<endl;
}
