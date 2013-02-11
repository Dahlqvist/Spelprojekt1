#include "TextureManager.h"
//Skapar statiska variablar som alltid kommer att finnas
TextureManager::TextureMap TextureManager::mTextureMap;

TextureManager::TextureManager()
{
	loadTexture();
}

TextureManager::~TextureManager()
{
}

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
	//Ladda in texturen fr�n en fil, beh�ver veta vad filerna p� bilderna kommer att heta
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
	//Stix Other

	mTextureMap["StixBrain"].loadFromFile("Texture/Stix/stix_brain_flight_dark.png");

	mTextureMap["StixBrainAni"].loadFromFile("Texture/Stix/stix_brain_animation_strip8_dark.png");

	mTextureMap["StixBrainLowered"].loadFromFile("Texture/Stix/stix_brain_lowered_dark.png");

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

	mTextureMap["Exit"].loadFromFile("Texture/Enviroment/Exit_dark.png");

	mTextureMap["RailEndL"].loadFromFile("Texture/Enviroment/Rail_End_L_dark.png");

	mTextureMap["RailEndR"].loadFromFile("Texture/Enviroment/Rail_End_R_dark.png");

	mTextureMap["RailMiddle"].loadFromFile("Texture/Enviroment/Rail_Middle_dark.png");

	mTextureMap["Tile1"].loadFromFile("Texture/Enviroment/tile1.png");
	mTextureMap["Tile2"].loadFromFile("Texture/Enviroment/tiles/tile2_dark.png");
	mTextureMap["Tile3"].loadFromFile("Texture/Enviroment/tiles/tile3_dark.png");
	mTextureMap["Tile4"].loadFromFile("Texture/Enviroment/tiles/tile4_dark.png");
	mTextureMap["Tile5"].loadFromFile("Texture/Enviroment/tiles/tile5_dark.png");
	mTextureMap["Tile6"].loadFromFile("Texture/Enviroment/tiles/tile6_dark.png");
	mTextureMap["Tile7"].loadFromFile("Texture/Enviroment/tiles/tile7_dark.png");
	mTextureMap["Tile8"].loadFromFile("Texture/Enviroment/tiles/tile8_dark.png");
	mTextureMap["Tile9"].loadFromFile("Texture/Enviroment/tiles/tile9_dark.png");

	mTextureMap["TileL1a"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P2.png");
	mTextureMap["TileL1b"].loadFromFile("Texture/Enviroment/tiles/tile6_dark_P3&P7.png");
	mTextureMap["TileL1c"].loadFromFile("Texture/Enviroment/tiles/tile2_dark_P4&P10.png");
	mTextureMap["TileL1d"].loadFromFile("Texture/Enviroment/tiles/tile4_dark_P5.png");
	mTextureMap["TileL1e"].loadFromFile("Texture/Enviroment/tiles/tile3_dark_P6.png");
	mTextureMap["TileL1f"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P8.png");

	mTextureMap["TileL1g"].loadFromFile("Texture/Enviroment/tiles/tile8_dark_P13.png");
	mTextureMap["TileL1h"].loadFromFile("Texture/Enviroment/tiles/tile6_dark_P14.png");
	mTextureMap["TileL1i"].loadFromFile("Texture/Enviroment/tiles/tile2_dark_P15.png");

	mTextureMap["RailL1a"].loadFromFile("Texture/Enviroment/New/R�cke_Slut_L-1_2.png");
	mTextureMap["RailL1b"].loadFromFile("Texture/Enviroment/New/R�cke_Mitt-1_2.png");
	mTextureMap["RailL1c"].loadFromFile("Texture/Enviroment/New/R�cke_Mitt_Sluttning_R_2.png");
	mTextureMap["RailL1d"].loadFromFile("Texture/Enviroment/New/R�cke_Slut_R_2.png");

	mTextureMap["Tile10S"].loadFromFile("Texture/Enviroment/tiles/tile11_dark.png");
	

	//Initializing DialogueBox
	mTextureMap["DialogueBox1"].loadFromFile("Texture/Dialogue/textruta.png");

	mTextureMap["HelpBoxInactive"].loadFromFile("Texture/Dialogue/help.png");

	mTextureMap["HelpBoxActive"].loadFromFile("Texture/Dialogue/help_active.png");

	mTextureMap["HelpBox1"].loadFromFile("Texture/Dialogue/help_textruta.png");

	mTextureMap["Checkpoint"].loadFromFile("Texture/Background/Robot01.png");
	
	//Initializing Lava
	mTextureMap["LavaMiddle"].loadFromFile("Texture/Enviroment/Lava_Middle.png");

	//INTIIALIZING TEMPORARYBANA
	mTextureMap["Bana1_bg1"].loadFromFile("Texture/Background/Background_Part01.png");

	mTextureMap["Bana1_bg2"].loadFromFile("Texture/Background/Background_Part02.png");

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

	mTextureMap["MouseSuicide"].loadFromFile("Texture/Background/Minirobot_02_Animation_72px.png");

	//Initializing the frame parts.

	mTextureMap["RamTop1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part01.png");

	mTextureMap["RamTop2"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part02.png");
	
	mTextureMap["RamLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Left.png");
	
	mTextureMap["RamRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Right.png");

	mTextureMap["RamPipeLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_L_Pipe.png");

	mTextureMap["RamPipeRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_R_Pipe.png");

	mTextureMap["Line"].loadFromFile("Texture/Line.png");

	//Initializing splash-screens
	mTextureMap["RobotSplitConcept1"].loadFromFile("Texture/Splash/Robotsplit_promo1024.png");
	
	mTextureMap["StixSplashDash"].loadFromFile("Texture/Splash/stix_splashscreen_dash.png");
	
	mTextureMap["StixSplashJump"].loadFromFile("Texture/Splash/stix_splashscreen_jump.png");
	
	mTextureMap["StixSplashMagnet"].loadFromFile("Texture/Splash/stix_splashscreen_magnet.png");
	
	mTextureMap["StixSplashPlatform"].loadFromFile("Texture/Splash/stix_splashscreen_platform.png");
	
	mTextureMap["StixSplashSplit"].loadFromFile("Texture/Splash/stix_splashscreen_split.png");

	mTextureMap["Watermelon"].loadFromFile("Texture/Splash/watermelon_games.png");
}

const sf::Texture TextureManager::getTexture(std::string texture)
{
	//P�kalla funktionen med namnet till r�tt animationen
		return getManager().mTextureMap[texture];
};

const sf::Sprite TextureManager::getSprite(std::string sprite)
{	
	//P�kalla funktionen med namnet till r�tt animation
		sf::Sprite temp;
		temp.setTexture(getManager().mTextureMap[sprite]);
		return temp;
		//return getManager().mSpriteMap[sprite];
}

const std::string	TextureManager::getSpriteName(sf::Sprite sprite)
{
	/*for(TextureMap::iterator it=getManager().mTextureMap.begin();it!=getManager().mTextureMap.end();it++)
	{
		if(it->second==sprite.getTexture())
		{
			return	it->first;
		}
	}*/
	return	"ERROR!";
}