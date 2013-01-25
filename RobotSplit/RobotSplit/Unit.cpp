#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, bool solid)
	:GameObject()
	,mSolid(solid)
{
	mPosition=position;
	mId=id;
}