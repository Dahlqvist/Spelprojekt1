#include "Controls.h"
#include "StateInput.h"
#include "Window.h"

Controls::Controls():
	mWindow(Window::getWindow()),
	mStateInput(StateInput::getInstance()),
	mBackground("Main", 1, 1),
	mInGameBackground("Ingame", 1, 1),
	mBlip("Blip", 1, 1),
	mBack("Back", 1, 2),
	mControlSchedule("ControlSchedule", 1, 1),
	currentSelection(&mBack),
	currentBackground(&mBackground)
{
	mBack.setAnimate(false);

	sf::Vector2f tempPos(mWindow.getSize().x/2-mBackground.getSprite().getGlobalBounds().width/2, 0);
	sf::Vector2f tempPos2(mWindow.getSize().x/2-mInGameBackground.getSprite().getGlobalBounds().width/2, 0);
	mBackground.setPosition(tempPos);
	mInGameBackground.setPosition(tempPos2);

	mControlSchedule.setPosition(sf::Vector2f(tempPos.x + 230, tempPos.y + 150 ));
	mBack.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 550));
	mBlip.setPosition(sf::Vector2f(tempPos.x + 240, tempPos.y +550));
	mBack.setCurrentFrame(1);

}

Controls::~Controls()
{}

void Controls::update()
{
	if(StateInput::getMenuStatus())
		currentBackground = &mBackground;
	else if(!StateInput::getMenuStatus())
		currentBackground = &mInGameBackground;
	if(mStatus == 0)
		currentSelection = &mBack;
	currentSelection ->update();
}

void Controls::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(currentBackground->getSprite());
	mWindow.draw(mControlSchedule.getSprite());
	mWindow.draw(mBack.getSprite());
	mWindow.draw(mBlip.getSprite());

	mWindow.display();
}

void Controls::input()
{
	if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Return)
				mStateInput.changeState("Last");
}