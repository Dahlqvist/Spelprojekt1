#include "LaserDeactivator.h"

LaserDeactivator::LaserDeactivator(Trigger* trigger)
	:Trigger(*trigger)
{

}

void LaserDeactivator::hitOnce()
{
	mTriggedObject->deactivate();
}