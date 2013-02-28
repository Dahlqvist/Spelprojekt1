#include "Timer.h"
#include "Window.h"

sf::Clock Timer::mClock;
sf::Clock Timer::mSecondClock;
int Timer::mDec;
int Timer::mSek;
int Timer::mMin;
int Timer::mHour;

int Timer::m1Sek;
int Timer::m10Sek;
int Timer::m1Min;
int Timer::m10Min;
int Timer::m1Hour;
int Timer::m10Hour;

Animation* Timer::mNumbers;

Timer::Timer()
{
	load();

	initialize();
	restartClock();

	mNumbers->setPosition(sf::Vector2f(Window::getWindow().getSize()));
	mNumbers->setAnimate(false);
}

void Timer::load()
{
	mNumbers = new Animation("Numbers", 1, 20);
}

void Timer::initialize()
{
	mDec = 0;
	mSek = 0;
	mMin = 0;
	mHour = 0;

	m1Sek = 0;
	m10Sek = 0;
	m1Min = 0;
	m10Min = 0;
	m1Hour = 0;
	m10Hour = 0;
}

Timer::~Timer()
{
	delete mNumbers;
}

//Timer& Timer::getInstance()
//{
//	Timer temp;
//	return temp;
//}

sf::Clock& Timer::getClock()
{
	return mClock;
}

void Timer::restartClock()
{
	mSecondClock.restart();
	mClock.restart();
}

void Timer::input()
{
	if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::G)
	{
		initialize();
		restartClock();
	}
}

void Timer::update()
{
	//sf::Vector2f timerPos = sf::Vector2f(Window::getWindow().getSize().x - 400, Window::getWindow().getSize().y );
	sf::Vector2f timerPos = sf::Vector2f(1200, 10);
	//För att få fram vilken bild som skall visas

	mDec = (mClock.getElapsedTime().asMilliseconds() / 100) % 10;
	mSek = mClock.getElapsedTime().asSeconds();
	mMin = mClock.getElapsedTime().asSeconds() / 60;
	mHour = mClock.getElapsedTime().asSeconds() / 3600;

	m1Sek = mSek % 10;
	m10Sek = (mSek / 10) % 6;
	m1Min = mMin % 10;
	m10Min = (mMin / 10) % 6;
	m1Hour = mHour % 10;
	m10Hour = (mHour / 10) % 10;

	//Window::getWindow().clear(sf::Color::Black);

	//tiondels sekunder
	mNumbers->setCurrentFrame(mDec);
	mNumbers->setPosition(timerPos);
	mNumbers->update();
	Window::getWindow().draw(mNumbers->getSprite());

	//ental sekunder
	timerPos.x = timerPos.x - (10 + mNumbers->getSprite().getGlobalBounds().width);
	mNumbers->setCurrentFrame(m1Sek);
	mNumbers->setPosition(timerPos);
	mNumbers->update();
	Window::getWindow().draw(mNumbers->getSprite());
	
	//tiotal sekunder
	timerPos.x = timerPos.x - (10 + mNumbers->getSprite().getGlobalBounds().width);
	mNumbers->setCurrentFrame(m10Sek);
	mNumbers->setPosition(timerPos);
	mNumbers->update();
	Window::getWindow().draw(mNumbers->getSprite());

	//ental minuter
	if(mSek > 60)
	{
		timerPos.x = timerPos.x - (10 + mNumbers->getSprite().getGlobalBounds().width);
		mNumbers->setCurrentFrame(m1Min);
		mNumbers->setPosition(timerPos);
		mNumbers->update();
		Window::getWindow().draw(mNumbers->getSprite());
	}

	//tiotal minuter
	timerPos.x = timerPos.x - (10 + mNumbers->getSprite().getGlobalBounds().width);
	mNumbers->setCurrentFrame(m10Min);
	mNumbers->setPosition(timerPos);
	mNumbers->update();
	Window::getWindow().draw(mNumbers->getSprite());
}

void Timer::render()
{
	Window::getWindow().display();
}