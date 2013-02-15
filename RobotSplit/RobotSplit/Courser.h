#ifndef INC_COURSER
#define INC_COURSER
#include <SFML\Graphics.hpp>

class Courser
{
public:
	Courser();
	sf::Sprite* getSprite();
private:
	sf::Sprite mSprite;
};

#endif