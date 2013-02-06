#ifndef INC_WINDOW
#define INC_WINDOW

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();
	static sf::RenderWindow& getWindow();

private:
	void loadWindow();
	static sf::RenderWindow mWindow;
};

#endif