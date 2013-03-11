#include	"LevelSaver.h"
#include	"Level.h"
#include	"Line.h"
#include	"Laser.h"
#include	"LaserHolder.h"
#include	"UnitWrap.h"
#include	"Player.h"
#include	"Platform.h"
#include	"Trigger.h"
#include	"TextureManager.h"
#include	"Checkpoint.h"
#include	"Meanix.h"
#include	"DialogueBox.h"
#include	"Trigger.h"
#include	"LaserDeactivator.h"
#include	"MiniBot.h"


LevelSaver::LevelSaver(std::string	Name)
	:XmlSaver(Name)
{
}

LevelSaver::LevelSaver()
	:XmlSaver()
{
}

LevelSaver::~LevelSaver(void)
{
}


void	LevelSaver::saveLevel(Level &Source)
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
			else if(VectorCopy[i]->getId()=="Line")
			{
			//	addLine(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="DialogueBox")
			{
				addDialogueBox(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="Trigger")
			{
				addTrigger(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="Meanix")
			{
				addMeanix(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="Checkpoint")
			{
				addCheckpoint(VectorCopy[i],Objects);
			}
			else if(VectorCopy[i]->getId()=="MiniBot")
			{
				addMiniBot(VectorCopy[i],Objects);
			}
			else if(dynamic_cast<LaserDeactivator*>(VectorCopy[i])!=0)
			{
				addLaserDeactive(VectorCopy[i],Objects);
			}
			else if(dynamic_cast<Laser*>(VectorCopy[i])!=0)
			{
			}
			else if(dynamic_cast<LaserHolder*>(VectorCopy[i])!=0)
			{
				addLaser(VectorCopy[i],VectorCopy,Objects);
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

void	LevelSaver::addBackground	(Level&	Source,xml_node<>*	Parent)
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

void	LevelSaver::addPlayer		(Player	*Source,xml_node<>* Parent)
{
	//Allocates the Unit and Position elements in the Xml document
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type","\"Player\"");
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getCollisionSprite()[0]->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getCollisionSprite()[0]->getPosition().y))));
	//Adds the Position element to the Gameobject element
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Parent->	append_node(Gameobject);
	//std::cout<<"Adds Player"<<endl;
}

void	LevelSaver::addLaser		(Unit	*Source,UnitVector& vector,xml_node<>* Parent)
{
	LaserHolder*	laserholder=dynamic_cast<LaserHolder*>(Source);
	Laser*			laser=laserholder->getLaser();
	xml_node<> *Gameobject		=mDocument.allocate_node(node_element,"Unit");
	xml_node<> *Type			=mDocument.allocate_node(node_element,"Type",modifyString("Laser"));
	xml_node<> *Position		=mDocument.allocate_node(node_element,"Position");
	xml_node<> *Id				=mDocument.allocate_node(node_element,"Id", modifyString(laserholder->getId()));
	xml_node<> *Active			=mDocument.allocate_node(node_element,"Active");
	xml_node<> *Rotation		=mDocument.allocate_node(node_element,"Rotation");
	xml_node<> *Color			=mDocument.allocate_node(node_element,"Color");
	xml_node<> *VisibilityRange	=mDocument.allocate_node(node_element,"VisibilityRange");
	xml_node<> *Length			=mDocument.allocate_node(node_element,"Length", modifyInt(laser->getLength()));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(laser->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(laser->getPosition().y))));
	//Get Visibility range, length and rotaiton angle.
		int		angle=laser->getRotation();
		float	visibility=laserholder->getSize().x;
		float	length=laserholder->getLaser()->getLength();
		switch(angle)
		{
		case 0:
			visibility=laserholder->getSize().x;
			break;
		case 90:
			visibility=laserholder->getSize().y;
			break;
		case 180:
			visibility=laserholder->getSize().x;
			break;
		case 270:
			visibility=laserholder->getSize().y;
			break;
		}
		visibility=visibility/2;
		//Sets the rotation, visibility range and length to their nodes
		Rotation->value(modifyInt(angle));
		VisibilityRange->value(modifyInt(visibility));
		Length->value(modifyInt(length));
	//Sets the Color node's Value
		int ColLength=3;
		if(Source->getId().find("Blue")<Source->getId().length())
		{
			ColLength=4;
		}
		else if(Source->getId().find("Yellow")<Source->getId().length())
		{
			ColLength=6;
		}
		Color->value(modifyString(Source->getId().substr(5,ColLength)));
	//Set wether the laser is active or not
		if(laserholder->isActive())
		{
			Active->value(modifyString("true"));
		}
		else
		{
			Active->value(modifyString("false"));
		}

	//Adds the nodes to Gameobject node
	Gameobject->append_node(Position);
	Gameobject->append_node(Type);
	Gameobject->append_node(Id);
	Gameobject->append_node(Active);
	Gameobject->append_node(Rotation);
	Gameobject->append_node(Color);
	Gameobject->append_node(VisibilityRange);
	Gameobject->append_node(Length);
	//Adds the Gameobject node to the Parent Node
	Parent->append_node(Gameobject);
}

void	LevelSaver::addLine		(Unit	*Source,xml_node<>* Parent)
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

void	LevelSaver::addPlatform	(Unit	*Source,xml_node<>* Parent)
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

void	LevelSaver::addUnit		(Unit	*Source,xml_node<>* Parent)
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

void	LevelSaver::addCheckpoint	(Unit	*Source,xml_node<>* Parent)
{
	//Checks if offset and size is specified
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
	//Generates Nodes
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(Source->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));


	//Adds the nodes to the Gameobject node
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Sprite);
	if(Size!=0)
	{
		Gameobject->append_node(Size);
	}
	if(Offset!=0)
	{
		Gameobject->append_node(Offset);
	}
	Parent->append_node(Gameobject);
}

void	LevelSaver::addDialogueBox(Unit	*Source,xml_node<>* Parent)
{
	DialogueBox*	box=dynamic_cast<DialogueBox*>(Source);
	//Generates Nodes
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(dynamic_cast<Checkpoint*>(Source)->getSprite())));
		xml_node<> *Text		=mDocument.allocate_node(node_element,"Text",modifyString(box->getText().getString()));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *FadeIn		=mDocument.allocate_node(node_element,"FadeIn");
		xml_node<> *Visible		=mDocument.allocate_node(node_element,"Visible");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Sets the FadeIn node's value
		if(box->mFadeIn)
		{
			FadeIn->value("true");
		}
		else
		{
			FadeIn->value("false");
		}
	//Sets the FadeIn node's value
		if(box->mVisible)
		{
			Visible->value("true");
		}
		else
		{
			Visible->value("false");
		}
	//Adds the nodes to the Gameobject node
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Text);
	Gameobject->append_node(FadeIn);
	Gameobject->append_node(Visible);
	Parent->append_node(Gameobject);
}

void	LevelSaver::addMeanix		(Unit	*Source,xml_node<>* Parent)
{
	xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
	xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
	xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	Parent->append_node(Gameobject);
}

void	LevelSaver::addTrigger	(Unit	*Source,xml_node<>* Parent)
{
	Trigger*	trigger=dynamic_cast<Trigger*>(Source);
	//Checks if offset and size is specified
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
	//Generates Nodes
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString(Source->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(trigger->getSprite())));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Id			=mDocument.allocate_node(node_element,"Id",modifyString(trigger->getTargetId()));
		xml_node<> *Target		=mDocument.allocate_node(node_element,"Target",modifyString(trigger->getId()));
		xml_node<> *Sound		=mDocument.allocate_node(node_element,"Sound",modifyString(trigger->getSound()));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));


	//Adds the nodes to the Gameobject node
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	if(Size!=0)
	{
		Gameobject->append_node(Size);
	}
	if(Offset!=0)
	{
		Gameobject->append_node(Offset);
	}
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Id);
	Gameobject->append_node(Target);
	Gameobject->append_node(Sound);
	Parent->append_node(Gameobject);
}

void	LevelSaver::addLaserDeactive(Unit	*Source,xml_node<>* Parent)
{
	LaserDeactivator*	trigger=dynamic_cast<LaserDeactivator*>(Source);
	//Checks if offset and size is specified
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
	//Generates Nodes
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString("LaserDeactivator"));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Id			=mDocument.allocate_node(node_element,"Id",modifyString(trigger->getId()));
		xml_node<> *Sprite		=mDocument.allocate_node(node_element,"SpriteName",modifyString(TextureManager::getSpriteName(trigger->getSprite())));
		xml_node<> *Target		=mDocument.allocate_node(node_element,"Target",modifyString(trigger->getTargetId()));
		xml_node<> *Sound		=mDocument.allocate_node(node_element,"Sound",modifyString(trigger->getSound()));
		xml_node<> *Rotation	=mDocument.allocate_node(node_element,"Rotation",modifyInt(trigger->getRotation()));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));


	//Adds the nodes to the Gameobject node
	Gameobject->append_node(Type);
	Gameobject->append_node(Position);
	if(Size!=0)
	{
		Gameobject->append_node(Size);
	}
	if(Offset!=0)
	{
		Gameobject->append_node(Offset);
	}
	Gameobject->append_node(Sprite);
	Gameobject->append_node(Id);
	Gameobject->append_node(Rotation);
	Gameobject->append_node(Target);
	Gameobject->append_node(Sound);
	Parent->append_node(Gameobject);
}

void	LevelSaver::addMiniBot	(Unit	*Source,xml_node<>* Parent)
{
	MiniBot*	MINI=dynamic_cast<MiniBot*>(Source);
	string sSide;
	if(MINI->mSideways)
	{
		sSide="true";
	}
	else
	{
		sSide="false";
	}
		xml_node<> *Gameobject	=mDocument.allocate_node(node_element,"Unit");
		xml_node<> *Type		=mDocument.allocate_node(node_element,"Type",modifyString("MiniBot"));
		xml_node<> *Length		=mDocument.allocate_node(node_element,"Length",modifyInt(MINI->mLength));
		xml_node<> *Rotation	=mDocument.allocate_node(node_element,"Rotation",modifyInt(MINI->mRotation));
		xml_node<> *Position	=mDocument.allocate_node(node_element,"Position");
		xml_node<> *Sideways	=mDocument.allocate_node(node_element,"SideWays",modifyString(sSide));
	//Adds the x element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"x",modifyInt(int(Source->getPosition().x))));
	//Adds the y element into the Position element
		Position->append_node(mDocument.allocate_node(node_element,"y",modifyInt(int(Source->getPosition().y))));
	//Adds nodes to the Gameobject node
		Gameobject->append_node(Type);
		Gameobject->append_node(Position);
		Gameobject->append_node(Length);
		Gameobject->append_node(Rotation);
		Gameobject->append_node(Sideways);
		Parent->append_node(Gameobject);
}