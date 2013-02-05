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

//#include "Window.h"

Game::Game(sf::RenderWindow& window): 
		mStateInput(StateInput::getInstance()),
		mlevel("Test.xml"),
		mPlayer(new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition())),
		BG(mlevel.getBackground()),
		lastUpdate(0),
		loops(0),
		mWindow(window)
{
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	Collision::unitAtSides(Objects->getUnits());
	/*for(UnitVector::size_type i=0;i<Objects->getUnits().size();i++)
	{
		cout << Objects->getUnits()[i]->getId() << endl;
	}*/
}

Game::~Game()
{
	std::cout << "Game DELETE" << std::endl;

	/*system("PAUSE");
	XmlSaver saver("TestSave");
	saver.saveLevel(mlevel);
	saver.createFile();
	mlevel.deletePointers();*/
}

void Game::update()
{
	sf::Clock TestTimer;
		loops = 0;
		while (lastUpdateClock.getElapsedTime().asSeconds()>lastUpdate && loops<2)
		{
			loops++;
			lastUpdate+=1/60.0;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				mPlayer->interact(3);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				mPlayer->interact(1);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				mPlayer->interact(2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				mPlayer->interact(0);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
				mPlayer->interact(4);
			}

			if(TestTimer.getElapsedTime().asSeconds()>0.3){
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
					mPlayer->reFuel(100);
					TestTimer.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
					mPlayer->interact(6);
					TestTimer.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
					mPlayer->interact(5);
					TestTimer.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
					mPlayer->interact(7);
					TestTimer.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
					mPlayer->restartPlayer(sf::Vector2f(100, 100));
					TestTimer.restart();
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonPressed){
					sf::Vector2f Temp;
					Temp.x=(float)sf::Mouse::getPosition(mWindow).x;
					Temp.y=(float)sf::Mouse::getPosition(mWindow).y;
					mPlayer->shootHead(sf::Vector2f(Temp));
					TestTimer.restart();
				}
		//	BG->update();
			mPlayer->update();
			Objects->update();

			//runCollisions(Objects.getUnits(), *mPlayer);
		}
	}
}

void Game::render()
{
	
	//std::cout << "Game" << std::endl;
	mWindow.clear(sf::Color::Black);
	//Window::getWindow().draw(BG->draw());

	Objects->draw(mWindow);
	mPlayer->draw(mWindow);
	mPlayer->resetAnimations();

	mWindow.display();
}




	//Test for finding Textures' names
	/*for(UnitVector::size_type i=0;i<Objects.size();i++)
	{
		cout<<TextureManager::getSpriteName(Objects[i]->getSprite())<<endl;
	}*/
