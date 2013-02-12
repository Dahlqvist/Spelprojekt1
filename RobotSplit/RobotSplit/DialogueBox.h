#ifndef INC_DIALOGBOX
#define INC_DIALOGBOX

#include "Unit.h"

class DialogueBox: public Unit
{
public:
	DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible, std::string id);

	void update();
	void hit();
	void activate();
	void deactivate();
	
	sf::Text getText();
	sf::Sprite getSprite();

	bool isFullyVisible();

private:
	int mAlpha;
	bool mVisible, mFadeIn, mDeactivated;

	sf::Text mText;
};

#endif