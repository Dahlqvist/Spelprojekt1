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
#include "TriggedAnimation.h"

#include "Window.h"
#include "Sound.h"
#include "Music.h"
#include "Timer.h"

Game::Game():
		mStateInput(StateInput::getInstance()),
		mPlayer(mlevel.getPlayer()/* new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition())*/),
		BG(mlevel.getBackground()),
		loops(0),
		mWindow(Window::getWindow()),
		mTimer(new Timer),
		mTime((float)0.2)
{
	Objects= new UnitManager(mPlayer, mlevel.getObjects());
	Collision::unitAtSides(Objects->getUnits());
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setMouseCursorVisible(false);
	//diaBox = mlevel.getDialogueBoxes();
	mSecurityLevel=0;
	//Music::loadMusic("Music/tutorial_2.wav");
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
	
	/*mBanor.push_back("Xml/Tutorial1.xml");

	mBanor.push_back("Xml/boss1_eric.xml");*/

	//Rickys filmer
	//mBanor.push_back("Xml/ricky1_movement_split_shift.xml");
	//mBanor.push_back("Xml/ricky2_laserz.xml");
	//mBanor.push_back("Xml/ricky3_fuel_rocketshoes_extension.xml");
	//mBanor.push_back("Xml/ricky4_magneticshoes_longjump.xml");
	
	//Lägger testbanorna från editorn här tillfälligt för att slippa växla mellan banorna
	//mBanor.push_back("Xml/gm_testa7.xml");
	//mBanor.push_back("Xml/gm_testa4.xml");
	//mBanor.push_back("Xml/gm_testa5.xml");
	
	//Vanlig ordning igen..
/*	mBanor.push_back("Xml/Tutorial2.xml");
	mBanor.push_back("Xml/TutorialNy.xml");
	mBanor.push_back("Xml/TutorialNy2.xml");
	mBanor.push_back("Xml/Tutorial3.xml");
	mBanor.push_back("Xml/TutorialNy3.xml");
	mBanor.push_back("Xml/Tutorial5.xml");
	mBanor.push_back("Xml/Tutorial6.xml");
	mBanor.push_back("Xml/Tutorial7.xml");

	//Storybanornas ursprungsordning är kvar men i bortkommenterad form nedanför
	//mBanor.push_back("Xml/RasmusIntro.xml"); Borttagen iom speltest
	mBanor.push_back("Xml/Bana1.xml"); //da original
	mBanor.push_back("Xml/gmBana2.xml"); //enkel sätta-sig-på-sidan-och-förlänga_ändra
	mBanor.push_back("Xml/gmBana3.xml"); //enkel nr2
	mBanor.push_back("Xml/Bana3Ny.xml"); //leap of faith 
	mBanor.push_back("Xml/Bana5.xml"); //randomTiles
	mBanor.push_back("Xml/Bana4.xml"); //stress
	mBanor.push_back("Xml/gmBana8.xml"); //ny.. kan inte beskriva den_ändra
	mBanor.push_back("Xml/gmBana8_ny3.xml");
	mBanor.push_back("Xml/Bana2.xml"); //gamla laserbanan
	mBanor.push_back("Xml/gmBana10_2.xml");//_ändra
	mBanor.push_back("Xml/Bana6Ny.xml"); //weakTiles and laserzz*/

	mBanor.push_back("Xml/ricky1_movement_split_shift.xml");
	mBanor.push_back("Xml/ricky2_laserz.xml");
	mBanor.push_back("Xml/ricky3_fuel_rocketshoes_extension.xml");
	mBanor.push_back("Xml/ricky4_magneticshoes_longjump.xml");

	/*
	mBanor.push_back("Xml/RasmusIntro.xml");
	mBanor.push_back("Xml/Bana1.xml");
	mBanor.push_back("Xml/Bana2.xml");
	mBanor.push_back("Xml/Bana3Ny.xml");
	mBanor.push_back("Xml/Bana4.xml");
	mBanor.push_back("Xml/Bana5.xml");
	mBanor.push_back("Xml/Bana6Ny.xml");
	*/

	changeMap(0);
}

Game::~Game()
{
	delete Objects;
	/*system("PAUSE");
	XmlSaver saver("TestSave");
	saver.saveLevel(mlevel);
	saver.createFile();*/
	mlevel.deletePointers();
	delete mTimer;
}



void Game::changeMap(int map)
{
	if(mBana+map<(signed)mBanor.size() && mBana+map>=0)
	{
		mBana+=map;
		//std::cout << mBanor[mBana] << std::endl;
		mlevel.loadNewLevel(mBanor[mBana]);
		Timer::stop();
		for(int i=0;i<BG.size();i++)
		{
			delete BG[i];
		}
		BG=mlevel.getBackground();
		//delete mPlayer;
		mPlayer = mlevel.getPlayer();//new Player(mlevel.getPlayer()->getCollisionSprite()[0]->getPosition());
		Objects= new UnitManager(mPlayer, mlevel.getObjects());
		//mPlayer->restartPlayer();

		if(mlevel.getName()=="Tutorial1")
		{
			mSecurityLevel=0;
		}
		else if(mlevel.getName()=="Tutorial2")
		{
			mSecurityLevel=1;
		}
		else if(mlevel.getName()=="IntroBana")
		{
			mStateInput.changeState("Bank");
		}
		else
		{
			mSecurityLevel=2;
		}

		setMusic();

		Music::playMusic();
		mPlayer->restartPlayer();
	}
	else
	{
		mStateInput.changeState("QuitToMenu");
		mBana=0;
	}

}

void Game::setMusic()
{
	if (mlevel.getName()=="Tutorial2")
	{
		Music::stopMusic();
		Music::loadMusic("Music/tutorial_2.wav");
	}
	else if (mlevel.getName()=="Tutorial5")
	{
		Music::stopMusic();
		Music::loadMusic("Music/bank_1.wav");
	}
	else if (mlevel.getName()=="IntroBana")
	{
		Music::stopMusic();
		Music::loadMusic("Music/level_1.wav");
	}
}

void Game::update()
{
	if(mPlayer->getWinning()==true)
	{
		Music::pauseMusic();
		if(Sound::getSoundStatus("Winning") == 0)
		{
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
	mTimer->input();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSecurityLevel>=0)
	{
		mPlayer->interact(0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSecurityLevel>=0)
	{
		mPlayer->interact(1);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSecurityLevel>=0)
	{
		mPlayer->interact(2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSecurityLevel>=0)
	{
		mPlayer->interact(3);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mSecurityLevel>=1)
	{
		mPlayer->interact(4);
	}
	if(TestTimer.getElapsedTime().asSeconds()>mTime)
	{
		mTime=(float)0.2;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && mSecurityLevel>=1)
		{
			mPlayer->interact(5);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && mSecurityLevel>=1)
		{
			mPlayer->interact(6);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mSecurityLevel>=2)
		{
			mPlayer->interact(7);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mSecurityLevel>=0)
		{
			mPlayer->interact(8);
			TestTimer.restart();
			mTime=(float)0.7;
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mSecurityLevel>=2)
		{
		/*	sf::Vector2f Temp;
			Temp.x=(float)sf::Mouse::getPosition(mWindow).x+(float)(mWindow.getView().getCenter().x-mWindow.getSize().x/2.0);
			Temp.y=(float)sf::Mouse::getPosition(mWindow).y+(float)(mWindow.getView().getCenter().y-mWindow.getSize().y/2.0);
			mPlayer->shootHead(sf::Vector2f(Temp));*/
		//	mWindow.setView(sf::View(sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(mWindow.getSize()))));

			moveCamera();
			sf::Vector2f mVec=mWindow.convertCoords(sf::Mouse::getPosition(mWindow));
			mPlayer->shootHead(sf::Vector2f(mVec));
			TestTimer.restart();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) || sf::Keyboard::isKeyPressed(sf::Keyboard::Back))
		{
			mPlayer->restartPlayer();
			TestTimer.restart();
			Objects->reset();
		}
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		//{
		//	mPlayer->reFuel();
		//	TestTimer.restart();
		//}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
		{
			Game::changeMap(-1);
			TestTimer.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F8))
		{
			Game::changeMap(1);
			TestTimer.restart();
		}
		//if(sf::Keyboard::isKeyPressed(sf::Keyboard::F9))
		//{
		//	mStateInput.changeState("Bank");
		//	TestTimer.restart();
		//}
		//runCollisions(Objects.getUnits(), *mPlayer);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Timer::pause();
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
	Objects->draw(mWindow, true);
	mPlayer->draw(mWindow, false);
	Objects->draw(mWindow, false);
	mPlayer->draw(mWindow, true);
	mPlayer->resetAnimations();

	/*mWindow.draw(mMini1.getSprite());
	mWindow.draw(mMini2.getSprite());
	mWindow.draw(mMini3.getSprite());
	mWindow.draw(mMini4.getSprite());*/

	//for (vector<DialogueBox*>::size_type i=0; i<diaBox.size(); i++)
	//{
		//mWindow.draw(diaBox[i]->getSprite());
		//mWindow.draw(diaBox[i]->getText());
	//}
	//mWindow.draw(diaBox->getText());
	if(mPlayer->getWinning()==false)
	{
		Music::playMusic();
	}
	mTimer->update();
	mWindow.display();
}
