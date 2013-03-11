#ifndef INC_LASERDEACTIVATOR
#define INC_LASERDEACTIVATOR

#include "Trigger.h"

class LaserDeactivator: public Trigger
{
public:
	LaserDeactivator(Trigger* trigger, float rotation);

	float	getRotation(){return mRotation;}
	void hitOnce();
	void hit(){}
	void draw();
	void reset();
	void setReset();
	
	void setRotation(float rotation);
private:
	bool mPressed, mStartPressed;
	float mRotation;
	friend class Toolbar;
};

#endif