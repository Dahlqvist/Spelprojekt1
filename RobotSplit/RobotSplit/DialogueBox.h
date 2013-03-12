#ifndef INC_DIALOGBOX
#define INC_DIALOGBOX

#include "Unit.h"

class DialogueBox: public Unit
{
public:
	DialogueBox(sf::Vector2f position, std::string spriteName, std::string text, bool fadeIn, bool visible, std::string id);

	void update();
	void activate();
	void deactivate();
	void reset();
	void setReset();
	
	sf::Text getText();
	sf::Sprite getSprite();

	bool isFullyVisible();

	bool	getVisible();
	bool	getFadeIn();
	
	void	setFadeIn(bool);
	void	setVisible(bool);
	void	forceAlpha(sf::Uint8);
private:
	int mAlpha, mLastAlpha;
	bool mVisible, mFadeIn, mHasFaded;
	bool mStartVisible, mStartFadeIn;

	sf::Text mText;
	friend class LevelSaver;
};

#endif