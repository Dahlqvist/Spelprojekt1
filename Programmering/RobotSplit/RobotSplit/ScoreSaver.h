#ifndef	INC_SCORESAVER
#define INC_SCORESAVER
#include "XmlSaver.h"
#include "HighScore.h"

class ScoreSaver
	:public XmlSaver
{
public:
	ScoreSaver(string	File);
	void	saveScore(Highscore&	Source);
	~ScoreSaver(void);
};

#endif