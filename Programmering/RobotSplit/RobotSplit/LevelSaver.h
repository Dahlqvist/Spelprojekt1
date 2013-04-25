#ifndef INC_LEVELSAVER
#define	INC_LEVELSAVER
#include"XmlSaver.h"
class LevelSaver:public	XmlSaver
{
public:
	LevelSaver(void);
	LevelSaver(std::string	Name);
	~LevelSaver(void);
	//Converts the level to XML								(Done)
	void	saveLevel(Level &Source);
private:
	//Functions adding objects to the parameter				(Done)
	void	addBackground	(Level&		 Source,xml_node<>* Parent);
	void	addPlayer		(Player		*Source,xml_node<>* Parent);
	void	addPlatform		(Unit		*Source,xml_node<>* Parent);
	void	addLaser		(Unit		*Source,UnitVector& Vector,xml_node<>* Parent);
	void	addLine			(Unit		*Source,xml_node<>* Parent);
	void	addDialogueBox	(Unit		*Source,xml_node<>* Parent);
	void	addTrigger		(Unit		*Source,xml_node<>* Parent);
	void	addMiniBot		(Unit		*Source,xml_node<>* Parent);
	void	addLaserDeactive(Unit		*Source,xml_node<>* Parent);
	void	addUnit			(Unit		*Source,xml_node<>* Parent);
	void	addMeanix		(Unit		*Source,xml_node<>* Parent);
	void	addCheckpoint	(Unit		*Source,xml_node<>* Parent);
};

#endif