#ifndef INC_STATE
#define INC_STATE

#include <iostream>

class State
{
public:
	virtual ~State();
	virtual void update()=0;
	virtual void render()=0;
};

#endif