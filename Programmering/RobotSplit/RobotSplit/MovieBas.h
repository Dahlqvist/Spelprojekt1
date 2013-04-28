#ifndef INC_MOVIEBAS
#define INC_MOVIEBAS
#include "Window.h"
#include "TextureManager.h"
#include "Music.h"
#include "Sound.h"

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