#include	"UIItemContainer.h"

using namespace std;

bool UIComp::operator()(UIItem* ItemLess,UIItem* ItemMore)
{
	bool	ReturnBool=true;
	if(ItemLess->getChangeablitiy()==ItemMore->getChangeablitiy())
	{
		if(ItemLess->getName()=="Name")
		{
			ReturnBool==true;
		}
		else
		{
			ReturnBool=ItemLess->getName()<ItemMore->getName();
		}
	}
	else
	{
		ReturnBool=ItemMore->getChangeablitiy();
	}
	return ReturnBool;
}

UISet&	UIItemContainer::accessActive()
{
	return	mActive;
}

UISet&	UIItemContainer::accessInactive()
{
	return	mInactive;
}

UIItem*	UIItemContainer::getActivated(std::string Name)
{
	for(UISet::iterator	it=mActive.begin();it!=mActive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			return	*it;
		}
	}
	return	0;
}

UIItem*	UIItemContainer::getDeactivated(std::string Name)
{
	for(UISet::iterator	it=mInactive.begin();it!=mInactive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			return	*it;
		}
	}
	return	0;
}

void	UIItemContainer::deactivate(std::string Name)
{
	for(UISet::iterator	it=mActive.begin();it!=mActive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			mInactive.insert(*it);
			mActive.erase(it);
			break;
		}
	}
}

void	UIItemContainer::activate(std::string Name)
{
	for(UISet::iterator	it=mInactive.begin();it!=mInactive.end();it++)
	{
		if((*it)->getName()==Name)
		{
			mActive.insert(*it);
			mInactive.erase(it);
			break;
		}
	}
}

UIItemContainer::UIItemContainer()
{
}