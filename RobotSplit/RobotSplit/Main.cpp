#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "PlayerPart.h"
#include "Player.h"
#include "TextureManager.h"
#include "Animation.h"
#include "Unit.h"
#include "Platform.h"

int main(){
	TextureManager mTextures;
	mTextures.loadTexture();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Robot split");
	window.setFramerateLimit(60);
	sf::Texture* Text=new sf::Texture;
	Text->loadFromFile("hej.JPG");
	std::vector <PlayerPart*> Wiie;

	//Platt mPlatt(sf::Vector2f(100, 500));
	//Platt mPlatt2(sf::Vector2f(300, 400));

	Player* mPlayer= new Player;
	bool Collision=true;


	Platform* platform=new Platform(sf::Vector2f(300, 300), "Tile1");

	std::vector<Unit*> objects;
	objects.push_back(platform);

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
						//mPlayer->yesffs(!mPlayer->getYes());
					}
					break;
				}
			}
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
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2f Temp;
			Temp.x=sf::Mouse::getPosition(window).x;
			Temp.y=sf::Mouse::getPosition(window).y;
			mPlayer->shootHead(sf::Vector2f(Temp));
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			mPlayer->shootHead(sf::Vector2f(0, 0));
		}
		if(Collision==true){
			//for(int i=0; i<mPlayer->getVector().size(); i++){
			//	//if(mPlayer->getVector()[i]->getPosition().y<400 && mPlayer->getVector()[i]->getMovable()){
			//		mPlayer->getVector()[i]->setPosition(sf::Vector2f(0, 3));
			//	//}
			//	if(mPlayer->getVector()[i]->getPosition().x<0){
			//		mPlayer->getVector()[i]->setPosition(sf::Vector2f(0-mPlayer->getVector()[i]->getPosition().x, 0));
			//	}
			//	if(mPlayer->getVector()[i]->getPosition().x+mPlayer->getVector()[i]->getSprite().getTexture()->getSize().x>800){
			//		mPlayer->getVector()[i]->setPosition(sf::Vector2f(800-(mPlayer->getVector()[i]->getPosition().x+mPlayer->getVector()[i]->getSprite().getTexture()->getSize().x), 0));
			//	}
			//	if(mPlayer->getVector()[i]->getPosition().y+mPlayer->getVector()[i]->getSprite().getTexture()->getSize().y>600){
			//		mPlayer->getVector()[i]->setPosition(sf::Vector2f(0, 600-(mPlayer->getVector()[i]->getPosition().y+mPlayer->getVector()[i]->getSprite().getTexture()->getSize().y)));
			//	}
			//	if(mPlayer->getVector()[i]->getPosition().y<0){
			//		mPlayer->getVector()[i]->setPosition(sf::Vector2f(0, 0-(mPlayer->getVector()[i]->getPosition().y)));
			//		mPlayer->resetJump();
			//	}
			//}
		}

		/*if((mPlatt.getSprite().getGlobalBounds().intersects(mPlayer->getVector()[0]->getSprite().getGlobalBounds()))){
			std::cout << "Touch me" << std::endl;
		}*/
		//mPlatt.getSprite().getGlobalBounds().intersects(

		window.clear(sf::Color::Black);
		//window.draw(mPlatt.getSprite());
		//window.draw(mPlatt2.getSprite());
		mPlayer->update();
		mPlayer->draw(window);
		mPlayer->resetAnimations();

		window.draw(platform->getSprite());

		window.display();
	}

	return 0;
}
