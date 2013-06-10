#ifndef INC_HIGHSCORESTATE
#define INC_HIGHSCORESTATE
#include	<set>
#include	"Highscore.h"
#include	"State.h"
#include	"Animation.h"

class	StateInput;

class HighscoreState:public State
{
public:
	HighscoreState(std::string fileName);
	~HighscoreState();
	void update();
	void render();
	void input();
	void reInitiate(std::string level,unsigned int time = 0);
private:
	bool				mInput;
	sf::Font			mFont;
	Highscore			mScores;
	Animation			mBackground;
	StateInput&			mStateInput;
	std::string			mFileName;
	HighscoreEntry		*mTempEntry;
	sf::RenderWindow	&mWindow;
};

#endif