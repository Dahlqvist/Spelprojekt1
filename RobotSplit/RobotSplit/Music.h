#ifndef INC_MUSIC
#define INC_MUSIC

#include <SFML/Audio/Music.hpp>

class Music
{
public:
	Music();
	~Music();
	const static void playMusic(std::string music);
private:
	void loadMusic();
	static sf::Music mMusicTest;
};

#endif