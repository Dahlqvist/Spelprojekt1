#include "EndMovie.h"

EndMovie::EndMovie():
mWindow(Window::getWindow())
{
	mCounter=0;
	mPlaying=true;

	mBackground=TextureManager::getSprite("CinemaBG6");
	mBackground2=TextureManager::getSprite("CinemaBG5");
}

void EndMovie::update()
{

}

void EndMovie::draw()
{
	mWindow.clear();
	if(mCounter==0)
	{
		mWindow.draw(mBackground);
	}
	else
	{
		mWindow.draw(mBackground2);
	}
	mWindow.display();
}

bool EndMovie::playing()
{
	return mPlaying;
}
void EndMovie::countup()
{
	mCounter++;
	if(mCounter>1)
	{
	 mPlaying=false;
	}
}
void EndMovie::endit()
{
	mPlaying=false;
}