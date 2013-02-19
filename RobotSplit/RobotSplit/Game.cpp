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
#include "Trigger.h"

#include "Window.h"
#include "Sound.h"
#include "Music.h"

Game::Game():
		mStateInput(StateInput::getInstance()),
		mlevel("Bana2.xml"),
		mPlayer(new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition())),
		BG(mlevel.getBackground()),
		nextUpdate(0),
		loops(0),
		mWindow(Window::getWindow()),
		mTime(0.2)
{
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	Collision::unitAtSides(Objects->getUnits());
	lastUpdateClock.restart();
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setMouseCursorVisible(false);
	diaBox = mlevel.getDialogueBoxes();
	mSecurityLevel=0;
	Music::loadMusic("Music/menu_1.wav");
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
	mRenderGame=false;
	while (lastUpdateClock.getElapsedTime().asSeconds()>nextUpdate && loops<5)
	{
		mRenderGame=true;
		loops++;
		nextUpdate+=1/60.0;
		Game::input();
		//window.setKeyRepeatEnabled(true);
		mPlayer->update();
		Objects->update();

		moveCamera();

		//runCollisions(Objects.getUnits(), *mPlayer);
	}
}
void Game::input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSecurityLevel>=0){
		mPlayer->interact(0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSecurityLevel>=0){
		mPlayer->interact(1);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSecurityLevel>=0){
		mPlayer->interact(2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSecurityLevel>=0){
		mPlayer->interact(3);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mSecurityLevel>=0){
		mPlayer->interact(4);
	}
	if(TestTimer.getElapsedTime().asSeconds()>mTime){
		mTime=(float)0.2;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && mSecurityLevel>=0){
			mPlayer->interact(5);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && mSecurityLevel>=0){
			mPlayer->interact(6);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mSecurityLevel>=0){
			mPlayer->interact(7);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mSecurityLevel>=0){
			mPlayer->interact(8);
			TestTimer.restart();
			mTime=(float)0.7;
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mSecurityLevel>=0){
			sf::Vector2f Temp;
			Temp.x=(float)sf::Mouse::getPosition(mWindow).x+(mWindow.getView().getCenter().x-mWindow.getSize().x/2.0);
			Temp.y=(float)sf::Mouse::getPosition(mWindow).y+(mWindow.getView().getCenter().y-mWindow.getSize().y/2.0);
			mPlayer->shootHead(sf::Vector2f(Temp));
			TestTimer.restart();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
			mPlayer->restartPlayer(sf::Vector2f(64, 384));
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			mPlayer->reFuel(100);
			TestTimer.restart();
		}

		//runCollisions(Objects.getUnits(), *mPlayer);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mStateInput.changeState("InGameMenu");
}

void Game::moveCamera()
{
	//sf::View view(sf::FloatRect(mWindow.getPosition().x/2, mWindow.getPosition().y/2, mWindow.getSize().x/2, mWindow.getSize().y/2));
	//view.setViewport(sf::FloatRect(0, 0, 1, 1));
	sf::View view(mWindow.getView());
	sf::FloatRect partRect;
	
	if (mPlayer->getTogether() || !mPlayer->getBodyActive())
	{
		partRect=mPlayer->getCollisionSprite()[0]->getGlobalBounds();
	}
	else
	{
		partRect=mPlayer->getCollisionSprite()[1]->getGlobalBounds();
	}
	float posX=partRect.left+(partRect.width/2.0f);
	float posY=partRect.top+(partRect.height/2.0f);
	float levelWidth=mlevel.getSize().x;
	float levelHeight=mlevel.getSize().y;

	if (posX<view.getSize().x/2.0)
	{
		posX=view.getSize().x/2.0;
	}
	else if (posX>levelWidth-view.getSize().x/2.0)
	{
		posX=levelWidth-view.getSize().x/2.0;
	}

	if (posY<view.getSize().y/2.0)
	{
		posY=view.getSize().y/2.0;
	}
	else if (posY>levelHeight-view.getSize().y/2.0)
	{
		posY=levelHeight-view.getSize().y/2.0;
	}

	view.setCenter(posX, posY);
	mWindow.setView(view);
}

void Game::render()
{
	if (mRenderGame)
	{
		mWindow.clear(sf::Color::Black);
		for(vector<Background*>::size_type i =0; i < BG.size(); i++)
		{
			mWindow.draw(BG[i]->draw());
			BG[i]->update();
		}
		mPlayer->draw(mWindow);
		Objects->draw(mWindow);
		mPlayer->resetAnimations();
		for (vector<DialogueBox*>::size_type i=0; i<diaBox.size(); i++)
		{
			mWindow.draw(diaBox[i]->getSprite());
			mWindow.draw(diaBox[i]->getText());
		}
		//mWindow.draw(diaBox->getText());
		Music::playMusic();
		mWindow.display();

		lastUpdateClock.restart();
		nextUpdate=0;
	}
}
