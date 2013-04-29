#include "ObjectLoader.h"


ObjectLoader::ObjectLoader(std::string	FileName)
	:XmlLoader(FileName)
{
}


UIObjectMenu*	ObjectLoader::getObject(Toolbar*	Parent)
{
	std::string		Name="Error";
	Vector2f		Size=Vector2f(Parent->getSize());
	rapidxml::xml_node<>	*MenuNode,*CurrentChild;
	MenuNode=mDocument.first_node("Menu");
	if(mFileOpen)
	{
		Name=getValue(MenuNode->first_node("Name"));
		CurrentChild=MenuNode->first_node("Size");
		Size.x=atof(getValue(CurrentChild->first_node("x")).c_str());
		Size.y=atof(getValue(CurrentChild->first_node("y")).c_str());
	}
	UIObjectMenu*	Object=new	UIObjectMenu(Name,Size,Parent);
	CurrentChild=MenuNode->first_node("Object");
	if(mFileOpen)
	{
		bool	oneLoop=false;
		do
		{
			if(oneLoop)
			{
				CurrentChild=CurrentChild->next_sibling();
			}
			else
			{
				oneLoop=true;
			}
			if(getValue(CurrentChild->first_node("Type"))=="Player")
			{
				Object->addIcon(new PlayerIcon());
			}
			else
			{
				int	FPS=1,Speed=0;
				sf::Vector2f	tempSize(0,0),tempOffset(0,0);
				if(CurrentChild->first_node("Frames")!=0x0)
				{
					FPS=atoi(getValue(CurrentChild->first_node("Frames")).c_str());
					Speed=atoi(getValue(CurrentChild->first_node("Speed")).c_str());
				}
				if(CurrentChild->first_node("Size")!=0x0)
				{
					tempSize.x=atoi(getValue(CurrentChild->first_node("Size")->first_node("x")).c_str());
					tempSize.y=atoi(getValue(CurrentChild->first_node("Size")->first_node("y")).c_str());
				}
				if(CurrentChild->first_node("Offset")!=0x0)
				{
					tempOffset.x=atoi(getValue(CurrentChild->first_node("Offset")->first_node("x")).c_str());
					tempOffset.y=atoi(getValue(CurrentChild->first_node("Offset")->first_node("y")).c_str());
				}

				Object->addIcon(new UnitIcon(getValue(CurrentChild->first_node("Type")),getValue(CurrentChild->first_node("Sprite")),tempSize,tempOffset,FPS,Speed));
			}
		}
		while(CurrentChild!=MenuNode->last_node("Object"));
	}
	return Object;
}