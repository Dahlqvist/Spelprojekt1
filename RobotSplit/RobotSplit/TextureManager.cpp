#include "TextureManager.h"
//Skapar statiska variablar som alltid kommer att finnas
TextureManager::SpriteMap TextureManager::mSpriteMap;
TextureManager::TextureMap TextureManager::mTextureMap;

//Bakgrund
sf::Texture TextureManager::textureBackground;
sf::Sprite TextureManager::spriteBackground;

//Stix Right
sf::Texture TextureManager::textureStix_lowerRight;
sf::Sprite TextureManager::spriteStix_lowerRight;

sf::Texture TextureManager::textureStix_lower_aniRight;
sf::Sprite TextureManager::spriteStix_lower_aniRight;

sf::Texture TextureManager::textureStix_upperRight;
sf::Sprite TextureManager::spriteStix_upperRight;

sf::Texture TextureManager::textureStix_upper_aniRight;
sf::Sprite TextureManager::spriteStix_upper_aniRight;

sf::Texture TextureManager::textureStix_shoot_aniRight;
sf::Sprite TextureManager::spriteStix_shoot_aniRight;

sf::Texture TextureManager::textureStix_upper_split_aniRight;
sf::Sprite TextureManager::spriteStix_upper_split_aniRight;

sf::Texture TextureManager::textureStix_FeetExtented;
sf::Sprite TextureManager::spriteStix_FeetExtented;

//Stix Left
sf::Texture TextureManager::textureStix_lowerLeft;
sf::Sprite TextureManager::spriteStix_lowerLeft;

sf::Texture TextureManager::textureStix_lower_aniLeft;
sf::Sprite TextureManager::spriteStix_lower_aniLeft;

sf::Texture TextureManager::textureStix_upperLeft;
sf::Sprite TextureManager::spriteStix_upperLeft;

sf::Texture TextureManager::textureStix_upper_aniLeft;
sf::Sprite TextureManager::spriteStix_upper_aniLeft;

sf::Texture TextureManager::textureStix_shoot_aniLeft;
sf::Sprite TextureManager::spriteStix_shoot_aniLeft;

sf::Texture TextureManager::textureStix_upper_split_aniLeft;
sf::Sprite TextureManager::spriteStix_upper_split_aniLeft;

//Stix Other

sf::Texture TextureManager::texture_stix_brain_flight;
sf::Sprite TextureManager::sprite_stix_brain_flight;

sf::Texture TextureManager::textureStix_smoke_ani;
sf::Sprite TextureManager::spriteStix_smoke_ani;

//Enviroment

sf::Texture TextureManager::textureAnti_magnet;
sf::Sprite TextureManager::spriteAnti_magnet;

sf::Texture TextureManager::textureBolcony_corner_L;
sf::Sprite TextureManager::spriteBolcony_corner_L;

sf::Texture TextureManager::textureBolcony_corner_R;
sf::Sprite TextureManager::spriteBolcony_corner_R;

sf::Texture TextureManager::textureBolcony_middle;
sf::Sprite TextureManager::spriteBolcony_middle;
	
sf::Texture TextureManager::texturePlatform_break_ani;
sf::Sprite TextureManager::spritePlatform_break_ani;

sf::Texture TextureManager::textureBlue_button_ani;
sf::Sprite TextureManager::spriteBlue_button_ani;

sf::Texture TextureManager::textureRed_button_ani;
sf::Sprite TextureManager::spriteRed_button_ani;

sf::Texture TextureManager::textureYellow_button_ani;
sf::Sprite TextureManager::spriteYellow_button_ani;

sf::Texture TextureManager::textureExit;
sf::Sprite TextureManager::spriteExit;

sf::Texture TextureManager::textureRail_end_L;
sf::Sprite TextureManager::spriteRail_end_L;

sf::Texture TextureManager::textureRail_end_R;
sf::Sprite TextureManager::spriteRail_end_R;

sf::Texture TextureManager::textureRail_middle;
sf::Sprite TextureManager::spriteRail_middle;

sf::Texture TextureManager::textureTile1;
sf::Sprite TextureManager::spriteTile1;

sf::Texture TextureManager::textureTile2;
sf::Sprite TextureManager::spriteTile2;

sf::Texture TextureManager::textureTile3;
sf::Sprite TextureManager::spriteTile3;

sf::Texture TextureManager::textureTile4;
sf::Sprite TextureManager::spriteTile4;

sf::Texture TextureManager::textureTile5;
sf::Sprite TextureManager::spriteTile5;

sf::Texture TextureManager::textureTile6;
sf::Sprite TextureManager::spriteTile6;

sf::Texture TextureManager::textureTile7;
sf::Sprite TextureManager::spriteTile7;

sf::Texture TextureManager::textureTile8;
sf::Sprite TextureManager::spriteTile8;

sf::Texture TextureManager::textureTile9;
sf::Sprite TextureManager::spriteTile9;

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
	//Ladda in texturen fr�n en fil, beh�ver veta vad filerna p� bilderna kommer att heta
	textureBackground.loadFromFile(/*filename.png*/"Texture/Background/background.png");
	//Placera texturen i en sprite-variabel
	spriteBackground.setTexture(textureBackground);
	//Stix Right
	textureStix_lowerRight.loadFromFile("Texture/Stix/stix_lower_dark.png");
	spriteStix_lowerRight.setTexture(textureStix_lowerRight);
	TextureManager::getManager().mTextureMap["StixLower"] = textureStix_lowerRight;
	mSpriteMap["StixLower"] = spriteStix_lowerRight;

	textureStix_lower_aniRight.loadFromFile("Texture/Stix/stix_loweranimation_strip8_dark.png");
	spriteStix_lower_aniRight.setTexture(textureStix_lower_aniRight);
	mTextureMap["StixLowerAni"] = textureStix_lower_aniRight;
	mSpriteMap["StixLowerAni"] = spriteStix_lower_aniRight;

	textureStix_upper_aniRight.loadFromFile("Texture/Stix/stix_head_match_loweranimation_strip8_H66px_dark.png");
	spriteStix_upper_aniRight.setTexture(textureStix_upper_aniRight);
	mTextureMap["StixUpperAni"] = textureStix_upper_aniRight;
	mSpriteMap["StixUpperAni"] = spriteStix_upper_aniRight;

	textureStix_upperRight.loadFromFile("Texture/Stix/stix_upper_dark.png");
	spriteStix_upperRight.setTexture(textureStix_upperRight);
	mTextureMap["StixUpper"] = textureStix_upperRight;
	mSpriteMap["StixUpper"] = spriteStix_upperRight;

	textureStix_shoot_aniRight.loadFromFile("Texture/Stix/stix_upper_shootanimation_strip8_dark.png");
	spriteStix_shoot_aniRight.setTexture(textureStix_shoot_aniRight);
	mTextureMap["StixShootAni"] = textureStix_shoot_aniRight;
	mSpriteMap["StixShootAni"] = spriteStix_shoot_aniRight;

	textureStix_upper_split_aniRight.loadFromFile("Texture/Stix/stix_upper_splitanimation_strip8_dark.png");
	spriteStix_upper_split_aniRight.setTexture(textureStix_upper_split_aniRight);
	mTextureMap["StixUpperSplit"] = textureStix_upper_split_aniRight;
	mSpriteMap["StixUpperSplit"] = spriteStix_upper_split_aniRight;

	textureStix_FeetExtented.loadFromFile("Texture/Stix/stix_lower_Freeze_dark_R.png");
	spriteStix_FeetExtented.setTexture(textureStix_FeetExtented);
	mTextureMap["StixFeetExtend"] = textureStix_FeetExtented;
	mSpriteMap["StixFeetExtend"] = spriteStix_FeetExtented;
	//Stix Left
	textureStix_lowerLeft.loadFromFile("Texture/Stix/Mirror_stix_lower_dark.png");
	spriteStix_lowerLeft.setTexture(textureStix_lowerLeft);
	mTextureMap["StixLowerL"] = textureStix_lowerLeft;
	mSpriteMap["StixLowerL"] = spriteStix_lowerLeft;

	textureStix_lower_aniLeft.loadFromFile("Texture/Stix/Mirror_stix_loweranimation_strip8_dark.png");
	spriteStix_lower_aniLeft.setTexture(textureStix_lower_aniLeft);
	mTextureMap["StixLowerAniL"] = textureStix_lower_aniLeft;
	mSpriteMap["StixLowerAniL"] = spriteStix_lower_aniLeft;	

	textureStix_upperLeft.loadFromFile("Texture/Stix/Mirror_stix_upper_dark.png");
	spriteStix_upperLeft.setTexture(textureStix_upperLeft);
	mTextureMap["StixUpperL"] = textureStix_upperLeft;
	mSpriteMap["StixUpperL"] = spriteStix_upperLeft;

	textureStix_upper_aniLeft.loadFromFile("Texture/Stix/stix_head_match_loweranimation_strip8_H66px_dark_l.png");
	spriteStix_upper_aniLeft.setTexture(textureStix_upper_aniLeft);
	mTextureMap["StixUpperAniL"] = textureStix_upper_aniLeft;
	mSpriteMap["StixUpperAniL"] = spriteStix_upper_aniLeft;

	textureStix_shoot_aniLeft.loadFromFile("Texture/Stix/Mirror_stix_upper_shootanimation_strip8_dark.png");
	spriteStix_shoot_aniLeft.setTexture(textureStix_shoot_aniLeft);
	mTextureMap["StixShootAniL"] = textureStix_shoot_aniLeft;
	mSpriteMap["StixShootAniL"] = spriteStix_shoot_aniLeft;

	textureStix_upper_split_aniLeft.loadFromFile("Texture/Stix/Mirror_stix_upper_splitanimation_strip8_dark.png");
	spriteStix_upper_split_aniLeft.setTexture(textureStix_upper_split_aniLeft);
	mTextureMap["StixUpperSplitL"] = textureStix_upper_split_aniLeft;
	mSpriteMap["StixUpperSplitL"] = spriteStix_upper_split_aniLeft;

	//Stix Other
	texture_stix_brain_flight.loadFromFile("Texture/Stix/stix_brain_flight_dark.png");
	sprite_stix_brain_flight.setTexture(texture_stix_brain_flight);
	mTextureMap["StixBrain"] = texture_stix_brain_flight;
	mSpriteMap["StixBrain"] = sprite_stix_brain_flight;

	mTextureMap["StixBrainAni"].loadFromFile("Texture/Stix/stix_brain_animation_strip8_dark.png");
	mSpriteMap["StixBrainAni"].setTexture(mTextureMap["StixBrainAni"]);

	mTextureMap["StixBrainLowered"].loadFromFile("Texture/Stix/stix_brain_lowered_dark.png");
	mSpriteMap["StixBrainLowered"].setTexture(mTextureMap["StixBrainLowered"]);

	textureStix_smoke_ani.loadFromFile("Texture/Stix/stix_smokeanimation_strip4_dark.png");
	spriteStix_smoke_ani.setTexture(textureStix_smoke_ani);
	mTextureMap["StixSmokeAni"] = textureStix_smoke_ani;
	mSpriteMap["StixSmokeAni"] = spriteStix_smoke_ani;

	//Enviroment

	textureAnti_magnet.loadFromFile("Texture/Enviroment/Avmagnitiserad_extraplatta.png");
	spriteAnti_magnet.setTexture(textureAnti_magnet);
	mTextureMap["AntiMagnet"] = textureAnti_magnet;
	mSpriteMap["AntiMagnet"] = spriteAnti_magnet;

	textureBolcony_corner_L.loadFromFile("Texture/Enviroment/Bolcony_Corner_L.png");
	spriteBolcony_corner_L.setTexture(textureBolcony_corner_L);
	mTextureMap["BolconyCornerL"] = textureBolcony_corner_L;
	mSpriteMap["BolconyCornerL"] = spriteBolcony_corner_L;

	textureBolcony_corner_R.loadFromFile("Texture/Enviroment/Bolcony_Corner_R.png");
	spriteBolcony_corner_R.setTexture(textureBolcony_corner_R);
	mTextureMap["BolconyCornerR"] = textureBolcony_corner_R;
	mSpriteMap["BolconyCornerR"] = spriteBolcony_corner_R;

	textureBolcony_middle.loadFromFile("Texture/Enviroment/Bolcony_Middle.png");
	spriteBolcony_middle.setTexture(textureBolcony_middle);
	mTextureMap["BolconyMiddle"] = textureBolcony_middle;
	mSpriteMap["BolconyMiddle"] = spriteBolcony_middle;

	texturePlatform_break_ani.loadFromFile("Texture/Enviroment/Break_Total_Sprite.png");
	spritePlatform_break_ani.setTexture(texturePlatform_break_ani);
	mTextureMap["PlatformBreakAni"] = texturePlatform_break_ani;
	mSpriteMap["PlatformBreakAni"] = spritePlatform_break_ani;

	textureBlue_button_ani.loadFromFile("Texture/Enviroment/Button_Blue_Sprite_16px.png");
	spriteBlue_button_ani.setTexture(textureBlue_button_ani);
	mTextureMap["BlueButtonAni"] = textureBlue_button_ani;
	mSpriteMap["BlueButtonAni"] = spriteBlue_button_ani;

	textureRed_button_ani.loadFromFile("Texture/Enviroment/Button_Red_Sprite_16px.png");
	spriteRed_button_ani.setTexture(textureRed_button_ani);
	mTextureMap["RedButtonAni"] = textureRed_button_ani;
	mSpriteMap["RedButtonAni"] = spriteRed_button_ani;

	textureYellow_button_ani.loadFromFile("Texture/Enviroment/Button_Yellow_Sprite_16px.png");
	spriteYellow_button_ani.setTexture(textureYellow_button_ani);
	mTextureMap["YellowButtonAni"] = textureYellow_button_ani;
	mSpriteMap["YellowButtonAni"] = spriteYellow_button_ani;

	textureExit.loadFromFile("Texture/Enviroment/Exit.png");
	spriteExit.setTexture(textureExit);
	mTextureMap["Exit"] = textureExit;
	mSpriteMap["Exit"] = spriteExit;

	textureRail_end_L.loadFromFile("Texture/Enviroment/Rail_End_L.png");
	spriteRail_end_L.setTexture(textureRail_end_L);
	mTextureMap["RailEndL"] = textureRail_end_L;
	mSpriteMap["RailEndL"] = spriteRail_end_L;

	textureRail_end_R.loadFromFile("Texture/Enviroment/Rail_End_R.png");
	spriteRail_end_R.setTexture(textureRail_end_R);
	mTextureMap["RailEndR"] = textureRail_end_R;
	mSpriteMap["RailEndR"] = spriteRail_end_R;

	textureRail_middle.loadFromFile("Texture/Enviroment/Rail_middle.png");
	spriteRail_middle.setTexture(textureRail_middle);
	mTextureMap["RailMiddle"] = textureRail_middle;
	mSpriteMap["RailMiddle"] = spriteRail_middle;

	textureTile1.loadFromFile("Texture/Enviroment/tile1.png");
	spriteTile1.setTexture(textureTile1);
	mTextureMap["Tile1"] = textureTile1;
	mSpriteMap["Tile1"] = spriteTile1;

	textureTile2.loadFromFile("Texture/Enviroment/tiles/tile2_dark.png");
	spriteTile2.setTexture(textureTile2);
	mTextureMap["Tile2"] = textureTile2;
	mSpriteMap["Tile2"] = spriteTile2;

	textureTile3.loadFromFile("Texture/Enviroment/tiles/tile3_dark.png");
	spriteTile3.setTexture(textureTile3);
	mTextureMap["Tile3"] = textureTile3;
	mSpriteMap["Tile3"] = spriteTile3;

	textureTile4.loadFromFile("Texture/Enviroment/tiles/tile4_dark.png");
	spriteTile4.setTexture(textureTile4);
	mTextureMap["Tile4"] = textureTile4;
	mSpriteMap["Tile4"] = spriteTile4;

	textureTile5.loadFromFile("Texture/Enviroment/tiles/tile5_dark.png");
	spriteTile5.setTexture(textureTile5);
	mTextureMap["Tile5"] = textureTile5;
	mSpriteMap["Tile5"] = spriteTile5;

	textureTile6.loadFromFile("Texture/Enviroment/tiles/tile6_dark.png");
	spriteTile6.setTexture(textureTile6);
	mTextureMap["Tile6"] = textureTile6;
	mSpriteMap["Tile6"] = spriteTile6;

	textureTile7.loadFromFile("Texture/Enviroment/tiles/tile7_dark.png");
	spriteTile7.setTexture(textureTile7);
	mTextureMap["Tile7"] = textureTile7;
	mSpriteMap["Tile7"] = spriteTile7;

	textureTile8.loadFromFile("Texture/Enviroment/tiles/tile8_dark.png");
	spriteTile8.setTexture(textureTile8);
	mTextureMap["Tile8"] = textureTile8;
	mSpriteMap["Tile8"] = spriteTile8;

	textureTile9.loadFromFile("Texture/Enviroment/tiles/tile9_dark.png");
	spriteTile9.setTexture(textureTile9);
	mTextureMap["Tile9"] = textureTile9;
	mSpriteMap["Tile9"] = spriteTile9;
	
	//Initializing Lava
	mTextureMap["LavaMiddle"].loadFromFile("Texture/Enviroment/Lava_Middle.png");
	mSpriteMap["LavaMiddle"].setTexture(mTextureMap["LavaMiddle"]);

	//INTIIALIZING TEMPORARYBANA
	mTextureMap["Bana1"].loadFromFile("Texture/Background/Background_Part01.png");
	mSpriteMap["Bana1"].setTexture(mTextureMap["Bana1"]);

	//mTextureMap["Bana1"].loadFromFile("Texture/Background/TestBackground1.png");
	//mSpriteMap["Bana1"].setTexture(mTextureMap["Bana1"]);

	//Initializing the frame parts.

	mTextureMap["RamTop1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part01.png");
	mSpriteMap["RamTop1"].setTexture(mTextureMap["RamTop1"]);

	mTextureMap["RamTop2"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Topp_Part02.png");
	mSpriteMap["RamTop2"].setTexture(mTextureMap["RamTop2"]);
	
	mTextureMap["RamLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Left.png");
	mSpriteMap["RamLeft1"].setTexture(mTextureMap["RamLeft1"]);
	
	mTextureMap["RamRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_Right.png");
	mSpriteMap["RamRight1"].setTexture(mTextureMap["RamRight1"]);

	mTextureMap["RamPipeLeft1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_L_Pipe.png");
	mSpriteMap["RamPipeLeft1"].setTexture(mTextureMap["RamPipeLeft1"]);

	mTextureMap["RamPipeRight1"].loadFromFile("Texture/Enviroment/ram_added_pipe_dark_R_Pipe.png");
	mSpriteMap["RamPipeRight1"].setTexture(mTextureMap["RamPipeRight1"]);

	mTextureMap["Line"].loadFromFile("Texture/Line.png");
	mSpriteMap["Line"].setTexture(mTextureMap["Line"]);
}

const sf::Texture TextureManager::getTexture(std::string texture)
{
	//P�kalla funktionen med namnet till r�tt animationen
	if(texture == "Background")
		return getManager().textureBackground;
	else
		return getManager().mTextureMap[texture];
};

const sf::Sprite TextureManager::getSprite(std::string sprite)
{	
	//P�kalla funktionen med namnet till r�tt animation
	if(sprite == "Background")
		return getManager().spriteBackground;	
	else
	{
		/*sf::Sprite temp;
		temp.setTexture(getManager().mTextureMap[sprite]);
		return temp;*/
		return getManager().mSpriteMap[sprite];
	}
}

const std::string	TextureManager::getSpriteName(sf::Sprite sprite)
{
	for(SpriteMap::iterator it=getManager().mSpriteMap.begin();it!=getManager().mSpriteMap.end();it++)
	{
		if(it->second.getTexture()==sprite.getTexture())
		{
			return	it->first;
		}
	}
	return	"ERROR!";
}