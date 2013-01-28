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

void runCollisions(Level level, Player& player)
{
	std::vector<Collision> col;
	for (int i=0; i<player.getCollisionSprite().size(); i++)
	{
		/*int part=i;
		if (player.getTogether())
		{
			part=-1;
		}*/
		col.push_back(Collision());
		col[i].collide(i, player, level.getObjects());
	}
}

int main(){
	TextureManager mTextures;
	mTextures.loadTexture();

	sf::RenderWindow window(sf::VideoMode(1280, 768), "Robot split");
	window.setFramerateLimit(60);

	Level	level("Test.xml");
	for(UnitVector::size_type i=0;i<level.getObjects().size();i++)
	{
		cout<<level.getObjects()[i]->getId();
	}

	Player* mPlayer= level.getPlayer();


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
			mPlayer->sprint();
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
			Temp.x=sf::Mouse::getPosition(window).x;
			Temp.y=sf::Mouse::getPosition(window).y;
			mPlayer->shootHead(sf::Vector2f(Temp));
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			mPlayer->shootHead(sf::Vector2f(0, 0));
		}

		mPlayer->update();

		runCollisions(level, *mPlayer);

		window.clear(sf::Color::Black);
		
		mPlayer->draw(window);
		mPlayer->resetAnimations();

		for(UnitVector::size_type i=0;i<level.getObjects().size();i++)
		{
			window.draw(level.getObjects()[i]->getSprite());
		}

		window.display();
	}
	level.deletePointers();
	return 0;
}
