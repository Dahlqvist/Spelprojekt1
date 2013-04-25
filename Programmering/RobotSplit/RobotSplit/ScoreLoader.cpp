#include "ScoreLoader.h"


ScoreLoader::ScoreLoader(string	FileName)
	:XmlLoader(FileName)
{
}

ScoreLoader::~ScoreLoader(void)
{
}

Highscore	ScoreLoader::getHighScore()
{
	string LevelName=getValue(mDocument.first_node("Level"));
	HighScoreSet	SET;
	bool once=false;
	xml_node<>*	CurrentChild=mDocument.first_node("Entries")->first_node("Score");
	while(CurrentChild!=mDocument.first_node("Entries")->last_node("Score"))
	{
		if(once)
		{
			CurrentChild=CurrentChild->next_sibling();
		}
		else
		{
			once=true;
		}
		tm	tDate;
		string	name=getValue(CurrentChild->first_node("Name"));
		int		time=atoi(getValue(CurrentChild->first_node("Time")).c_str());
		xml_node<>*	nDate=CurrentChild->first_node("Date");
		tDate.tm_year=atoi(getValue(nDate->first_node("Year")).c_str());
		tDate.tm_mon=atoi(getValue(nDate->first_node("Month")).c_str());
		tDate.tm_mday=atoi(getValue(nDate->first_node("Day")).c_str());
		tDate.tm_hour=atoi(getValue(nDate->first_node("Hour")).c_str());
		tDate.tm_min=atoi(getValue(nDate->first_node("Minute")).c_str());
		tDate.tm_sec=atoi(getValue(nDate->first_node("Second")).c_str());
		SET.insert(HighScoreEntry(name,time,tDate));
	}
	return	Highscore(SET,LevelName);
}