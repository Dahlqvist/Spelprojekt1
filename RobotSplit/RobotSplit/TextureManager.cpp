#include "TextureManager.h"
//Skapar statiska variablar som alltid kommer att finnas
TextureManager::TextureMap TextureManager::mTextureMap;

TextureManager::TextureManager()
{
	loadTexture();
}

TextureManager::~TextureManager()
{}

TextureManager&	TextureManager::getManager()
{
	static TextureManager Manager;
	return Manager;
}

void TextureManager::internalClear()
{
	/*while(!mTextureMap.empty())
	{
		delete mTextureMap.en;
	}*/
}

void TextureManager::loadTexture()
{
	//Ladda in texturen från en fil, behöver veta vad filerna på bilderna kommer att heta
	mTextureMap["Background"].loadFromFile(/*filename.png*/"Texture/Background/TestBackground3.png");

	//Stix Right
	mTextureMap["StixLower"].loadFromFile("Texture/Stix/stix_lower_dark.png");

	mTextureMap["StixLowerMagnet"].loadFromFile("Texture/Stix/stix_lower_magnet_dark.png");

	mTextureMap["StixLowerAni"].loadFromFile("Texture/Stix/stix_loweranimation_strip8_dark.png");

	mTextureMap["StixLowerAniMagnet"].loadFromFile("Texture/Stix/stix_lower_magnetanimation_strip8_dark.png");

	mTextureMap["StixUpperAni"].loadFromFile("Texture/Stix/stix_head_match_loweranimation_strip8_H66px_dark.png");

	mTextureMap["StixUpper"].loadFromFile("Texture/Stix/stix_upper_dark.png");

	mTextureMap["StixShootAni"].loadFromFile("Texture/Stix/stix_upper_shootanimation_strip8_dark.png");

	mTextureMap["StixUpperSplit"].loadFromFile("Texture/Stix/stix_upper_splitanimation_strip8_dark.png");

	mTextureMap["StixFeetExtend"].loadFromFile("Texture/Stix/stix_lower_Freeze_dark_R.png");

	mTextureMap["StixFeetExtendAni"].loadFromFile("Texture/Stix/stix_lower_Freeze_dark.png");

	mTextureMap["StixFeetExtend"].loadFromFile("Texture/Stix/Single_stix_lower_Freeze_Ext_R_Dark.png");
	
	mTextureMap["StixFeetExtendAni"].loadFromFile("Texture/Stix/stix_lower_Freeze_R_Dark.png");

	mTextureMap["StixFeetExtendAniMagnet"].loadFromFile("Texture/Stix/stix_lower_Freeze_Ext_R_Dark.png");

	mTextureMap["StixFeetJumpAni"].loadFromFile("Texture/Stix/stix_lowerjumpanimation_strip8_dark.png");

	mTextureMap["StixUpperWalkPart"].loadFromFile("Texture/Stix/stix_upper_walkanimation.png");

	mTextureMap["StixUpperJump"].loadFromFile("Texture/Stix/stix_upper_jump.png");
	
	mTextureMap["StixUpperIdlePart"].loadFromFile("Texture/Stix/Stix004.png");

	//textureStix_FeetExtented.loadFromFile("Texture/Stix/stix_lower_Freeze_dark_R.png");
	//spriteStix_FeetExtented.setTexture(textureStix_FeetExtented);
	//mTextureMap["StixFeetExtend"] = textureStix_FeetExtented;
	//mSpriteMap["StixFeetExtend"] = spriteStix_FeetExtented;
	//Stix Left

	mTextureMap["StixLowerL"].loadFromFile("Texture/Stix/Mirror_stix_lower_dark.png");

	mTextureMap["StixLowerLMagnet"].loadFromFile("Texture/Stix/Mirror_stix_lower_magnet_dark.png");

	mTextureMap["StixLowerAniL"].loadFromFile("Texture/Stix/Mirror_stix_loweranimation_strip8_dark.png");

	mTextureMap["StixLowerAniLMagnet"].loadFromFile("Texture/Stix/Mirror_stix_lower_magnetanimation_strip8_dark.png");

	mTextureMap["StixUpperL"].loadFromFile("Texture/Stix/Mirror_stix_upper_dark.png");

	mTextureMap["StixUpperAniL"].loadFromFile("Texture/Stix/stix_head_match_loweranimation_strip8_H66px_dark_l.png");

	mTextureMap["StixShootAniL"].loadFromFile("Texture/Stix/Mirror_stix_upper_shootanimation_strip8_dark.png");

	mTextureMap["StixUpperSplitL"].loadFromFile("Texture/Stix/Mirror_stix_upper_splitanimation_strip8_dark.png");

	mTextureMap["StixFeetExtendL"].loadFromFile("Texture/Stix/Single_stix_lower_Freeze_Ext_L_Dark.png");

	mTextureMap["StixFeetExtendAniL"].loadFromFile("Texture/Stix/stix_lower_Freeze_Flip_Dark.png");

	mTextureMap["StixFeetExtendAniLMagnet"].loadFromFile("Texture/Stix/stix_lower_Freeze_Ext_L_Dark.png");

	mTextureMap["StixFeetJumpAniL"].loadFromFile("Texture/Stix/Mirror_stix_lowerjumpanimation_strip8_dark.png");

	mTextureMap["StixUpperWalkPartL"].loadFromFile("Texture/Stix/Mirror_stix_upper_walkanimation.png");

	mTextureMap["StixUpperJumpL"].loadFromFile("Texture/Stix/Mirror_stix_upper_jump.png");

	mTextureMap["StixUpperIdlePartL"].loadFromFile("Texture/Stix/Stix005.png");
	//Stix Other

	mTextureMap["StixBrainWall"].loadFromFile("Texture/Stix/brain/stix_brain_on.png");

	mTextureMap["StixBrain"].loadFromFile("Texture/Stix/brain/stix_brain_off.png");

	mTextureMap["StixBrainAni"].loadFromFile("Texture/Stix/brain/stix_brain_animation_strip7.png");

	mTextureMap["StixBrainStuck"].loadFromFile("Texture/Stix/brain/stix_brain_error.png");

	mTextureMap["StixBrainLowered"].loadFromFile("Texture/Stix/brain/stix_brain_stringasd.png");

	mTextureMap["StixRocketFuel"].loadFromFile("Texture/Stix/Rocket_Flame_Sprite.png");

	mTextureMap["StixSmokeAni"].loadFromFile("Texture/Stix/stix_smokeanimation_strip4.png");

	mTextureMap["LightTogether"].loadFromFile("Texture/Stix/stix_sil_full.png");

	mTextureMap["LightBody"].loadFromFile("Texture/Stix/stix_sil_upper.png");

	mTextureMap["LightFeet"].loadFromFile("Texture/Stix/stix_sil_lower.png");

	mTextureMap["WinningFeet"].loadFromFile("Texture/Stix/stix_winning_lower_strip6.png");

	mTextureMap["WinningBody"].loadFromFile("Texture/Stix/stix_winning_upper_strip6.png");

	//Enviroment

	mTextureMap["AntiMagnet"].loadFromFile("Texture/Enviroment/Avmagnitiserad_extraplatta.png");

	mTextureMap["BolconyCornerL"].loadFromFile("Texture/Enviroment/Tiles/Bolcony_Corner_L_32_dark.png");

	mTextureMap["BolconyCornerR"].loadFromFile("Texture/Enviroment/Tiles/Bolcony_Corner_R_32_dark.png");

	mTextureMap["BolconyMiddle"].loadFromFile("Texture/Enviroment/Tiles/Bolcony_Middle_32_dark.png");

	mTextureMap["PlatformBreakAni"].loadFromFile("Texture/Enviroment/Break_Total_Sprite.png");

	mTextureMap["BlueButtonAni"].loadFromFile("Texture/Enviroment/Button_Blue_Sprite_16px.png");
	mTextureMap["RedButtonAni"].loadFromFile("Texture/Enviroment/Button_Red_Sprite_16px.png");
	mTextureMap["YellowButtonAni"].loadFromFile("Texture/Enviroment/Button_Yellow_Sprite_16px.png");

	mTextureMap["LaserHolderStandby"].loadFromFile("Texture/Enviroment/Laser_Emitter_Standby.png");
	mTextureMap["LaserHolderOn"].loadFromFile("Texture/Enviroment/Laser_Emitter_Active.png");
	mTextureMap["LaserHolderOff"].loadFromFile("Texture/Enviroment/Laser_Emitter_Off.png");
	
	
	mTextureMap["RedLaser"].loadFromFile("Texture/Enviroment/Laser_Röd_Sprite_4px.png");
	mTextureMap["BlueLaser"].loadFromFile("Texture/Enviroment/Laser_Blå_Sprite_4px.png");
	mTextureMap["YellowLaser"].loadFromFile("Texture/Enviroment/Laser_Gul_Sprite_4px.png");

	mTextureMap["Exit"].loadFromFile("Texture/Enviroment/Exit_dark.png");

	mTextureMap["RailEndL"].loadFromFile("Texture/Enviroment/Rail_End_L_dark.png");

	mTextureMap["RailEndR"].loadFromFile("Texture/Enviroment/Rail_End_R_dark.png");

	mTextureMap["RailMiddle"].loadFromFile("Texture/Enviroment/Rail_Middle_dark.png");

	mTextureMap["Break1"].loadFromFile("Texture/Enviroment/Tiles/break3_dark.png");
	mTextureMap["Break2"].loadFromFile("Texture/Enviroment/Tiles/break2_dark.png");
	mTextureMap["Break3"].loadFromFile("Texture/Enviroment/Tiles/break_dark.png");
	mTextureMap["BreakAnim"].loadFromFile("Texture/Enviroment/Tiles/break_dustanimation_strip5.png");

	//Tutorials
	mTextureMap["House1"].loadFromFile("Texture/Tutorials/Tutorial01/House02_High02.png");
	mTextureMap["House2"].loadFromFile("Texture/Tutorials/Tutorial01/House02_TutLvl01.png");
	mTextureMap["HelpDialogue1"].loadFromFile("Texture/Tutorials/Tutorial01/radio_help_1.png");
	mTextureMap["HelpDialogue2"].loadFromFile("Texture/Tutorials/Tutorial01/radio_help_2.png");
	mTextureMap["TriggerTutorial"].loadFromFile("Texture/Tutorials/Tutorial01/Trigger.png");
	mTextureMap["Ventilation"].loadFromFile("Texture/Tutorials/Tutorial01/Vent.png");
	mTextureMap["BankSign"].loadFromFile("Texture/Tutorials/Tutorial01/BANK_SIGN.png");
	mTextureMap["BGTutorial"].loadFromFile("Texture/Tutorials/tutorial_background.png");

	mTextureMap["Tile1"].loadFromFile("Texture/Enviroment/tile1.png");
	mTextureMap["Tile2"].loadFromFile("Texture/Enviroment/tiles/tile2_dark.png");
	mTextureMap["Tile3"].loadFromFile("Texture/Enviroment/tiles/tile3_dark.png");
	mTextureMap["Tile4"].loadFromFile("Texture/Enviroment/tiles/tile4_dark.png");
	mTextureMap["Tile5"].loadFromFile("Texture/Enviroment/tiles/tile5_dark.png");
	mTextureMap["Tile6"].loadFromFile("Texture/Enviroment/tiles/tile6_dark.png");
	mTextureMap["Tile7"].loadFromFile("Texture/Enviroment/tiles/tile7_dark.png");
	mTextureMap["Tile8"].loadFromFile("Texture/Enviroment/tiles/tile8_dark.png");
	mTextureMap["Tile9"].loadFromFile("Texture/Enviroment/tiles/tile9_dark.png");

	mTextureMap["Break1"].loadFromFile("Texture/Enviroment/Tiles/break3_dark.png");
	mTextureMap["Break2"].loadFromFile("Texture/Enviroment/Tiles/break2_dark.png");
	mTextureMap["Break3"].loadFromFile("Texture/Enviroment/Tiles/break_dark.png");

	mTextureMap["TileL1a"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P2.png");
	mTextureMap["TileL1b"].loadFromFile("Texture/Enviroment/tiles/tile6_dark_P3&P7.png");
	mTextureMap["TileL1c"].loadFromFile("Texture/Enviroment/tiles/tile2_dark_P4&P10.png");
	mTextureMap["TileL1d"].loadFromFile("Texture/Enviroment/tiles/tile4_dark_P5.png");
	mTextureMap["TileL1e"].loadFromFile("Texture/Enviroment/tiles/tile3_dark_P6.png");
	mTextureMap["TileL1f"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P8.png");

	mTextureMap["TileL1g"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P13.png");
	mTextureMap["TileL1h"].loadFromFile("Texture/Enviroment/tiles/tile6_dark_P14.png");
	mTextureMap["TileL1i"].loadFromFile("Texture/Enviroment/tiles/tile2_dark_P15.png");

	mTextureMap["RailL1a"].loadFromFile("Texture/Enviroment/New/Räcke_Slut_L-1_2.png");
	mTextureMap["RailL1b"].loadFromFile("Texture/Enviroment/New/Räcke_Mitt-1_2.png");
	mTextureMap["RailL1c"].loadFromFile("Texture/Enviroment/New/Räcke_Mitt_Sluttning_R_2.png");
	mTextureMap["RailL1d"].loadFromFile("Texture/Enviroment/New/Räcke_Slut_R_2.png");

	mTextureMap["Tile10S"].loadFromFile("Texture/Enviroment/tiles/tile11_dark.png");

	mTextureMap["TileHigh"].loadFromFile("Texture/Enviroment/tiles/tile13_dark.png");
	mTextureMap["TileBreak"].loadFromFile("Texture/Enviroment/tiles/break2_dark.png");

	//Initializing DialogueBox
	mTextureMap["DialogueBox1"].loadFromFile("Texture/Dialogue/textruta.png");

	mTextureMap["HelpBoxInactive"].loadFromFile("Texture/Dialogue/help.png");

	mTextureMap["HelpBoxActive"].loadFromFile("Texture/Dialogue/help_active.png");

	mTextureMap["HelpBox1"].loadFromFile("Texture/Dialogue/help_textruta.png");

	mTextureMap["Checkpoint"].loadFromFile("Texture/Background/Robot01.png");
	
	//Initializing Lava
	mTextureMap["LavaMiddle"].loadFromFile("Texture/Enviroment/ny_lava_topp.png");

	mTextureMap["MeanixAni"].loadFromFile("Texture/Units/Meanix_idleanimation_strip8_dark.png");

	//INTIIALIZING TEMPORARYBANA
	mTextureMap["Bana1_bg1"].loadFromFile("Texture/Background/Background_Part01.png");

	mTextureMap["Bana1_bg2"].loadFromFile("Texture/Background/Background_Part02.png");

	mTextureMap["Bana2_bg1"].loadFromFile("Texture/Background/Background_2_Part01.png");

	mTextureMap["Bana2_bg2"].loadFromFile("Texture/Background/Background_2_Part02.png");

	mTextureMap["Bana3_bg1"].loadFromFile("Texture/Background/Background_3_Part01.png");

	mTextureMap["Bana3_bg2"].loadFromFile("Texture/Background/Background_3_Part02.png");

	mTextureMap["Tutorial1a"].loadFromFile("Texture/Background/background_tutorial0_PT01.png");

	mTextureMap["Tutorial1b"].loadFromFile("Texture/Background/background_tutorial0_PT02.png");

	mTextureMap["Tutorial2a"].loadFromFile("Texture/Background/background_tutorial1_PT01.png");

	mTextureMap["Tutorial2b"].loadFromFile("Texture/Background/background_tutorial1_PT02.png");

	mTextureMap["Tutorial3a"].loadFromFile("Texture/Background/background_tutorial2_PT01.png");

	mTextureMap["Tutorial3b"].loadFromFile("Texture/Background/background_tutorial2_PT02.png");

	mTextureMap["Tutorial4a"].loadFromFile("Texture/Background/background_tutorial3_PT01.png");

	mTextureMap["Tutorial4b"].loadFromFile("Texture/Background/background_tutorial3_PT02.png");

	mTextureMap["Tutorial5a"].loadFromFile("Texture/Background/background_tutorial4_PT01.png");

	mTextureMap["Tutorial5b"].loadFromFile("Texture/Background/background_tutorial4_PT02.png");

	mTextureMap["Tutorial6a"].loadFromFile("Texture/Background/background_tutorial5_PT01.png");

	mTextureMap["Tutorial6b"].loadFromFile("Texture/Background/background_tutorial5_PT02.png");

	mTextureMap["Tutorial7a"].loadFromFile("Texture/Background/background_tutorial6_PT01.png");

	mTextureMap["Tutorial7b"].loadFromFile("Texture/Background/background_tutorial6_PT02.png");

	mTextureMap["SparkleAnim"].loadFromFile("Texture/Background/Sprak_13px.png");

	mTextureMap["MouseSuicide"].loadFromFile("Texture/Background/Minirobot_02_Animation_72px_NEW.png");

	//Initializing the frame parts.

	mTextureMap["RamTop1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part01.png");

	mTextureMap["RamTop2"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part02.png");
	
	mTextureMap["RamLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Left.png");
	
	mTextureMap["RamRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Right.png");

	mTextureMap["RamPipeLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_L_Pipe.png");

	mTextureMap["RamPipeRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_R_Pipe.png");

	mTextureMap["RamPipeLeftWOPipe1"].loadFromFile("Texture/Enviroment/ram_level2_L_dark.png");

	mTextureMap["RamPipeRightWOPipe1"].loadFromFile("Texture/Enviroment/ram_level2_R_dark.png");

	mTextureMap["Line"].loadFromFile("Texture/Line.png");

	//Initializing splash-screens
	mTextureMap["RobotSplitConcept1"].loadFromFile("Texture/Splash/Robotsplit_promo1024.png");
	
	mTextureMap["StixSplashDash"].loadFromFile("Texture/Splash/stix_splashscreen_dash.png");
	
	mTextureMap["StixSplashJump"].loadFromFile("Texture/Splash/stix_splashscreen_jump.png");
	
	mTextureMap["StixSplashMagnet"].loadFromFile("Texture/Splash/stix_splashscreen_magnet.png");
	
	mTextureMap["StixSplashPlatform"].loadFromFile("Texture/Splash/stix_splashscreen_platform.png");
	
	mTextureMap["StixSplashSplit"].loadFromFile("Texture/Splash/stix_splashscreen_split.png");

	mTextureMap["Watermelon"].loadFromFile("Texture/Splash/watermelon_games.png");

	//Initializing menu
	//Bakgrunder
	mTextureMap["Main"].loadFromFile("Texture/Menu/Background/Main.png");
	mTextureMap["Ingame"].loadFromFile("Texture/Menu/Background/Ingame.png");

	//Knappar
	mTextureMap["Audio"].loadFromFile("Texture/Menu/Audio.png");
	mTextureMap["Back"].loadFromFile("Texture/Menu/Back.png");
	mTextureMap["Blip"].loadFromFile("Texture/Menu/Blip.png");
	mTextureMap["Controls"].loadFromFile("Texture/Menu/Controls.png");
	mTextureMap["EffectMute"].loadFromFile("Texture/Menu/Effect_Mute.png");
	mTextureMap["EffectVolym"].loadFromFile("Texture/Menu/Effect_Volym.png");
	mTextureMap["MusicMute"].loadFromFile("Texture/Menu/Music_Mute.png");
	mTextureMap["MusicVolym"].loadFromFile("Texture/Menu/Music_Volym.png");
	mTextureMap["NewGame"].loadFromFile("Texture/Menu/New_Game.png");
	mTextureMap["No"].loadFromFile("Texture/Menu/No.png");
	mTextureMap["Options"].loadFromFile("Texture/Menu/Options.png");
	mTextureMap["Quit"].loadFromFile("Texture/Menu/Quit.png");
	mTextureMap["QuitToMenu"].loadFromFile("Texture/Menu/Quit_To_Menu.png");
	mTextureMap["Restart"].loadFromFile("Texture/Menu/Restart.png");
	mTextureMap["Resume"].loadFromFile("Texture/Menu/Resume.png");
	mTextureMap["Slider"].loadFromFile("Texture/Menu/Slider.png");
	mTextureMap["SliderIcon"].loadFromFile("Texture/Menu/Slider_Icon.png");
	mTextureMap["StoryMode"].loadFromFile("Texture/Menu/Story_Mode.png");
	mTextureMap["Sure"].loadFromFile("Texture/Menu/Sure.png");
	mTextureMap["TimeTrial"].loadFromFile("Texture/Menu/Time_Trial.png");
	mTextureMap["TimerChecked"].loadFromFile("Texture/Menu/Timer_Checked.png");
	mTextureMap["TimerUnchecked"].loadFromFile("Texture/Menu/Timer_Unchecked.png");
	mTextureMap["Tutorial"].loadFromFile("Texture/Menu/Tutorial.png");
	mTextureMap["Yes"].loadFromFile("Texture/Menu/Yes.png");
	mTextureMap["Numbers"].loadFromFile("Texture/Menu/Numbers.png");
	mTextureMap["LeftArrow"].loadFromFile("Texture/Menu/Arrow_Left.png");
	mTextureMap["RightArrow"].loadFromFile("Texture/Menu/Arrow_Right.png");
	mTextureMap["ControlSchedule"].loadFromFile("Texture/Menu/Control_Schedule.png");

}

const sf::Texture TextureManager::getTexture(std::string texture)
{
	//Påkalla funktionen med namnet till rätt animationen
		return getManager().mTextureMap[texture];
};

const sf::Sprite TextureManager::getSprite(std::string sprite)
{	
	//Påkalla funktionen med namnet till rätt animation
		sf::Sprite temp;
		temp.setTexture(getManager().mTextureMap[sprite]);
		return temp;
		//return getManager().mSpriteMap[sprite];
}

const std::string	TextureManager::getSpriteName(sf::Sprite sprite)
{
	for(TextureMap::iterator it=getManager().mTextureMap.begin();it!=getManager().mTextureMap.end();it++)
	{
		sf::Texture* temp=&it->second;
		if(temp==sprite.getTexture())
		{
			return	it->first;
		}
	}
	return	"ERROR!";
}