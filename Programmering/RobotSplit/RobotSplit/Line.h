#ifndef INC_LINE
#define INC_LINE
#include "unit.h"

using namespace sf;

class Line :public Unit
{
public:
	Line(Vector2f Position,int Rotation,float Size);
	~Line(void);
	int		getRotation()const;
	float	getSize()const;
};
#endif