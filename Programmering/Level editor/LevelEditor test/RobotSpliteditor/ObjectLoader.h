#ifndef	INC_OBJECTLOADER
#define	INC_OBJECTLOADER
#include "XmlLoader.h"
#include "UIObjectMenu.h"
using namespace std;
class ObjectLoader :
	public XmlLoader
{
public:
	UIObjectMenu*	getObject(Toolbar*);
	ObjectLoader(string	Filename);
};

#endif