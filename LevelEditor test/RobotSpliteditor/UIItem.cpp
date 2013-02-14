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

std::string	UIItem::getName()
{
	return	mName;
}

UIItem::UIItem(std::string Name)
	:mName(Name),mSelected(false)
{
	mChangeable=true;
}

void	UIItem::setChangeablitiy(bool&	NEW)
{
	mChangeable=NEW;
}

bool	UIItem::getChangeablitiy()const
{
	return	mChangeable;
}