#include "Sound.h"
//Statiska variabler, Soundbuffer lägger in ljudet i minnet
//får inte tas bort ifall ljudet skall fortsätta användas

Sound::SoundMap Sound::mSoundMap;
Sound::BufferMap Sound::mBufferMap;
sf::Music Sound::mLava;
float Sound::mVolume;

//Statiska variabler som får en SoundBuffer tilldelad, det är via
//dessa variabler som funktioner t.ex. play används.

Sound::Sound()
{
	mVolume = 100;
	loadSound();
}

Sound::~Sound()
{}

Sound& Sound::getInstance()
{
	static Sound sound;
	return sound;
}

//Laddar in ljudfilerna från hårddisken och anger dem till
//rätt ljudvariabel.
void Sound::loadSound()
{
	mLava.openFromFile("Sound/lava_proto.wav");

	mBufferMap["Dash"].loadFromFile("Sound/dash_proto.wav");
	mBufferMap["Extend"].loadFromFile("Sound/extend_proto.wav");
	mBufferMap["ExtBodyColl"].loadFromFile("Sound/extention_body_collision_proto.wav");
	mBufferMap["Death"].loadFromFile("Sound/general_death_proto.wav");
	mBufferMap["HeadStuck"].loadFromFile("Sound/head_stuck_proto.wav");
	mBufferMap["Jump"].loadFromFile("Sound/jump_proto.wav");
	mBufferMap["MagnetLetGo"].loadFromFile("Sound/magnet_let_go_proto.wav");
	mBufferMap["MagnetStuckWall"].loadFromFile("Sound/magnet_stuck_wall_proto.wav");
	mBufferMap["ShootHead"].loadFromFile("Sound/shoot_head_proto.wav");
	mBufferMap["Move"].loadFromFile("Sound/move_smoother_proto.wav");
	mBufferMap["Split"].loadFromFile("Sound/split_proto.wav");

	mSoundMap["Dash"].setBuffer(mBufferMap["Dash"]);
	mSoundMap["Extend"].setBuffer(mBufferMap["Extend"]);
	mSoundMap["ExtBodyColl"].setBuffer(mBufferMap["ExtBodyColl"]);
	mSoundMap["Death"].setBuffer(mBufferMap["Death"]);
	mSoundMap["HeadStuck"].setBuffer(mBufferMap["HeadStuck"]);
	mSoundMap["Jump"].setBuffer(mBufferMap["Jump"]);
	mSoundMap["MagnetLetGo"].setBuffer(mBufferMap["MagnetLetGo"]);
	mSoundMap["MagnetStuckWall"].setBuffer(mBufferMap["MagnetStuckWall"]);
	mSoundMap["ShootHead"].setBuffer(mBufferMap["ShootHead"]);
	mSoundMap["Move"].setBuffer(mBufferMap["Move"]);
	mSoundMap["Split"].setBuffer(mBufferMap["Split"]);
	//mSoundMap["Move"].setVolume(20);
}
//Statisk funktion, anropas genom Sound::playSound(namn)
const void Sound::playSound(std::string sound)
{
	if(sound == "Lava")
	{
		mLava.setVolume(mVolume);
		mLava.play();
	}
	else
		if(mSoundMap[sound].getStatus() == sf::Sound::Stopped)
		{
			mSoundMap[sound].setVolume(mVolume);
			mSoundMap[sound].play();
		}
}

const void Sound::stopSound(std::string sound)
{
	if(sound == "Lava")
		mLava.stop();
	else
		mSoundMap[sound].stop();
}

const void Sound::changeVolume(float q)
{
	mVolume = q;
}