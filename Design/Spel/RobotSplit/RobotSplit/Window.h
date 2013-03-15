#ifndef INC_WINDOW
#define INC_WINDOW

#include <SFML/Graphics.hpp>
//#include <vector>

//typedef	std::vector<sf::Event>	EventVector;

class Window
{
public:
	static sf::RenderWindow& getWindow();
	static Window& getInstance();
	static sf::Event& getEvent();

	//static	void newEvents();
	//static	EventVector	getEvents();
private:
	Window();
	Window(const Window& window);
	Window operator=(const Window& window);
	~Window();

	void load();

	static sf::Event mEvent;
	static sf::RenderWindow mWindow;
};

#endif