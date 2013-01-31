#ifndef INC_UNITWRAP
#define INC_UNITWRAP
#include"Unit.h"
#include"AnimationWrap.h"
class UnitWrap:public Unit	
{
public:
	AnimationWrap getAnimationWraper();
	UnitWrap(Unit&);
	~UnitWrap(void);
};
#endif