#ifndef INC_UNITWRAP
#define INC_UNITWRAP
#include"Unit.h"

class UnitWrap:public Unit	
{
public:
	Animation* getAnimation();
	UnitWrap(Unit&);
	~UnitWrap(void);
};
#endif