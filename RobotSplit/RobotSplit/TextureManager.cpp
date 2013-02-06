#include "TextureManager.h"
//Skapar statiska variablar som alltid kommer att finnas
TextureManager::TextureMap TextureManager::mTextureMap;

//Bakgrund
sf::Texture TextureManager::textureBackground;

//Stix Right
sf::Texture TextureManager::textureStix_lowerRight;

sf::Texture TextureManager::textureStix_lowerRight_Magnet;

sf::Texture TextureManager::textureStix_lower_aniRight;

sf::Texture TextureManager::textureStix_lower_aniRight_Magnet;

sf::Texture TextureManager::textureStix_upperRight;

sf::Texture TextureManager::textureStix_upper_aniRight;

sf::Texture TextureManager::textureStix_shoot_aniRight;

sf::Texture TextureManager::textureStix_upper_split_aniRight;


//Stix Left
sf::Texture TextureManager::textureStix_lowerLeft;

sf::Texture TextureManager::textureStix_lowerLeft_Magnet;

sf::Texture TextureManager::textureStix_lower_aniLeft;

sf::Texture TextureManager::textureStix_lower_aniLeft_Magnet;

sf::Texture TextureManager::textureStix_upperLeft;

sf::Texture TextureManager::textureStix_upper_aniLeft;

sf::Texture TextureManager::textureStix_shoot_aniLeft;

sf::Texture TextureManager::textureStix_upper_split_aniLeft;

//Stix Other

sf::Texture TextureManager::texture_stix_brain_flight;

sf::Texture TextureManager::textureStix_smoke_ani;

//Enviroment

sf::Texture TextureManager::textureAnti_magnet;

sf::Texture TextureManager::textureBolcony_corner_L;

sf::Texture TextureManager::textureBolcony_corner_R;

sf::Texture TextureManager::textureBolcony_middle;
	
sf::Texture TextureManager::texturePlatform_break_ani;

sf::Texture TextureManager::textureBlue_button_ani;

sf::Texture TextureManager::textureRed_button_ani;

sf::Texture TextureManager::textureYellow_button_ani;

sf::Texture TextureManager::textureExit;

sf::Texture TextureManager::textureRail_end_L;

sf::Texture TextureManager::textureRail_end_R;

sf::Texture TextureManager::textureRail_middle;

sf::Texture TextureManager::textureTile1;

sf::Texture TextureManager::textureTile2;

sf::Texture TextureManager::textureTile3;

sf::Texture TextureManager::textureTile4;

sf::Texture TextureManager::textureTile5;

sf::Texture TextureManager::textureTile6;

sf::Texture TextureManager::textureTile7;

sf::Texture TextureManager::textureTile8;

sf::Texture TextureManager::textureTile9;

//Splash screens
sf::Texture TextureManager::textureSplash_Concept1;

sf::Texture TextureManager::textureStix_Dash;

sf::Texture TextureManager::textureStix_Jump;

sf::Texture TextureManager::textureStix_Magnet;

sf::Texture TextureManager::textureStix_Platform;

sf::Texture TextureManager::textureStix_Split;

sf::Texture TextureManager::textureWatermelon;

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

void TextureManager::loadTexture()
{
	//Ladda in texturen från en fil, behöver veta vad filerna på bilderna kommer att heta
	//Test
	textureBackground.loadFromFile(/*filename.png*/"Texture/Background/TestBackground3.png");
	
	//Stix Right
	//textureStix_lowerRight.loadFromFile("Texture/Stix/stix_lower_dark.png");
	//TextureManager::getManager().mTextureMap["StixLower"] = textureStix_lowerRight;
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

	mTextureMap["StixFeetExtend"].loadFromFile("Texture/Stix/stix_lower_Freeze_RedExt_R.png");

	mTextureMap["StixFeetExtendAni"].loadFromFile("Texture/Stix/stix_lower_Freeze.png");

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

	mTextureMap["StixFeetExtendL"].loadFromFile("Texture/Stix/stix_lower_Freeze_RedExt_L.png");

	mTextureMap["StixFeetExtendAniL"].loadFromFile("Texture/Stix/stix_lower_Freeze_Flip.png");
	//Stix Other

	mTextureMap["StixBrain"].loadFromFile("Texture/Stix/stix_brain_flight_dark.png");

	mTextureMap["StixBrainAni"].loadFromFile("Texture/Stix/stix_brain_animation_strip8_dark.png");

	mTextureMap["StixBrainLowered"].loadFromFile("Texture/Stix/stix_brain_lowered_dark.png");
	//Test
	mTextureMap["StixSmokeAni"].loadFromFile("Texture/Stix/stix_smokeanimation_strip4.png");

	//Enviroment

	mTextureMap["AntiMagnet"].loadFromFile("Texture/Enviroment/Avmagnitiserad_extraplatta.png");

	mTextureMap["BolconyCornerL"].loadFromFile("Texture/Enviroment/Bolcony_Corner_L.png");

	textureBolcony_corner_R.loadFromFile("Texture/Enviroment/Bolcony_Corner_R.png");
	mTextureMap["BolconyCornerR"] = textureBolcony_corner_R;

	mTextureMap["BolconyMiddle"].loadFromFile("Texture/Enviroment/Bolcony_Middle.png");

	mTextureMap["PlatformBreakAni"].loadFromFile("Texture/Enviroment/Break_Total_Sprite.png");

	mTextureMap["BlueButtonAni"].loadFromFile("Texture/Enviroment/Button_Blue_Sprite_16px.png");

	mTextureMap["RedButtonAni"].loadFromFile("Texture/Enviroment/Button_Red_Sprite_16px.png");

	mTextureMap["YellowButtonAni"].loadFromFile("Texture/Enviroment/Button_Yellow_Sprite_16px.png");

	mTextureMap["Exit"].loadFromFile("Texture/Enviroment/Exit.png");

	mTextureMap["RailEndL"].loadFromFile("Texture/Enviroment/Rail_End_L.png");

	mTextureMap["RailEndR"].loadFromFile("Texture/Enviroment/Rail_End_R.png");

	mTextureMap["RailMiddle"].loadFromFile("Texture/Enviroment/Rail_middle.png");

	mTextureMap["Tile1"].loadFromFile("Texture/Enviroment/tile1.png");
	mTextureMap["Tile2"].loadFromFile("Texture/Enviroment/tiles/tile2_dark.png");
	mTextureMap["Tile3"].loadFromFile("Texture/Enviroment/tiles/tile3_dark.png");
	mTextureMap["Tile4"].loadFromFile("Texture/Enviroment/tiles/tile4_dark.png");
	mTextureMap["Tile5"].loadFromFile("Texture/Enviroment/tiles/tile5_dark.png");
	mTextureMap["Tile6"].loadFromFile("Texture/Enviroment/tiles/tile6_dark.png");
	mTextureMap["Tile7"].loadFromFile("Texture/Enviroment/tiles/tile7_dark.png");
	mTextureMap["Tile8"].loadFromFile("Texture/Enviroment/tiles/tile8_dark.png");
	mTextureMap["Tile9"].loadFromFile("Texture/Enviroment/tiles/tile9_dark.png");

	//Initializing DialogueBox
	mTextureMap["DialogueBox1"].loadFromFile("Texture/Dialogue/textruta.png");

	mTextureMap["HelpBox1"].loadFromFile("Texture/Dialogue/help_textruta.png");
	
	//Initializing Lava
	mTextureMap["LavaMiddle"].loadFromFile("Texture/Enviroment/Lava_Middle.png");

	//INTIIALIZING TEMPORARYBANA
	mTextureMap["Bana1_bg1"].loadFromFile("Texture/Background/Background_Part01.png");

	mTextureMap["Bana1_bg2"].loadFromFile("Texture/Background/Background_Part02.png");

	//Initializing the frame parts.

	mTextureMap["RamTop1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part01.png");

	mTextureMap["RamTop2"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part02.png");
	
	mTextureMap["RamLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Left.png");
	
	mTextureMap["RamRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Right.png");

	mTextureMap["RamPipeLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_L_Pipe.png");

	mTextureMap["RamPipeRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_R_Pipe.png");

	mTextureMap["Line"].loadFromFile("Texture/Line.png");

	//Initializing splash-screens
	mTextureMap["RobotSplitConcept1"].loadFromFile("Texture/Splash/Robot_split_concept1.png");
	
	mTextureMap["StixSplashDash"].loadFromFile("Texture/Splash/stix_splashscreen_dash.png");
	
	mTextureMap["StixSplashJump"].loadFromFile("Texture/Splash/stix_splashscreen_jump.png");
	
	mTextureMap["StixSplashMagnet"].loadFromFile("Texture/Splash/stix_splashscreen_magnet.png");
	
	mTextureMap["StixSplashPlatform"].loadFromFile("Texture/Splash/stix_splashscreen_platform");
	
	mTextureMap["StixSplashSplit"].loadFromFile("stix_splashscreen_split.png");

	mTextureMap["Watermelon"].loadFromFile("watermelon games.png");
}

const sf::Texture TextureManager::getTexture(std::string texture)
{
	//Påkalla funktionen med namnet till rätt animationen
	if(texture == "Background")
		return getManager().textureBackground;
	else
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
	/*for(TextureMap::iterator it=getManager().mTextureMap.begin();it!=getManager().mTextureMap.end();it++)
	{
		if(it->second==sprite.getTexture())
		{
			return	it->first;
		}
	}*/
	return	"ERROR!";
}