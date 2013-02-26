#include "Music.h"
//Skapar statiska variabler.

sf::Music Music::mMusic;
float Music::mVolume;

Music::Music()
{
	mVolume = 100;
}

Music::~Music()
{}

Music& Music::getInstance()
{
	static Music music;
	return music;
}

	//Öppnar musikfilen och lägger den till en variabel,
	//musiken kommer att "streamas" från filen istället
	//för att den läggs in i minnet.
void Music::loadMusic(std::string music)
{
	mMusic.openFromFile(music);
}

//Statisk funktion, anropas genom Music::playMusic()
//Fortsätter spela ifall musiken är pausad.
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
//Pausar musiken, kan återupptas genom Music::playMusic()
const void Music::pauseMusic()
{
	mMusic.pause();
}
//Statisk funktion, anropas genom Music::stopMusic()
//Stoppar musiken och lägger startpunkten från början
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