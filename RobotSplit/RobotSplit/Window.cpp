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
	mWindow.create(sf::VideoMode::getDesktopMode(), "Robot split", sf::Style::Fullscreen);
	mWindow.setVerticalSyncEnabled(true);
	//sf::View Test;
	//Test.setCenter(1280/2, 768/2);
	//Test.setCenter(1280/2, 768/2);
	//Test.setSize(1280, 768);
	//Test.move(100, 100);
	//Test.zoom(1280/sf::VideoMode::getDesktopMode().width);
	//sf::VideoMode Mode;
	//Mode.getDesktopMode
	//mWindow.setView(Test);
	sf::Vector2f Center(1280/2, 768/2);
	sf::Vector2f Size(1280, 768);
	sf::View Test(Center, Size);
	mWindow.setView(Test);
	mWindow.clear(sf::Color::Black);
	mWindow.display();
}

sf::RenderWindow& Window::getWindow()
{
	sf::Vector2f Center(1280/2, 768/2);
	sf::Vector2f Size(1280, 768);
	sf::View Test(Center, Size);
	mWindow.setView(Test);
	//sf::FloatRect temp(mWindow.getPosition().x, mWindow.getPosition().y, mWindow.getSize().x, mWindow.getSize().y);
	//sf::View tempView(temp);
	//mWindow.setView(tempView);
	return mWindow;

}