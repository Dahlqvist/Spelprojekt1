#include "Sound.h"
//Statiska variabler, Soundbuffer lägger in ljudet i minnet
//får inte tas bort ifall ljudet skall fortsätta användas
sf::SoundBuffer Sound::mDelaBuff;
sf::SoundBuffer Sound::mHoppaBuff;
sf::SoundBuffer Sound::mSkjutaBuff;

//Statiska variabler som får en SoundBuffer tilldelad, det är via
//dessa variabler som funktioner t.ex. play används.
sf::Sound Sound::mDela;
sf::Sound Sound::mHoppa;
sf::Sound Sound::mSkjuta;

Sound::Sound()
{
	loadSound();
}

Sound::~Sound()
{}
//Laddar in ljudfilerna från hårddisken och anger dem till
//rätt ljudvariabel.
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