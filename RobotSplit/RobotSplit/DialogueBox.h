#ifndef INC_DIALOGBOX
#define INC_DIALOGBOX

#include "Unit.h"

class DialogueBox: public Unit
{
public:
	DialogueBox(sf::Vector2f position, std::string text, bool fadeIn);

	void update();

	sf::Sprite getSprite();

private:
	int mAlpha;
};

#endif