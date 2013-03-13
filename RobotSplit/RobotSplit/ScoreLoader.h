#pragma once
#include "XmlLoader.h"
#include "HighScore.h"
class ScoreLoader :
	public XmlLoader
{
public:
	ScoreLoader(string	File);
	Highscore	getHighScore();
	~ScoreLoader(void);
};

