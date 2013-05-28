#ifndef INC_ENDMOVIE
#define INC_ENDMOVIE
#include "MovieBas.h"
#include "Star.h"

class EndMovie:public MovieBas
{
public:
	EndMovie();
	virtual void update();
	virtual void draw();
	virtual bool playing();
	virtual void countup();
	virtual void endit();
	void act();
	void act2();
private:
	sf::RenderWindow& mWindow;
	bool mPlaying;
	float mCounter;
	sf::Sprite mBackground, mBackground2;
};

#endif