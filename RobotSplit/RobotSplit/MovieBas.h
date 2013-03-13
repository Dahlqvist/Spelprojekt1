#ifndef INC_MOVIEBAS
#define INC_MOVIEBAS

class MovieBas
{
public:
	virtual void update()=0;
	virtual void draw()=0;
	virtual bool playing()=0;
	virtual void countup()=0;
	virtual void endit()=0;
};

#endif