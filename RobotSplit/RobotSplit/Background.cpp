#include "Background.h"
#include "Animation.h"
//mBackground behöver filnamnet på spritesheet, tid för varje frame,
//samt hur många frames
Background::Background(const std::string& filnamn, int timePerFrame, int numFrames):
	mBackground(new Animation(filnamn, timePerFrame, numFrames))
{
	mCurrentAnimation=mBackground;
	mPos.x = 0;
	mPos.y = 0;
	mCurrentAnimation->setPosition(mPos);
}

Background::~Background()
{
	delete mCurrentAnimation;
}
//Uppdaterar backgrounds animationen så att rätt frame ska visas
void Background::update()
{
	mCurrentAnimation->update();
}
//Renderar sprite
const sf::Sprite& Background::draw() const
{
	return mCurrentAnimation->getSprite();
}