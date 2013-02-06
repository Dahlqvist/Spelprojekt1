#ifndef INC_DIALOGBOX
#define INC_DIALOGBOX

#include "Unit.h"

class DialogueBox: public Unit
{
public:
	DialogueBox(sf::Vector2f position, std::string text, bool fadeIn);

	void update();

	sf::Text getText();
	sf::Sprite getSprite();

private:
	int mAlpha;
	sf::Text mText;
};

#endif