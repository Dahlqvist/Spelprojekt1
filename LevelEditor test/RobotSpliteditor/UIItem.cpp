#include "UIItem.h"


UIItem::UIItem(void):mSelected(false)
{
}


UIItem::~UIItem(void)
{
}

bool	UIItem::selected()
{
	return	mSelected;
}