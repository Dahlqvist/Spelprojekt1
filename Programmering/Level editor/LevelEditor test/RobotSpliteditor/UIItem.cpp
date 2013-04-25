#include "UIItem.h"


UIItem::UIItem(void):mSelected(false),mChangeable(true)
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

UIItem::UIItem(std::string Name,bool change)
	:mName(Name),mSelected(false),mChangeable(change)
{
}

void	UIItem::setChangeablitiy(bool&	NEW)
{
	mChangeable=NEW;
}

bool	UIItem::getChangeablitiy()const
{
	return	mChangeable;
}

void	UIItem::setSelect(const bool& NEW)
{
	mSelected=NEW;
}