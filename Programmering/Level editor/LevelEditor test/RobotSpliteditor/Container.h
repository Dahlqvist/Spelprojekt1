#ifndef		INC_CONTAINER
#define		INC_CONTAINER
#include	<SFML\System\Vector2.hpp>
using namespace sf;

template	<class	T>
class	Container
{
public:
	Container()
		:mActivated(false)
	{
	}
	Container(T*	input,Vector2f	original=Vector2f(0,0),Vector2f offset=Vector2f(0,0),bool fromLevel=false)
		:mActivated(true),mInLevel(fromLevel),mOffset(offset),mOriginal(original)
	{
		mTHIS=input;
	}
	bool		isActive()const
	{
		return	mActivated;
	}
	bool		fromLevel()const
	{
		return	mInLevel;
	}
	T*			getObject()
	{
		return mTHIS;
	}
	void		deletePtr()
	{	
		mActivated=false;
		delete mTHIS;
	}
	void		unInitiate()
	{
		mActivated=false;
		mTHIS=0;
	}
	void		setOriginal(const sf::Vector2f& Source)
	{
		mOriginal=Source;
	}
	void		setPtr(T*	NEW,Vector2f	original=Vector2f(0,0),Vector2f offset=Vector2f(0,0),bool fromLevel=false)
	{
		if(isActive())
		{
			delete	mTHIS;
		}
		mInLevel=fromLevel;
		mActivated=true;
		mTHIS=NEW;
		mOffset=offset;
		mOriginal=original;
	}
	Vector2f	getOffset()const
	{
		return	mOffset;
	}
	Vector2f	getOriginal()const
	{
		return	mOriginal;
	}
private:
	T*			mTHIS;
	bool		mActivated,mInLevel;
	Vector2f	mOffset,mOriginal;

};

#endif