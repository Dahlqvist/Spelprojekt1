#ifndef INC_ANIMATION
#define INC_ANIMATION

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Animation
{
public:
	Animation(const std::string& filename, int timePerFrame, int numFrames);
	~Animation();

	void update();
	void setPosition(const sf::Vector2f& position);
	
	const sf::Sprite& getSprite() const;
	const sf::Texture& getTexture() const;

	int getCurrentFrame();
	int getMaxFrame();
	void setCurrentFrame(int q);
	void restart();
	void setAnimate(bool animate);
private:
	sf::Clock mFrameTimer;
	sf::Sprite mSprite;
	sf::Texture mTexture;
	int mTimePerFrame;
	int mNumFrames;
	int mCurrentFrame;
	bool mAnimate;
	friend class LevelSaver;
};

#endif