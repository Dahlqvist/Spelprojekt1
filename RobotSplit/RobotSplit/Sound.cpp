#include "Sound.h"
//Statiska variabler, Soundbuffer l�gger in ljudet i minnet
//f�r inte tas bort ifall ljudet skall forts�tta anv�ndas
sf::SoundBuffer Sound::mDelaBuff;
sf::SoundBuffer Sound::mHoppaBuff;
sf::SoundBuffer Sound::mSkjutaBuff;

//Statiska variabler som f�r en SoundBuffer tilldelad, det �r via
//dessa variabler som funktioner t.ex. play anv�nds.
sf::Sound Sound::mDela;
sf::Sound Sound::mHoppa;
sf::Sound Sound::mSkjuta;

Sound::Sound()
{
	loadSound();
}

Sound::~Sound()
{}
//Laddar in ljudfilerna fr�n h�rddisken och anger dem till
//r�tt ljudvariabel.
void Sound::loadSound()
{
	mDelaBuff.loadFromFile("Sound/Dela.wav");
	mHoppaBuff.loadFromFile("Sound/Hoppa.wav");
	mSkjutaBuff.loadFromFile("Sound/Skjuta.wav");

	mDela.setBuffer(mDelaBuff);
	mHoppa.setBuffer(mHoppaBuff);
	mSkjuta.setBuffer(mSkjutaBuff);
}
//Statisk funktion, anropas genom Sound::playSound(namn)
const void Sound::playSound(std::string sound)
{
	if(sound == "Dela")
		mDela.play();
	else if(sound == "Hoppa")
		mHoppa.play();
	else if(sound == "Skjuta")
		mSkjuta.play();
}