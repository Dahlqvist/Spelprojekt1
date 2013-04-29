#include "Music.h"
//Skapar statiska variabler.

sf::Music Music::mMusic;
float Music::mVolume;
std::string Music::mCurrentMusic;

Music::Music()
{
	mVolume = 100;
	mCurrentMusic = "";
}

Music::~Music()
{}

Music& Music::getInstance()
{
	static Music music;
	return music;
}

	//�ppnar musikfilen och l�gger den till en variabel,
	//musiken kommer att "streamas" fr�n filen ist�llet
	//f�r att den l�ggs in i minnet.
void Music::loadMusic(std::string music)
{
	if(music != "" || music != " ")
	{
		if(mCurrentMusic != music)
		{
			mCurrentMusic = music;
			mMusic.openFromFile(music);
		}
	}
}

//Statisk funktion, anropas genom Music::playMusic()
//Forts�tter spela ifall musiken �r pausad.
const void Music::playMusic()
{
	if(mMusic.getStatus() == sf::Music::Stopped || mMusic.getStatus() == sf::Music::Paused)
	{
		mMusic.setVolume(mVolume);
		mMusic.play();
		mMusic.setLoop(true);
	}
}
//Statisk funktion, anropas genom Music::pauseMusic()
//Pausar musiken, kan �terupptas genom Music::playMusic()
const void Music::pauseMusic()
{
	mMusic.pause();
}
//Statisk funktion, anropas genom Music::stopMusic()
//Stoppar musiken och l�gger startpunkten fr�n b�rjan
const void Music::stopMusic()
{
	mMusic.stop();
}

const void Music::changeVolume(float q)
{
	mVolume = q;
}

const float Music::getVolume()
{
	return mMusic.getVolume();
}

const std::string Music::getCurrentMusic()
{
	return mCurrentMusic;
}