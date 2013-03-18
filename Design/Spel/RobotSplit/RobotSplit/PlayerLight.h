#ifndef INC_PLAYERLIGHT
#define INC_PLAYERLIGHT
#include <SFML\Graphics.hpp>

class PlayerLight
{
public:
	PlayerLight();
	void setSprite(bool together, bool bodyActive, bool attachedWall, int wall, sf::Vector2f Pos);
	sf::Sprite* getSprite();
private:
	sf::Sprite* mActiveLight;
	sf::Sprite mLightTogether;
	sf::Sprite mLightBody;
	sf::Sprite mLightFeet;
};

#endif