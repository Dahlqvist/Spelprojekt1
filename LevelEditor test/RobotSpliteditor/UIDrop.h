#ifndef	INC_UIDROP
#define	INC_UIDROP
#include"UIItem.h"
#include<vector>
#include<string>

using namespace std;

template<class T>
class UIDrop: public UIItem
{
public:
	UIDrop()
	{
	}

private:
	int				mCurrent;
	vector<T>		mOptions;
	vector<string>	mOptionNames;
};

#endif