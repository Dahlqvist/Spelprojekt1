#ifndef INC_MOVIESTATE
#define INC_MOVIESTATE
#include "State.h"
#include "MovieBas.h"
#include "IntroMovie.h"
#include "StateInput.h"
#include "BankMovie.h"

class MovieState:public State
{
public:
	MovieState();
	virtual void update();
	virtual void render();
	virtual void input();
	void setMovie(std::string movieName);
private:
	StateInput& mStateInput;
	MovieBas* mMovie;
};

#endif