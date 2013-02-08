#include "Music.h"
//Skapar statiska variabler.
sf::Music Music::mMusicTest;

Music::Music()
{
	loadMusic();
}

Music::~Music()
{}

	//Öppnar musikfilen och lägger den till en variabel,
	//musiken kommer att "streamas" från filen istället
	//för att den läggs in i minnet.
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