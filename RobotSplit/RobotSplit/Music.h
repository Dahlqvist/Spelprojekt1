#ifndef INC_MUSIC
#define INC_MUSIC

#include <SFML/Audio/Music.hpp>
#include <map>
#include <string>

class Music
{
public:
	static Music& getInstance();
	static void loadMusic(std::string music);
	const static void playMusic();
	const static void pauseMusic();
	const static void stopMusic();
	const static void changeVolume(float q);
	const static float getVolume();
private:
	Music();
	Music(const Music& music);
	Music operator=(Music& music);
	~Music();
	static sf::Music mMusic;
	static float mVolume;
};

#endif