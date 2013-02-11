#include "Sound.h"
//Statiska variabler, Soundbuffer l�gger in ljudet i minnet
//f�r inte tas bort ifall ljudet skall forts�tta anv�ndas

Sound::SoundMap Sound::mSoundMap;
Sound::BufferMap Sound::mBufferMap;

//Statiska variabler som f�r en SoundBuffer tilldelad, det �r via
//dessa variabler som funktioner t.ex. play anv�nds.

Sound::Sound()
{
	loadSound();
}

Sound::~Sound()
{}

Sound& Sound::getInstance()
{
	static Sound sound;
	return sound;
}

//Laddar in ljudfilerna fr�n h�rddisken och anger dem till
//r�tt ljudvariabel.
void Sound::loadSound()
{
	mBufferMap["Dash"].loadFromFile("Sound/dash_proto.wav");
	mBufferMap["Extend"].loadFromFile("Sound/extend_proto.wav");
	mBufferMap["ExtBodyColl"].loadFromFile("Sound/extention_body_collision_proto.wav");
	mBufferMap["Death"].loadFromFile("Sound/general_death_proto.wav");
	mBufferMap["HeadStuck"].loadFromFile("Sound/head_stuck_proto.wav");
	mBufferMap["Jump"].loadFromFile("Sound/jump_proto.wav");
	mBufferMap["Lava"].loadFromFile("Sound/lava_proto.wav");
	mBufferMap["MagnetLetGo"].loadFromFile("Sound/magnet_let_go_proto.wav");
	mBufferMap["MagnetStuckWall"].loadFromFile("Sound/magnet_stuck_wall_proto.wav");
	mBufferMap["ShootHead"].loadFromFile("Sound/shoot_head_proto.wav");
	mBufferMap["Move"].loadFromFile("Sound/move_proto.wav");
	mBufferMap["Split"].loadFromFile("Sound/split_proto.wav");

	mSoundMap["Dash"].setBuffer(mBufferMap["Dash"]);
	mSoundMap["Extend"].setBuffer(mBufferMap["Extend"]);
	mSoundMap["ExtBodyColl"].setBuffer(mBufferMap["ExtBodyColl"]);
	mSoundMap["Death"].setBuffer(mBufferMap["Death"]);
	mSoundMap["HeadStuck"].setBuffer(mBufferMap["HeadStuck"]);
	mSoundMap["Jump"].setBuffer(mBufferMap["Jump"]);
	mSoundMap["Lava"].setBuffer(mBufferMap["Lava"]);
	mSoundMap["MagnetLetGo"].setBuffer(mBufferMap["MagnetLetGo"]);
	mSoundMap["MagnetStuckWall"].setBuffer(mBufferMap["MagnetStuckWall"]);
	mSoundMap["ShootHead"].setBuffer(mBufferMap["ShootHead"]);
	mSoundMap["Move"].setBuffer(mBufferMap["Move"]);
	mSoundMap["Split"].setBuffer(mBufferMap["Split"]);
	mSoundMap["Move"].setVolume(20);
}
//Statisk funktion, anropas genom Sound::playSound(namn)
const void Sound::playSound(std::string sound)
{
	if(mSoundMap[sound].getStatus() == sf::Sound::Stopped)
		mSoundMap[sound].play();
}

const void Sound::stopSound(std::string sound)
{
	mSoundMap[sound].stop();
}