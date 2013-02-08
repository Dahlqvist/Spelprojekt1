#ifndef INC_SOUND
#define INC_SOUND

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <string>


class Sound
{
public:
	
	~Sound();
	const static void playSound(std::string sound);
private:
	Sound();
	Sound(const Sound& sound);

	void loadSound();
	static sf::SoundBuffer mDelaBuff;
	static sf::SoundBuffer mHoppaBuff;
	static sf::SoundBuffer mSkjutaBuff;

	static sf::Sound mDela;
	static sf::Sound mHoppa;
	static sf::Sound mSkjuta;
};

#endif