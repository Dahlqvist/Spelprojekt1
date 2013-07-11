#include "HighscoreState.h"
#include "StateInput.h"
#include "Window.h"
#include "ScoreLoader.h"
#include "ScoreSaver.h"
#include <sstream>
#include <SFML\System\String.hpp>

HighscoreState::HighscoreState(std::string source):
	mStateInput(StateInput::getInstance()),
	mBackground("Ingame",1,1),
	mWindow(Window::getWindow()),
	mFont(sf::Font::getDefaultFont()),
	mFileName(source)
{
	ScoreLoader	loader(source);
	mInput	=	false;
	std::time_t	raw;
	std::time(&raw);
	mTempEntry	=	new	HighscoreEntry("",1,*localtime(&raw));
	mScores	=	loader.getHighScore();
	sf::Vector2f tempPos(mWindow.getSize().x/2-mBackground.getSprite().getGlobalBounds().width/2, 0);
	mBackground.setPosition(tempPos);
}

HighscoreState::~HighscoreState()
{
}

void	HighscoreState::input()
{
	sf::Event	curEve=Window::getEvent();
	if(curEve.type==sf::Event::KeyPressed)
	{
		if(mInput)
		{
			//Saves the new highscore
			if(curEve.key.code==sf::Keyboard::Return)
			{
				ScoreSaver	saver(mFileName);
				mInput= false;
				mScores.insertEntry(*mTempEntry);
				saver.saveScore(mScores);
				saver.createFile();
				delete	mTempEntry;
			}
			//Skips saving or goes to prev state
			else if(curEve.key.code==sf::Keyboard::Escape)
			{
				mInput=false;
				delete	mTempEntry;
			}
		}
		else
		{
			mStateInput.changeState("Last");
		}
	}
	//Enters text into the name or goes to previous state
	if(curEve.type==sf::Event::TextEntered)
	{
		if(mInput)
		{
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Back))
				mTempEntry->setName(mTempEntry->getName()+sf::String(curEve.text.unicode).toAnsiString());
		}
		else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
	//		mStateInput.changeState("Last");
		}
	}
}

void	HighscoreState::render()
{
	sf::Text	rendStr;
	rendStr.setString("HighScore");
	rendStr.setFont(mFont);
	rendStr.setColor(sf::Color::White);
	rendStr.setCharacterSize(40);
	mWindow.clear();
	mWindow.draw(mBackground.getSprite());
	rendStr.setPosition((float(mWindow.getSize().x)/2.f)-(rendStr.getGlobalBounds().width/2.f),50.f);
	mWindow.draw(rendStr);
	rendStr.setString("Level: "+mScores.getLevelName());
	rendStr.setPosition((float(mWindow.getSize().x)/2.f)-(rendStr.getGlobalBounds().width/2.f),90.f);
	mWindow.draw(rendStr);
	rendStr.setString("No	Time(mm:ss):	Name:   Date:");
	rendStr.setCharacterSize(20);
	float xPos	=	(float(mWindow.getSize().x)/2.f)-(rendStr.getGlobalBounds().width/2.f);
	if(mInput)
	{
		rendStr.setString( "Enter name for new high score:");
		rendStr.setCharacterSize(40);
		rendStr.setPosition((float(mWindow.getSize().x)/2.f)-(rendStr.getGlobalBounds().width/2.f),140.f);
		mWindow.draw(rendStr);
		rendStr.setString(mTempEntry->getName());
		rendStr.setPosition((float(mWindow.getSize().x)/2.f)-(rendStr.getGlobalBounds().width/2.f),180.f);
		mWindow.draw(rendStr);
	}
	else
	{
		rendStr.setPosition(xPos,140.f);
		mWindow.draw(rendStr);
		HighscoreSet	high	= mScores.getEntries();
		int i	=	1;
		for(HighscoreSet::iterator	it = high.begin(); 
			it!= high.end();
			it++)
		{
			std::stringstream temp;
			temp	<<	i;
			rendStr.setPosition(xPos,160.f+(i*30.f));
			rendStr.setString(temp.str());
			mWindow.draw(rendStr);
			temp.str("");
			temp	<<	it->getTime();
			rendStr.setPosition(50+xPos,160.f+(i*30.f));
			rendStr.setString(temp.str());
			mWindow.draw(rendStr);
			rendStr.setPosition(190+xPos,160.f+(i*30.f));
			rendStr.setString(it->getName());
			mWindow.draw(rendStr);
			temp.str("");
			temp	<<it->getDate().tm_hour<<":"<<it->getDate().tm_min<<":"<<it->getDate().tm_sec<<"   "<<it->getDate().tm_mday<<"/"<<it->getDate().tm_mon<<"/"<<it->getDate().tm_year+1900;
			rendStr.setPosition(265+xPos,160.f+(i*30.f));
			rendStr.setString(temp.str());
			mWindow.draw(rendStr);
			i++;
		}
	}
	mWindow.display();
}

void	HighscoreState::update()
{
}

void	HighscoreState::reInitiate(std::string	name,unsigned int time)
{
	std::time_t	rawTime;
	std::time(&rawTime);
	ScoreLoader loader("");
	mInput=false;
	std::string scoreFile	=	"Xml/Score/"+name+"Score.xml";
	if(loader.loadFile(scoreFile))
	{
		mScores		=	loader.getHighScore();
		mFileName	=	scoreFile;
	}
	
	else
	{
		mScores	=	Highscore(HighscoreSet(),name,10);
		mFileName	=	scoreFile;
	}

	if(time!=0)
	{
		if(mScores.getSize()==mScores.getEntries().size())
		{
			for(HighscoreSet::iterator it=mScores.getEntries().begin();it!=mScores.getEntries().end();it++)
			{
				if(it->getTime()<time)
				{
					mInput		=	true;
					mTempEntry	=	new HighscoreEntry("",time,*localtime(&rawTime));
					break;
				}
			}
		}
		else
		{
			mInput		=	true;
			mTempEntry	=	new HighscoreEntry("",time,*localtime(&rawTime));
		}
	}
}