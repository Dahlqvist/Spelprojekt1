#include "Window.h"
#include <iostream>

sf::RenderWindow Window::mWindow;
sf::Event Window::mEvent;
//EventVector	Window::mEvents;

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
	mWindow.create(sf::VideoMode(1280, 768), "Robot split", /*sf::Style::Close*/sf::Style::Fullscreen);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	return mWindow;
}

//void	Window::newEvents()
//{
//	mEvents.clear();
//	sf::Event	tempEvent;
//	while(mWindow.pollEvent(tempEvent))
//	{
//		mEvents.push_back(tempEvent);
//		if(tempEvent.type==sf::Event::EventType::KeyReleased)
//		{
//			std::cout<<"finds key";
//		}
//	}
//}

//std::vector<sf::Event>	Window::getEvents()
//{
//	return	mEvents;
//}


sf::Event& Window::getEvent()
{
	return mEvent;
}