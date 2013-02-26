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
		mlevel("Tutorial1.xml"),
		mPlayer(new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition())),
		BG(mlevel.getBackground()),
		loops(0),
		mWindow(Window::getWindow()),
		mTime(0.2)
{
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	Collision::unitAtSides(Objects->getUnits());
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setMouseCursorVisible(false);
	//diaBox = mlevel.getDialogueBoxes();
	mSecurityLevel=0;
	Music::loadMusic("Music/menu_1.wav");
	mBana=0;
	//if(mlevel.getName()=="Tutorial1"){
	//	mSecurityLevel=0;
	//}
	//else if(mlevel.getName()=="Tutorial2"){
	//	mSecurityLevel=1;
	//}
	//else{
	//	mSecurityLevel=2;
	//}
	mBanor.push_back("Tutorial1.xml");
	mBanor.push_back("Tutorial2.xml");
	mBanor.push_back("Tutorial3.xml");
	mBanor.push_back("Tutorial4.xml");
	mBanor.push_back("Tutorial5.xml");
	mBanor.push_back("Tutorial6.xml");
	mBanor.push_back("Bana1.xml");
	mBanor.push_back("Bana2.xml");
	mBanor.push_back("Bana3.xml");
}

Game::~Game()
{
	delete Objects;
	/*system("PAUSE");
	XmlSaver saver("TestSave");
	saver.saveLevel(mlevel);
	saver.createFile();*/
	mlevel.deletePointers();
}

void Game::changeMap(int map)
{
	if(mBana+map<mBanor.size() && mBana+map>=0)
	{
		mBana+=map;
	}
	else
	{
		mStateInput.changeState("QuitToMenu");
		mBana=0;
	}
	//std::cout << mBanor[mBana] << std::endl;
	mlevel.loadNewLevel(mBanor[mBana]);
	for(int i=0;i<BG.size();i++)
	{
		delete BG[i];
	}
	BG=mlevel.getBackground();
	delete Objects;
	delete mPlayer;
	mPlayer = new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition());
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	//mPlayer->restartPlayer();
	Music::playMusic();
	if(mlevel.getName()=="Tutorial1")
	{
		mSecurityLevel=0;
	}
	else if(mlevel.getName()=="Tutorial2")
	{
		mSecurityLevel=1;
	}
	else
	{
		mSecurityLevel=2;
	}
}

void Game::update()
{
	if(mPlayer->getWinning()==true)
	{
		Music::pauseMusic();
		if(Sound::getSoundStatus("Winning") == 0){
			Game::changeMap(1);
		}
		mPlayer->update();
		Objects->update();
		Objects->collide();
	}
	else{
		Game::input();
		//window.setKeyRepeatEnabled(true);
		mPlayer->update();
		Objects->update();
		Objects->collide();

		moveCamera();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mSecurityLevel>=1){
		mPlayer->interact(4);
	}
	if(TestTimer.getElapsedTime().asSeconds()>mTime){
		mTime=(float)0.2;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && mSecurityLevel>=1){
			mPlayer->interact(5);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && mSecurityLevel>=1){
			mPlayer->interact(6);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mSecurityLevel>=2){
			mPlayer->interact(7);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mSecurityLevel>=0){
			mPlayer->interact(8);
			TestTimer.restart();
			mTime=(float)0.7;
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mSecurityLevel>=2){
			sf::Vector2f Temp;
			Temp.x=(float)sf::Mouse::getPosition(mWindow).x+(mWindow.getView().getCenter().x-mWindow.getSize().x/2.0);
			Temp.y=(float)sf::Mouse::getPosition(mWindow).y+(mWindow.getView().getCenter().y-mWindow.getSize().y/2.0);
			mPlayer->shootHead(sf::Vector2f(Temp));
			TestTimer.restart();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)){
			mPlayer->restartPlayer();
			TestTimer.restart();
			Objects->reset();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			mPlayer->reFuel();
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F7)){
			Game::changeMap(-1);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F8)){
			Game::changeMap(1);
			TestTimer.restart();
		}

		//runCollisions(Objects.getUnits(), *mPlayer);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mStateInput.changeMenu();
		mStateInput.changeState("InGameMenu");
	}
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
	mWindow.clear(sf::Color::Black);
	for(vector<Background*>::size_type i =0; i < BG.size(); i++)
	{
		mWindow.draw(BG[i]->draw());
		BG[i]->update();
	}
	mPlayer->draw(mWindow);
	Objects->draw(mWindow);
	mPlayer->resetAnimations();
	//for (vector<DialogueBox*>::size_type i=0; i<diaBox.size(); i++)
	//{
		//mWindow.draw(diaBox[i]->getSprite());
		//mWindow.draw(diaBox[i]->getText());
	//}
	//mWindow.draw(diaBox->getText());
	if(mPlayer->getWinning()==false){
		Music::playMusic();
	}
	mWindow.display();
}
