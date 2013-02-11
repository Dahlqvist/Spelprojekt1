#ifndef INC_DIALOGBOX
#define INC_DIALOGBOX

#include "Unit.h"

class DialogueBox: public Unit
{
public:
	DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible);

	void update();
	void hit();
	void activate();
	
	sf::Text getText();
	sf::Sprite getSprite();

	bool isFullyVisible();

private:
	int mAlpha;
	bool mVisible, mFadeIn;

	sf::Text mText;
};

#endif