#ifndef	INC_OBJECTLOADER
#define	INC_OBJECTLOADER
#include "XmlLoader.h"
using namespace std;
class ObjectLoader :
	public XmlLoader
{
public:
	ObjectLoader(void);
	ObjectLoader(string	Filename);
	~ObjectLoader(void);

};

#endif