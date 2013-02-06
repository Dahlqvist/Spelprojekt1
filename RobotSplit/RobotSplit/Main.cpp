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

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split");
	//window.setFramerateLimit(60);
	std::vector<Background*> BG;
	Level	level("Test.xml");	
	Player* mPlayer= new Player(level.getPlayer()->getCollisionSprite()[0]->getPosition());
	UnitManager Objects(mPlayer, level.getObjects());
	Collision::unitAtSides(Objects.getUnits());
	BG=level.getBackground();
	for(UnitVector::size_type i=0;i<Objects.getUnits().size();i++)
	{
		cout<<Objects.getUnits()[i]->getId()<<endl;
	}
	window.setKeyRepeatEnabled(false);
	sf::Clock TestTimer;
	TestTimer.restart();
	sf::Clock lastUpdateClock;
	double lastUpdate=0;
	int loops;
	bool renderGame;
	while (window.isOpen())
	{
		renderGame=false;
		loops=0;
		while (lastUpdateClock.getElapsedTime().asSeconds()>lastUpdate && loops<10)
		{
			renderGame=true;
			loops++;
			lastUpdate+=1/60.0;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				//if(event.type == sf::Event::KeyPressed){
				//	switch(event.key.code)
				//	{
				//	case sf::Keyboard::LShift:
				//		mPlayer->interact(6);
				//		//mPlayer->setBodyActive(!mPlayer->getBodyActive());
				//		break;
				//	case sf::Keyboard::Space:
				//		mPlayer->interact(5);
				//		//mPlayer->setTogether(!mPlayer->getTogether());
				//		break;
				//	case sf::Keyboard::E:
				//		mPlayer->interact(7);
				//		/*if(mPlayer->getTogether()==false && mPlayer->getBodyActive()==false){
				//			mPlayer->setAttachFeetExtension(!mPlayer->getAttachFeetExtension());
				//		}*/
				//		break;
				//	}
				//}
			}

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

			if(TestTimer.getElapsedTime().asSeconds()>0.2){
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
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
					mPlayer->interact(8);
					TestTimer.restart();
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
					mPlayer->restartPlayer(sf::Vector2f(100, 100));
					TestTimer.restart();
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonPressed){
					sf::Vector2f Temp;
					Temp.x=(float)sf::Mouse::getPosition(window).x;
					Temp.y=(float)sf::Mouse::getPosition(window).y;
					mPlayer->shootHead(sf::Vector2f(Temp));
					TestTimer.restart();
					//std::cout << "Anropar";
				}
			}
			//window.setKeyRepeatEnabled(true);

			window.clear(sf::Color::Black);
			
			mPlayer->update();
			Objects.update();

			//runCollisions(Objects.getUnits(), *mPlayer);
		}

		if(renderGame)
		{
			for (vector<Background*>::size_type i=0; i<BG.size(); i++)
			{
				window.draw(BG[i]->draw());
				BG[i]->update();
			}
			Objects.draw(window);
			mPlayer->draw(window);
			mPlayer->resetAnimations();

			window.display();
		}
	}
	/*
	//Test for finding Textures' names
	for(UnitVector::size_type i=0;i<Objects.size();i++)
	{
		cout<<TextureManager::getSpriteName(Objects[i]->getSprite())<<endl;
	}
	system("PAUSE");
	*/
	XmlSaver saver("TestSave");
	delete mPlayer;
	saver.saveLevel(level);
	saver.createFile();
	level.deletePointers();
	return 0;
}
