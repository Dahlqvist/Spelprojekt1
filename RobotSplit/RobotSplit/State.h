#ifndef INC_STATE
#define INC_STATE

#include <iostream>
#include <SFML/Graphics.hpp>

class State
{
public:
	virtual ~State();
	virtual void update()=0;
	virtual void render(sf::RenderWindow& window)=0;
};

#endif