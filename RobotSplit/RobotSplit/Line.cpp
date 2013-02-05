#include "Line.h"


Line::Line(Vector2f pos,int rotation,float size):
	Unit(pos,"Line","Line",false)
{
	mSprite.scale(size,1.0);
	mSprite.rotate(rotation);
	mSize=Vector2f(rotation,size);
	mSolid=false;
}


Line::~Line(void)
{
}

float	Line::getSize()const
{
	return	mSize.y;
}

int		Line::getRotation()const
{
	return	mSize.x;
}