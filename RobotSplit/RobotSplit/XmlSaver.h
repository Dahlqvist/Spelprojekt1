#ifndef	INC_XMLSAVER
#define	INC_XMLSAVER
#include"Level.h"
#include<rapidxml.hpp>

using namespace rapidxml;

class XmlSaver
{
public:
	//Uninitilized constructor								(Done)
	XmlSaver(void);
	//Initilized constructor								(Done)
	XmlSaver(string	Name);
	//Deconstructor											(Done)
	~XmlSaver(void);
	//Sets the name of the file	(don't include filetype)	(Done)
	void	setFilename(const string& NewName);
	//Converts the level to XML
	void	saveLevel(Level &Source);
	//Creates the xml-file in the format (Name).xml			(Done)
	void	createFile();
private:
	//Returns a properly modified string, adding quotations	(Done)
	string	modifyString	(const string &Source);
	//Returns a string of converted int
	string	modifyInt		(const int &Source);
	string	mFilename;
	rapidxml::xml_document<>	mDocument;
	//Functions adding objects to the parameter				(Done)
	void	addPlayer		(Player		*Source,xml_node<>* Parent);
	void	addPlatform		(Unit		*Source,xml_node<>* Parent);
	void	addLaser		(Unit		*Source,xml_node<>* Parent);
/*	void	addButton		(Button		*Source,xml_node<>* Parent);
	void	addDoor			(Door		*Source,xml_node<>* Parent);
	void	addAntiMagnet	(AntiMagnet	*Source,xml_node<>* Parent);
	void	addLava			(Lava		*Source,xml_node<>* Parent);*/
	void	addUnit			(Unit		*Source,xml_node<>* Parent);
};
#endif