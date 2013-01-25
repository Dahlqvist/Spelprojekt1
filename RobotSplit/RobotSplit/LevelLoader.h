#ifndef	INC_LEVELLOADER
#define	INC_LEVELLOADER
#include "xmlloader.h"
#include "Level.h"

//Class is Done	(01-23-2013)
class LevelLoader :public XmlLoader
{
public:
	//Uninitiated Constructor
	LevelLoader(void);
	//Initiated Constructor
	LevelLoader(std::string);
	//Deconstructor											(Done)
	~LevelLoader(void);
	//Creates a Level from the XML-File and returns it		(Done)
	Level	getLevel();
private:
	//Functions adding objects to the parameter				(Done)
	void	addPlayer		(Level	&level,xml_node<>* Node);
	void	addLaser		(Level	&level,xml_node<>* Node);
	void	addButton		(Level	&level,xml_node<>* Node);
	void	addDoor			(Level	&level,xml_node<>* Node);
	void	addPlatform		(Level	&level,xml_node<>* Node);
	void	addAntiMagnet	(Level	&level,xml_node<>* Node);
	void	addLava			(Level	&level,xml_node<>* Node);
};

#endif