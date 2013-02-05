#ifndef INC_WINDOW
#define INC_WINDOW

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();

	static const sf::RenderWindow getWindow();
private:
	static void loadWindow();
	static sf::RenderWindow mWindow;
};

#endif