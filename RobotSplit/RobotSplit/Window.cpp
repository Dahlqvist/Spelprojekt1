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
}

sf::RenderWindow& Window::getWindow()
{
	return mWindow;
}