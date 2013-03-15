#include "Sound.h"
//Statiska variabler, Soundbuffer l�gger in ljudet i minnet
//f�r inte tas bort ifall ljudet skall forts�tta anv�ndas

Sound::SoundMap Sound::mSoundMap;
Sound::BufferMap Sound::mBufferMap;
sf::Music Sound::mLava;
float Sound::mVolume;

//Statiska variabler som f�r en SoundBuffer tilldelad, det �r via
//dessa variabler som funktioner t.ex. play anv�nds.

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

//Laddar in ljudfilerna fr�n h�rddisken och anger dem till
//r�tt ljudvariabel.
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
	mBufferMap["Winning"].loadFromFile("Music/level_complete.wav");
	mBufferMap["Laser"].loadFromFile("Sound/pass_through_lazer_proto.wav");
	mBufferMap["MeanixTalkNormal"].loadFromFile("Sound/Meanix_speech_normal_1.wav");
	mBufferMap["StixTalkNormal"].loadFromFile("Sound/Stix_speech_normal.wav");
	mBufferMap["StixTalkAngry"].loadFromFile("Sound/Stix_speech_angry.wav");
	

	mBufferMap["TriggerHelp"].loadFromFile("Sound/Ljud/helpbox_1.wav");

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
	mSoundMap["Winning"].setBuffer(mBufferMap["Winning"]);
	mSoundMap["Laser"].setBuffer(mBufferMap["Laser"]);
	mSoundMap["MeanixTalkNormal"].setBuffer(mBufferMap["MeanixTalkNormal"]);
	mSoundMap["StixTalkNormal"].setBuffer(mBufferMap["StixTalkNormal"]);
	mSoundMap["StixTalkAngry"].setBuffer(mBufferMap["StixTalkAngry"]);


	mSoundMap["TriggerHelp"].setBuffer(mBufferMap["TriggerHelp"]);
}
//Statisk funktion, anropas genom Sound::playSound(namn)
const void Sound::playSound(std::string sound)
{
	if((sound == "Lava" && mLava.getStatus() == sf::Music::Stopped) || (sound == "Lava" && mLava.getStatus() == sf::Music::Paused))
	{
		mLava.setVolume(mVolume);
		mLava.play();
	}
	else
		if((mSoundMap[sound].getStatus() == sf::Sound::Stopped) || (mSoundMap[sound].getStatus() == sf::Sound::Paused))
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

const void Sound::pauseSound(std::string sound)
{
	if(sound == "Lava")
		mLava.pause();
	else
		mSoundMap[sound].pause();
}

const void Sound::changeVolume(float q)
{
	mVolume = q;
}

const int Sound::getSoundStatus(std::string sound)
{
	return mSoundMap[sound].getStatus();
}