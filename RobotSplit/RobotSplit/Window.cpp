#include "Window.h"

sf::RenderWindow Window::mWindow;

Window::Window()
{
	loadWindow();
}

Window::~Window()
{}

void Window::loadWindow()
{
	mWindow.create(sf::VideoMode(1280, 768), "Robot split");
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	return mWindow;
}