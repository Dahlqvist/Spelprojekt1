#ifndef INC_STATE
#define INC_STATE

#include <iostream>
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual ~State();
	virtual void update()=0;
	virtual void render()=0;
	virtual void input()=0;
};

#endif