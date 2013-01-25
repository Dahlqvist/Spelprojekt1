#include "Animation.h"
#include "TextureManager.h"
//N�r objektet skapas m�ste filnamnet p� vilket spritesheet som
//skall anv�ndas, hur l�ng tid varje frame ska synas, anges i millisekunder,
//samt hur m�nga frames per animation.
Animation::Animation(const std::string& filename, int timePerFrame, int numFrames):
	mTimePerFrame(timePerFrame),
	mNumFrames(numFrames),
	mCurrentFrame(0)
{
	mTexture = TextureManager::getTexture(filename);
	mSprite = TextureManager::getSprite(filename);
	sf::IntRect textureRect(0,0, mTexture.getSize().x/mNumFrames, mTexture.getSize().y);
	mSprite.setTextureRect(textureRect);
}

Animation::~Animation()
{}
//Updaterar animationen s� att r�tt frame visas, m�ste anropas
//vid varje frameupdatering.
void Animation::restart(){
	mFrameTimer.restart();
}
void Animation::update()
{
	if(mFrameTimer.getElapsedTime().asMilliseconds() > mTimePerFrame)
	{
		mFrameTimer.restart();
		mCurrentFrame++;

		if(mCurrentFrame >= mNumFrames)
		{
			mCurrentFrame = 0;
		}
		
		sf::IntRect currentRect = mSprite.getTextureRect();
		currentRect.left = currentRect.width * mCurrentFrame;
		mSprite.setTextureRect(currentRect);
	}
}
//S�tter positionen f�r vart spriten skall visas
//B�r uppdateras med varje frame ifall det animationen kopplas till
//ett objekt som ska r�ra sig.
void Animation::setPosition(const sf::Vector2f& position)
{
	mSprite.setPosition(position);
}
//Returnerar den frame/bild som skall visas
const sf::Sprite& Animation::getSprite() const
{
	return mSprite;
}

const sf::Texture& Animation::getTexture() const
{
	return mTexture;
}