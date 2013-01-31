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

void runCollisions(UnitVector& Objects, Player& player)
{
	Collision col[3];
	for (int i=0; i<player.getCollisionSprite().size() && i<3; i++)
	{
		col[i].collide(i, player, Objects);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split");
	window.setFramerateLimit(60);
	UnitVector Objects;
	Background *BG;
	Level	level("Test.xml");	
	Objects	= level.getObjects();
	Collision::unitAtSides(Objects);
	BG=level.getBackground();
	for(UnitVector::size_type i=0;i<Objects.size();i++)
	{
		cout<<Objects[i]->getId()<<endl;
	}

	Player* mPlayer= new Player(level.getPlayer()->getCollisionSprite()[0]->getPosition());


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed){
				switch(event.key.code)
				{
				case sf::Keyboard::LShift:
					mPlayer->interact(6);
					//mPlayer->setBodyActive(!mPlayer->getBodyActive());
					break;
				case sf::Keyboard::Space:
					mPlayer->interact(5);
					//mPlayer->setTogether(!mPlayer->getTogether());
					break;
				case sf::Keyboard::E:
					mPlayer->interact(7);
					/*if(mPlayer->getTogether()==false && mPlayer->getBodyActive()==false){
						mPlayer->setAttachFeetExtension(!mPlayer->getAttachFeetExtension());
					}*/
					break;
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			mPlayer->reFuel(100);
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
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Event::MouseButtonPressed){
			sf::Vector2f Temp;
			Temp.x=(float)sf::Mouse::getPosition(window).x-16;
			Temp.y=(float)sf::Mouse::getPosition(window).y-16;
			mPlayer->shootHead(sf::Vector2f(Temp));
			//std::cout << "Anropar";
		}
		/*if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			mPlayer->shootHead(sf::Vector2f(0, 0));
		}*/
		window.clear(sf::Color::Black);
		
		window.draw(BG->draw());
		BG->update();
		mPlayer->update();
		runCollisions(Objects, *mPlayer);


		mPlayer->draw(window);
		mPlayer->resetAnimations();

		for(UnitVector::size_type i=0;i<Objects.size();i++)
		{
			window.draw(Objects[i]->getSprite());
		}

		window.display();
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
