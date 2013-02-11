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
	mWindow.create(sf::VideoMode(1280, 758), "Robot split", sf::Style::Close);
	mWindow.setVerticalSyncEnabled(true);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	//sf::Vector2f Center(1280/2, 768/2);
	//sf::Vector2f Size(1280, 768);
	//sf::View Test(Center, Size);
	//mWindow.setView(Test);
	//sf::FloatRect temp(mWindow.getPosition().x, mWindow.getPosition().y, mWindow.getSize().x, mWindow.getSize().y);
	//sf::View tempView(temp);
	//mWindow.setView(tempView);
	return mWindow;

}