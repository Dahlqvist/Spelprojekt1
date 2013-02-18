#ifndef INC_LASERDEACTIVATOR
#define INC_LASERDEACTIVATOR

#include "Trigger.h"

class LaserDeactivator: public Trigger
{
public:
	LaserDeactivator(Trigger* trigger);

	void hitOnce();
};

#endif