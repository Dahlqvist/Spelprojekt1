#include "Music.h"
//Skapar statiska variabler.

sf::Music Music::mMusic;

Music::Music()
{}

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
	mMusic.openFromFile(music);
}

//Statisk funktion, anropas genom Music::playMusic()
//Forts�tter spela ifall musiken �r pausad.
const void Music::playMusic()
{
	if(mMusic.getStatus() == sf::Music::Stopped)
	{
		mMusic.setVolume(10);
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