#include "Line.h"


Line::Line(Vector2f pos,Vector2f size):
	Unit(pos,"Line","",false)
{
//	sf::Shape	temp= sf::RectangleShape();
	mSize=size;
}


Line::~Line(void)
{
}
