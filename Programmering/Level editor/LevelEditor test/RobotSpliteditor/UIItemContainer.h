#ifndef	INC_UIITEMCONTAINER
#define INC_UIITEMCONTAINER
#include	<set>
#include	"UIItem.h"

class	UIComp
{
public:
	bool operator()(UIItem*,UIItem*);
};

typedef	std::set<UIItem*,UIComp>	UISet;

class	UIItemContainer
{
public:
	UIItemContainer	();
	void	activate	(std::string);
	void	deactivate	(std::string);
	void	activateAll	();
	void	deactivateAll	();
	UISet&	accessActive();
	UIItem*	getActivated(std::string);
	UIItem*	getDeactivated	(std::string);
	UISet&	accessInactive	();
private:
	UISet	mActive,mInactive;
};
#endif