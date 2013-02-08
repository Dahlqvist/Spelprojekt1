#ifndef INC_WINDOW
#define INC_WINDOW

#include <SFML/Graphics.hpp>

class Window
{
public:
	static sf::RenderWindow& getWindow();
	static Window& getInstance();

private:
	Window();
	Window(const Window& window);
	Window operator=(const Window& window);
	~Window();

	void loadWindow();
	static sf::RenderWindow mWindow;
};

#endif