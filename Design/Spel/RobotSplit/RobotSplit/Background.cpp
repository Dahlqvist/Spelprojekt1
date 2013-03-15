#include "Background.h"
#include "Animation.h"
//mBackground beh�ver filnamnet p� spritesheet, tid f�r varje frame,
//samt hur m�nga frames
Background::Background(const std::string& filnamn, int timePerFrame, int numFrames, sf::Vector2f position):
	mBackground(new Animation(filnamn, timePerFrame, numFrames))
	,mPos(position)
{
	mCurrentAnimation=mBackground;
	mCurrentAnimation->setPosition(mPos);
}

Background::~Background()
{
	delete mCurrentAnimation;
}
//Uppdaterar backgrounds animationen s� att r�tt frame ska visas
void Background::update()
{
	mCurrentAnimation->update();
}
//Renderar sprite
const sf::Sprite& Background::draw() const
{
	return mCurrentAnimation->getSprite();
}