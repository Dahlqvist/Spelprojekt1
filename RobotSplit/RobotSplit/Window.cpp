#include "Window.h"
#include <iostream>

sf::RenderWindow Window::mWindow;
sf::Event Window::mEvent;

Window::Window()
{
	load();
}

Window::~Window()
{}

Window& Window::getInstance()
{
	Window window;
	return window;
}

void Window::load()
{
	mWindow.create(sf::VideoMode(1280, 768), "Robot split", sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	return mWindow;
}

sf::Event& Window::getEvent()
{
	return mEvent;
}