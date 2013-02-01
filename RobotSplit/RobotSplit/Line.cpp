#include "Line.h"


Line::Line(Vector2f pos,int rotation,float size):
	Unit(pos,"Line","Line",false)
{
	mSprite.scale(size,1.0);
	mSprite.rotate(rotation);
	mSize=Vector2f(rotation,size);
}


Line::~Line(void)
{
}
