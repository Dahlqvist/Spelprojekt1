#ifndef INC_TEXTUREMANAGER
#define INC_TEXTUREMANAGER

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
	~TextureManager();

	const static sf::Sprite		getSprite(std::string sprite);
	const static sf::Texture	getTexture(std::string texture);
	//Used to find the String part of the map for a Sprite
	//(Meant for XmlSaver use)
	const static std::string	getSpriteName(sf::Sprite);
private:
	//Function for loading all the Textures. Used in the default constructor
	static void loadTexture();
	//Function returning a static TextureManager object. Used in other get functions.
	static	TextureManager& getManager();
	//Constructor used in getManager
	TextureManager();
	//Standard constructor and operator that is not supposed to be use
	TextureManager(const TextureManager&){}
	void	operator=(const TextureManager&){}
	//Member Variables and Variabletypes

	typedef std::map<std::string, sf::Texture> TextureMap;
	static TextureMap mTextureMap;

	//Bakgrund
	static sf::Texture textureBackground;

	//Stix Right
	static sf::Texture textureStix_lowerRight;

	static sf::Texture textureStix_lowerRight_Magnet;

	static sf::Texture textureStix_lower_aniRight;

	static sf::Texture textureStix_lower_aniRight_Magnet;

	static sf::Texture textureStix_upperRight;

	static sf::Texture textureStix_upper_aniRight;

	static sf::Texture textureStix_shoot_aniRight;

	static sf::Texture textureStix_upper_split_aniRight;

	//Stix Left
	static sf::Texture textureStix_lowerLeft;

	static sf::Texture textureStix_lowerLeft_Magnet;

	static sf::Texture textureStix_lower_aniLeft;

	static sf::Texture textureStix_lower_aniLeft_Magnet;

	static sf::Texture textureStix_upperLeft;

	static sf::Texture textureStix_upper_aniLeft;

	static sf::Texture textureStix_shoot_aniLeft;

	static sf::Texture textureStix_upper_split_aniLeft;

	//Stix Other
	static sf::Texture texture_stix_brain_flight;

	static sf::Texture textureStix_smoke_ani;

	//Enviroment
	static sf::Texture textureAnti_magnet;

	static sf::Texture textureBolcony_corner_L;

	static sf::Texture textureBolcony_corner_R;

	static sf::Texture textureBolcony_middle;
	
	static sf::Texture texturePlatform_break_ani;

	static sf::Texture textureBlue_button_ani;

	static sf::Texture textureRed_button_ani;

	static sf::Texture textureYellow_button_ani;

	static sf::Texture textureExit;

	static sf::Texture textureRail_end_L;

	static sf::Texture textureRail_end_R;

	static sf::Texture textureRail_middle;

	static sf::Texture textureTile1;

	static sf::Texture textureTile2;

	static sf::Texture textureTile3;

	static sf::Texture textureTile4;

	static sf::Texture textureTile5;

	static sf::Texture textureTile6;

	static sf::Texture textureTile7;

	static sf::Texture textureTile8;

	static sf::Texture textureTile9;

	//Splash screens
	static sf::Texture textureSplash_Concept1;

	static sf::Texture textureStix_Dash;

	static sf::Texture textureStix_Jump;

	static sf::Texture textureStix_Magnet;

	static sf::Texture textureStix_Platform;

	static sf::Texture textureStix_Split;

};

#endif