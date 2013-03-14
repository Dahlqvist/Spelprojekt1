#include	"UIItemContainer.h"

using namespace std;

bool UIComp::operator()(UIItem* ItemLess,UIItem* ItemMore)
{
	bool	ReturnBool=true;
	if(ItemLess->getChangeablitiy()==ItemMore->getChangeablitiy())
	{
		if(ItemLess->getName()=="Update"||ItemMore->getName()=="Update")
		{
			if(ItemLess->getName()=="Update")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
		}
		else if(ItemLess->getName()=="Clear"||ItemMore->getName()=="Clear")
		{
			if(ItemLess->getName()=="Clear")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
		}
		else if(ItemLess->getName()=="Delete"||ItemMore->getName()=="Delete")
		{
			if(ItemLess->getName()=="Delete")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
		}
		else if(ItemLess->getName()=="Name"||ItemMore->getName()=="Name")
		{
			if(ItemLess->getName()=="Name")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
		}
		else if(ItemLess->getName()=="Position x"||ItemMore->getName()=="Position x")
		{
			if(ItemLess->getName()=="Position x")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
		}
		else if(ItemLess->getName()=="Position y"||ItemMore->getName()=="Position y")
		{
			if(ItemLess->getName()=="Position y")
			{
				ReturnBool==true;
			}
			else
			{
				ReturnBool=false;
			}
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
			it=mInactive.begin();
			break;
		}
	}
}

void	UIItemContainer::deactivateAll()
{
	UISet::iterator	it=mActive.begin();
	while(it!=mActive.end())
	{
		mInactive.insert(*it);
		mActive.erase(it);
		it=mActive.begin();
	}
}

void	UIItemContainer::activateAll()
{
	UISet::iterator	it=mInactive.begin();
	while(it!=mInactive.end())
	{
		mActive.insert(*it);
		mInactive.erase(it);
		it=mInactive.begin();
	}
}

UIItemContainer::UIItemContainer()
{
}