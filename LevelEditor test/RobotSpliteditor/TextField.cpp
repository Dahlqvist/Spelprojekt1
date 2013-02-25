#include "TextField.h"


TextField::TextField(Color color,String Base,int Position)
	:mText(Base),mColor(color)
{
	setCurrentPosition(Position);
}


TextField::~TextField(void)
{
}

void	TextField::clear()
{
	mText.clear();
	mCurrentPosition=0;
}

void	TextField::insertCharacter(const char& Insert)
{
	if(!mText.isEmpty())
	{
		mText.insert(mCurrentPosition,Insert);
		mCurrentPosition++;
	}
	else
	{
		mText+=Insert;
		mCurrentPosition=1;
	}
}

void	TextField::setColor(const Color& nColor)
{
	mColor=nColor;
}

void	TextField::setCurrentPosition(const int& nPosition)
{
	if(0<=nPosition&&nPosition<=mText.getSize())
	{
		mCurrentPosition=nPosition;
	}
}

void	TextField::deleteCharacter()
{
	if(mCurrentPosition>0&&!mText.isEmpty())
	{
		mCurrentPosition--;
	}
	if(!mText.isEmpty())
	{
		mText.erase(mCurrentPosition,1);
	}
	else
	{
		mCurrentPosition=0;
	}
}

Color	TextField::getColor()const
{
	return mColor;
}

String	TextField::getString()const
{
	return mText;
}

int	TextField::getCurrentPosition()const
{
	return mCurrentPosition;
}

int	TextField::getLength()const
{
	return	mText.toAnsiString().size();
}