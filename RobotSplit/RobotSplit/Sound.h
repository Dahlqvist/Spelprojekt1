#ifndef INC_SOUND
#define INC_SOUND

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <string>
#include <map>


class Sound
{
public:
	static Sound& getInstance();
	
	const static void playSound(std::string sound);
	const static void stopSound(std::string sound);
private:
	Sound();
	Sound(const Sound& sound);
	Sound operator=(const Sound& sound);
	~Sound();
	void loadSound();

	typedef std::map<std::string, sf::Sound> SoundMap;
	static SoundMap mSoundMap;
	typedef std::map<std::string, sf::SoundBuffer> BufferMap;
	static BufferMap mBufferMap;
	static sf::Music mLava;
};

#endif