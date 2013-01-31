#include "UnitWrap.h"


UnitWrap::UnitWrap(Unit& Source):Unit(Source)
{
}

Animation* UnitWrap::getAnimation()
{
	return mAnimation;
}

UnitWrap::~UnitWrap(void)
{
}
