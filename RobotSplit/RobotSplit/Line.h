#ifndef INC_LINE
#define INC_LINE
#include "unit.h"

using namespace sf;

class Line :public Unit
{
public:
	Line(Vector2f Position,Vector2f Size);
	~Line(void);
};
#endif