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

void runCollisions(UnitVector Objects, Player& player)
{
	std::vector<Collision> col;
	for (int i=0; i<player.getCollisionSprite().size(); i++)
	{
		col.push_back(Collision());
		col[i].collide(i, player, Objects);
	}
}

int main(){

	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split");
	window.setFramerateLimit(60);
	UnitVector Objects;
	Level	level("Test.xml");	
	Objects	= level.getObjects();
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
					if(mPlayer->getTogether()==false){
						mPlayer->setBodyActive(!mPlayer->getBodyActive());
					}
					break;
				case sf::Keyboard::Space:
					mPlayer->setTogether(!mPlayer->getTogether());
					break;
				case sf::Keyboard::E:
					if(mPlayer->getTogether()==false && mPlayer->getBodyActive()==false){
						mPlayer->setAttachFeet(!mPlayer->getAttachFeet());
					}
					break;
				}
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			mPlayer->reFuel(100);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			mPlayer->dash();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			mPlayer->move(sf::Vector2f(1,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			mPlayer->move(sf::Vector2f(-1,0));
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			mPlayer->jump();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && mPlayer->getTogether()==false && mPlayer->getBodyActive()==false){
			mPlayer->activateFeetRockets();
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2f Temp;
			Temp.x=(float)sf::Mouse::getPosition(window).x;
			Temp.y=(float)sf::Mouse::getPosition(window).y;
			mPlayer->shootHead(sf::Vector2f(Temp));
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			mPlayer->shootHead(sf::Vector2f(0, 0));
		}
		window.clear(sf::Color::Black);
		
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
