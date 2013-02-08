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
	mWindow.create(sf::VideoMode(1280, 768), "Robot split", sf::Style::Fullscreen);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	sf::FloatRect temp(mWindow.getPosition().x, mWindow.getPosition().y, mWindow.getSize().x, mWindow.getSize().y);
	sf::View tempView(temp);
	mWindow.setView(tempView);
	return mWindow;

}