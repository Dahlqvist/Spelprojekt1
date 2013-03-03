#ifndef	INC_XMLSAVER
#define	INC_XMLSAVER
#include	"Level.h"
#include	<rapidxml.hpp>

using namespace rapidxml;

//Class is Done 2013-01-29
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
	//Converts the level to XML								(Done)
	void	saveLevel(Level &Source);
	//Creates the xml-file in the format (Name).xml			(Done)
	void	createFile();
private:
	//Returns a properly modified string, adding quotations	(Done)
	char*	modifyString	(const string &Source);
	//Returns a string of converted int
	char*	modifyInt		(const int &Source);
	//Member variable
	string	mFilename;
	rapidxml::xml_document<>	mDocument;
	//Functions adding objects to the parameter				(Done)
	void	addBackground	(Level&		 Source,xml_node<>* Parent);
	void	addPlayer		(Player		*Source,xml_node<>* Parent);
	void	addPlatform		(Unit		*Source,xml_node<>* Parent);
	void	addLaser		(Unit		*Source,UnitVector& Vector,xml_node<>* Parent);
	void	addLine			(Unit		*Source,xml_node<>* Parent);
	void	addDialougeBox	(Unit		*Source,xml_node<>* Parent);
	void	addTrigger		(Unit		*Source,xml_node<>* Parent);
	void	addLaserDeactive(Unit		*Source,xml_node<>* Parent);
	void	addUnit			(Unit		*Source,xml_node<>* Parent);
	void	addMeanix		(Unit		*Source,xml_node<>* Parent);
	void	addCheckpoint	(Unit		*Source,xml_node<>* Parent);
};
#endif