#include "Music.h"
//Skapar statiska variabler.
sf::Music Music::mMusicTest;

Music::Music()
{
	loadMusic();
}

Music::~Music()
{}

	//�ppnar musikfilen och l�gger den till en variabel,
	//musiken kommer att "streamas" fr�n filen ist�llet
	//f�r att den l�ggs in i minnet.
void Music::loadMusic()
{

	mMusicTest.openFromFile("filnamn.wav");
}

//Statisk funktion, anropas genom Music::playMusic(namn)
const void Music::playMusic(std::string music)
{
	if(music == "test")
	{
		mMusicTest.play();
		mMusicTest.setLoop(true);
	}
}