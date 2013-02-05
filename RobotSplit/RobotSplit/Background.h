#ifndef INC_BACKGROUND
#define INC_BACKGROUND

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animation;

class Background
{
public:
	Background(const std::string& filnamn, int timePerFrame, int numFrames, sf::Vector2f position);
	~Background();

	void update();
	const sf::Sprite& draw() const;

	void getSprite();
private:
	Animation *mCurrentAnimation;
	Animation *mBackground;
	sf::Vector2f mPos;
};

#endif