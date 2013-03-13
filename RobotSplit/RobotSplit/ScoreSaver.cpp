#include "ScoreSaver.h"


ScoreSaver::ScoreSaver(string FileName)
	:XmlSaver(FileName)
{
}


ScoreSaver::~ScoreSaver(void)
{
}

void	ScoreSaver::saveScore(Highscore& Source)
{
	mDocument.append_node(mDocument.allocate_node(node_element,"Level",Source.getLevelName().c_str()));
	xml_node<>	*Entries=mDocument.allocate_node(node_element,"Entries");
	for(HighScoreSet::iterator	it=Source.getEntries().begin();it!=Source.getEntries().end();it++)
	{
		xml_node<>	*Score	=mDocument.allocate_node(node_element,"Score");
		xml_node<>	*Date	=mDocument.allocate_node(node_element,"Date");
		Score->	append_node(mDocument.allocate_node(node_element,"Name",	modifyString(it->getName())));
		Score->	append_node(mDocument.allocate_node(node_element,"Time",	modifyInt(it->getTime())));
		//Sets the date node
		Date->	append_node(mDocument.allocate_node(node_element,"Year",	modifyInt(it->getDate().tm_year)));
		Date->	append_node(mDocument.allocate_node(node_element,"Month",	modifyInt(it->getDate().tm_mon)));
		Date->	append_node(mDocument.allocate_node(node_element,"Day",		modifyInt(it->getDate().tm_mday)));
		Date->	append_node(mDocument.allocate_node(node_element,"Hour",	modifyInt(it->getDate().tm_hour)));
		Date->	append_node(mDocument.allocate_node(node_element,"Minute",	modifyInt(it->getDate().tm_min)));
		Date->	append_node(mDocument.allocate_node(node_element,"Second",	modifyInt(it->getDate().tm_sec)));
		Score->	append_node(Date);
		Entries->append_node(Score);
	}
	mDocument.append_node(Entries);
}