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
				Object->addIcon(new UnitIcon(getValue(CurrentChild->first_node("Type")),getValue(CurrentChild->first_node("Sprite"))));
			}
		}
		while(CurrentChild!=MenuNode->last_node("Object"));
	}
	return Object;
}