#ifndef INC_LASERDEACTIVATOR
#define INC_LASERDEACTIVATOR

#include "Trigger.h"

class LaserDeactivator: public Trigger
{
public:
	LaserDeactivator(Trigger* trigger, float rotation);

	float	getRotation(){return mRotation;}
	void hitOnce();
	void hit(){};
	void draw();
	void reset();

private:
	bool mPressed;
	float mRotation;
};

#endif