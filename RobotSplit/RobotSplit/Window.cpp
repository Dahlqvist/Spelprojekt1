#include "Window.h"

sf::RenderWindow Window::mWindow;

Window::Window()
{
	loadWindow();
}

Window::~Window()
{}

Window& Window::getInstance()
{
	Window window;
	return window;
}

void Window::loadWindow()
{
	mWindow.create(sf::VideoMode(1280, 758), "Robot split", sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	return mWindow;
}