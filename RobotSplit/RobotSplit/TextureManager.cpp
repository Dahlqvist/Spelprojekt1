#include "TextureManager.h"
//Skapar statiska variablar som alltid kommer att finnas

//Bakgrund
sf::Texture TextureManager::textureBackground;
sf::Sprite TextureManager::spriteBackground;

//Stix
sf::Texture TextureManager::textureStix_lower;
sf::Sprite TextureManager::spriteStix_lower;

sf::Texture TextureManager::textureStix_lower_ani;
sf::Sprite TextureManager::spriteStix_lower_ani;

sf::Texture TextureManager::textureStix_upper;
sf::Sprite TextureManager::spriteStix_upper;

sf::Texture TextureManager::textureStix_shoot_ani;
sf::Sprite TextureManager::spriteStix_shoot_ani;

sf::Texture TextureManager::textureStix_upper_split_ani;
sf::Sprite TextureManager::spriteStix_upper_split_ani;

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
{}

TextureManager::~TextureManager()
{}

void TextureManager::loadTexture()
{
	//Ladda in texturen från en fil, behöver veta vad filerna på bilderna kommer att heta
	//textureBackground.loadFromFile(/*filename.png*/"");

	//Placera texturen i en sprite-variabel
	//spriteBackground.setTexture(textureBackground);

	//Stix
	textureStix_lower.loadFromFile("Texture/Stix/stix_lower.png");
	spriteStix_lower.setTexture(textureStix_lower);

	textureStix_lower_ani.loadFromFile("Texture/Stix/stix_loweranimation_strip8.png");
	spriteStix_lower_ani.setTexture(textureStix_lower_ani);

	textureStix_upper.loadFromFile("Texture/Stix/stix_upper.png");
	spriteStix_upper.setTexture(textureStix_upper);

	textureStix_shoot_ani.loadFromFile("Texture/Stix/stix_upper_shootanimation_strip8.png");
	spriteStix_shoot_ani.setTexture(textureStix_shoot_ani);

	textureStix_upper_split_ani.loadFromFile("Texture/Stix/stix_upper_splitanimation_strip8.png");
	spriteStix_upper_split_ani.setTexture(textureStix_upper_split_ani);

	textureStix_smoke_ani.loadFromFile("Texture/Stix/stix_smokeanimation_strip4.png");
	spriteStix_smoke_ani.setTexture(textureStix_smoke_ani);

	//Enviroment

	textureAnti_magnet.loadFromFile("Texture/Enviroment/Avmagnitiserad_extraplatta.png");
	spriteAnti_magnet.setTexture(textureAnti_magnet);

	textureBolcony_corner_L.loadFromFile("Texture/Enviroment/Bolcony_Corner_L.png");
	spriteBolcony_corner_L.setTexture(textureBolcony_corner_L);

	textureBolcony_corner_R.loadFromFile("Texture/Enviroment/Bolcony_Corner_R.png");
	spriteBolcony_corner_R.setTexture(textureBolcony_corner_R);

	textureBolcony_middle.loadFromFile("Texture/Enviroment/Bolcony_Middle.png");
	spriteBolcony_middle.setTexture(textureBolcony_middle);

	texturePlatform_break_ani.loadFromFile("Texture/Enviroment/Break_Total_Sprite.png");
	spritePlatform_break_ani.setTexture(texturePlatform_break_ani);

	textureBlue_button_ani.loadFromFile("Texture/Enviroment/Button_Blue_Sprite_16px.png");
	spriteBlue_button_ani.setTexture(textureBlue_button_ani);

	textureRed_button_ani.loadFromFile("Texture/Enviroment/Button_Red_Sprite_16px.png");
	spriteRed_button_ani.setTexture(textureRed_button_ani);

	textureYellow_button_ani.loadFromFile("Texture/Enviroment/Button_Yellow_Sprite_16px.png");
	spriteYellow_button_ani.setTexture(textureYellow_button_ani);

	textureExit.loadFromFile("Texture/Enviroment/Exit.png");
	spriteExit.setTexture(textureExit);

	textureRail_end_L.loadFromFile("Texture/Enviroment/Rail_End_L.png");
	spriteRail_end_L.setTexture(textureRail_end_L);

	textureRail_end_R.loadFromFile("Texture/Enviroment/Rail_End_R.png");
	spriteRail_end_R.setTexture(textureRail_end_R);

	textureRail_middle.loadFromFile("Texture/Enviroment/Rail_middle.png");
	spriteRail_middle.setTexture(textureRail_middle);

	textureTile1.loadFromFile("Texture/Enviroment/tile1.png");
	spriteTile1.setTexture(textureTile1);

	textureTile2.loadFromFile("Texture/Enviroment/tile2.png");
	spriteTile2.setTexture(textureTile2);

	textureTile3.loadFromFile("Texture/Enviroment/tile3.png");
	spriteTile3.setTexture(textureTile3);

	textureTile4.loadFromFile("Texture/Enviroment/tile4.png");
	spriteTile4.setTexture(textureTile4);

	textureTile5.loadFromFile("Texture/Enviroment/tile5.png");
	spriteTile5.setTexture(textureTile5);

	textureTile6.loadFromFile("Texture/Enviroment/tile6.png");
	spriteTile6.setTexture(textureTile6);

	textureTile7.loadFromFile("Texture/Enviroment/tile7.png");
	spriteTile7.setTexture(textureTile7);

	textureTile8.loadFromFile("Texture/Enviroment/tile8.png");
	spriteTile8.setTexture(textureTile8);

	textureTile9.loadFromFile("Texture/Enviroment/tile9.png");
	spriteTile9.setTexture(textureTile9);
}

const sf::Texture TextureManager::getTexture(std::string texture)
{
	//Påkalla funktionen med namnet till rätt animationen
	if(texture == "Background")
		return textureBackground;

	//Stix
	else if(texture == "StixLower")
		return textureStix_lower;
	else if(texture == "StixLowerAni")
		return textureStix_lower_ani;
	else if(texture == "StixUpper")
		return textureStix_upper;
	else if(texture == "StixShootAni")
		return textureStix_shoot_ani;
	else if(texture == "StixUpperSplit")
		return textureStix_upper_split_ani;
	else if(texture == "StixSmokeAni")
		return textureStix_smoke_ani;

	//Enviroment

	else if(texture == "AntiMagnet")
		return textureAnti_magnet;
	else if(texture == "BolconyCornerL")
		return textureBolcony_corner_L;
	else if(texture == "BolconyCornerR")
		return textureBolcony_corner_R;
	else if(texture == "BolconyMiddle")
		return textureBolcony_middle;
	else if(texture == "PlatformBreakAni")
		return texturePlatform_break_ani;
	else if(texture == "BlueButtonAni")
		return textureBlue_button_ani;
	else if(texture == "RedButtonAni")
		return textureRed_button_ani;
	else if(texture == "YellowButtonAni")
		return textureYellow_button_ani;
	else if(texture == "Exit")
		return textureExit;
	else if(texture == "RailEndL")
		return textureRail_end_L;
	else if(texture == "RailEndR")
		return textureRail_end_R;
	else if(texture == "RailMiddle")
		return textureRail_middle;
	else if(texture == "Tile1")
		return textureTile1;
	else if(texture == "Tile2")
		return textureTile2;
	else if(texture == "Tile3")
		return textureTile3;
	else if(texture == "Tile4")
		return textureTile4;
	else if(texture == "Tile5")
		return textureTile5;
	else if(texture == "Tile6")
		return textureTile6;
	else if(texture == "Tile7")
		return textureTile7;
	else if(texture == "Tile8")
		return textureTile8;
	else if(texture == "Tile9")
		return textureTile9;
};

const sf::Sprite TextureManager::getSprite(std::string sprite)
{
	//Påkalla funktionen med namnet till rätt animation
	if(sprite == "Background")
		return spriteBackground;

	//Stix
	else if(sprite == "StixLower")
		return spriteStix_lower;
	else if(sprite == "StixLowerAni")
		return spriteStix_lower_ani;
	else if(sprite == "StixUpper")
		return spriteStix_upper;
	else if(sprite == "StixShootAni")
		return spriteStix_shoot_ani;
	else if(sprite == "StixUpperSplit")
		return spriteStix_upper_split_ani;
	else if(sprite == "StixSmokeAni")
		return spriteStix_smoke_ani;

	//Enviroment
	else if(sprite == "AntiMagnet")
		return spriteAnti_magnet;
	else if(sprite == "BolconyCornerL")
		return spriteBolcony_corner_L;
	else if(sprite == "BolconyCornerR")
		return spriteBolcony_corner_R;
	else if(sprite == "BolconyMiddle")
		return spriteBolcony_middle;
	else if(sprite == "PlatformBreakAni")
		return spritePlatform_break_ani;
	else if(sprite == "BlueButtonAni")
		return spriteBlue_button_ani;
	else if(sprite == "RedButtonAni")
		return spriteRed_button_ani;
	else if(sprite == "YellowButtonAni")
		return spriteYellow_button_ani;
	else if(sprite == "Exit")
		return spriteExit;
	else if(sprite == "RailEndL")
		return spriteRail_end_L;
	else if(sprite == "RailEndR")
		return spriteRail_end_R;
	else if(sprite == "RailMiddle")
		return spriteRail_middle;
	else if(sprite == "Tile1")
		return spriteTile1;
	else if(sprite == "Tile2")
		return spriteTile2;
	else if(sprite == "Tile3")
		return spriteTile3;
	else if(sprite == "Tile4")
		return spriteTile4;
	else if(sprite == "Tile5")
		return spriteTile5;
	else if(sprite == "Tile6")
		return spriteTile6;
	else if(sprite == "Tile7")
		return spriteTile7;
	else if(sprite == "Tile8")
		return spriteTile8;
	else if(sprite == "Tile9")
		return spriteTile9;
}

