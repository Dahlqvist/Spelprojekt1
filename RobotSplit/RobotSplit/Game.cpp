#include "Game.h"
#include "StateInput.h"

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "PlayerPart.h"
#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include "Unit.h"
#include "Platform.h"
#include "LevelLoader.h"
#include "Collision.h"
#include "XmlSaver.h"
#include "Background.h"
#include <SFML\System\Clock.hpp>
#include "UnitManager.h"


#include "Window.h"

Game::Game():
		mStateInput(StateInput::getInstance()),
		mlevel("Test.xml"),
		mPlayer(new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition())),
		BG(mlevel.getBackground()),
		lastUpdate(0),
		loops(0),
		mWindow(Window::getWindow()),
		mTime(0.2)
{
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	Collision::unitAtSides(Objects->getUnits());
	lastUpdateClock.restart();
	mWindow.setKeyRepeatEnabled(false);
	diaBox = mlevel.getDialogueBoxes();
}

Game::~Game()
{
	while (!diaBox.empty())
	{
		delete diaBox.back();
		diaBox.pop_back();
	}
	delete Objects;
	/*system("PAUSE");
	XmlSaver saver("TestSave");
	saver.saveLevel(mlevel);
	saver.createFile();*/
	mlevel.deletePointers();
}

void Game::update()
{
	loops = 0;
	while (lastUpdateClock.getElapsedTime().asSeconds()>lastUpdate && loops<10)
	{
		loops++;
		lastUpdate+=1/60.0;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			mPlayer->interact(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			mPlayer->interact(1);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			mPlayer->interact(2);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			mPlayer->interact(3);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
			mPlayer->interact(4);
		}
		if(TestTimer.getElapsedTime().asSeconds()>mTime){
			mTime=(float)0.2;
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				mPlayer->interact(5);
				TestTimer.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
				mPlayer->interact(6);
				TestTimer.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				mPlayer->interact(7);
				TestTimer.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
				mPlayer->interact(8);
				TestTimer.restart();
				mTime=(float)0.7;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonPressed){
				sf::Vector2f Temp;
				Temp.x=(float)sf::Mouse::getPosition(mWindow).x;
				Temp.y=(float)sf::Mouse::getPosition(mWindow).y;
				mPlayer->shootHead(sf::Vector2f(Temp));
				TestTimer.restart();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
				mPlayer->restartPlayer(sf::Vector2f(100, 100));
				TestTimer.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				mPlayer->reFuel(100);
				TestTimer.restart();
			}
		//window.setKeyRepeatEnabled(true);
		}
		mPlayer->update();
		Objects->update();
		for (vector<DialogueBox*>::size_type i=0; i<diaBox.size(); i++)
		{
			diaBox[i]->update();
		}

		//runCollisions(Objects.getUnits(), *mPlayer);
	}
}

void Game::render()
{
	mWindow.clear(sf::Color::Black);
	for(vector<Background*>::size_type i =0; i < BG.size(); i++)
	{
		mWindow.draw(BG[i]->draw());
		BG[i]->update();
	}

	Objects->draw(mWindow);
	mPlayer->draw(mWindow);
	mPlayer->resetAnimations();
	for (vector<DialogueBox*>::size_type i=0; i<diaBox.size(); i++)
	{
		mWindow.draw(diaBox[i]->getSprite());
		mWindow.draw(diaBox[i]->getText());
	}
	//mWindow.draw(diaBox->getText());

	mWindow.display();
}
