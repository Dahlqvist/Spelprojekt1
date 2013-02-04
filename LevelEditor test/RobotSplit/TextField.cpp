#include "TextField.h"


TextField::TextField(Color color,String Base,int Position)
	:mText(Base),mColor(color)
{
	setCurrentPosition(Position);
}


TextField::~TextField(void)
{
}

void	TextField::insertCharacter(const char& Insert)
{
	mText.insert(mCurrentPosition,Insert);
	mCurrentPosition++;
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
	if(mCurrentPosition>0)
	{
		mCurrentPosition--;
	}
	if(!mText.isEmpty())
	{
		mText.erase(mCurrentPosition,1);
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