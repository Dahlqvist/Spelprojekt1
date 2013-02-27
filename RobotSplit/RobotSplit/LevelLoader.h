#ifndef	INC_LEVELLOADER
#define	INC_LEVELLOADER
#include "xmlloader.h"
#include "Level.h"
#include "Trigger.h"

//Class is Done	(01-23-2013)
class LevelLoader :public XmlLoader
{
public:
	//Uninitiated Constructor								(Done)
	LevelLoader(void);
	//Initiated Constructor									(Done)
	LevelLoader(std::string);
	//Deconstructor											(Done)
	~LevelLoader(void);
	//Creates a Level from the XML-File and returns it		
	Level	getLevel();
private:
	//Functions adding objects to the parameter				(Done)
	vector<Background*>	getBackground();
	void	addPlayer		(Level	&level,xml_node<>* Node);
	void	addPlatform		(Level	&level,xml_node<>* Node);
	void	addLaser		(Level	&level,xml_node<>* Node);
	void	addLine			(Level	&level,xml_node<>* Node);
	void	addDialogueBox	(Level	&level,xml_node<>* Node);
	void	addTrigger		(vector<Trigger*> &triggers,std::vector<std::string> &triggerTargets,xml_node<>* Node);
	void	addLaserDeactivator	(vector<Trigger*> &triggers,std::vector<std::string> &triggerTargets,xml_node<>* Node);
	void	addUnit			(Level	&level,xml_node<>* Node);
	void	addMeanix		(Level	&level,xml_node<>* Node);
	void	addCheckpoint	(Level	&level,xml_node<>* Node);

};

#endif