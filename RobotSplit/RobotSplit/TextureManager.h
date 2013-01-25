#ifndef INC_TEXTUREMANAGER
#define INC_TEXTUREMANAGER

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
	TextureManager(); //Göra om till singelton
	~TextureManager();

	static void loadTexture();
	const static sf::Sprite getSprite(std::string sprite);
	const static sf::Texture getTexture(std::string texture);

private:

	typedef std::map<std::string, sf::Sprite> SpriteMap;
	static SpriteMap mSpriteMap;

	typedef std::map<std::string, sf::Texture> TextureMap;
	static TextureMap mTextureMap;

	//Bakgrund
	static sf::Texture textureBackground;
	static sf::Sprite spriteBackground;

	//Stix
	static sf::Texture textureStix_lower;
	static sf::Sprite spriteStix_lower;

	static sf::Texture textureStix_lower_ani;
	static sf::Sprite spriteStix_lower_ani;

	static sf::Texture textureStix_upper;
	static sf::Sprite spriteStix_upper;

	static sf::Texture textureStix_shoot_ani;
	static sf::Sprite spriteStix_shoot_ani;

	static sf::Texture textureStix_upper_split_ani;
	static sf::Sprite spriteStix_upper_split_ani;

	static sf::Texture textureStix_smoke_ani;
	static sf::Sprite spriteStix_smoke_ani;

	//Enviroment
	static sf::Texture textureAnti_magnet;
	static sf::Sprite spriteAnti_magnet;

	static sf::Texture textureBolcony_corner_L;
	static sf::Sprite spriteBolcony_corner_L;

	static sf::Texture textureBolcony_corner_R;
	static sf::Sprite spriteBolcony_corner_R;

	static sf::Texture textureBolcony_middle;
	static sf::Sprite spriteBolcony_middle;
	
	static sf::Texture texturePlatform_break_ani;
	static sf::Sprite spritePlatform_break_ani;

	static sf::Texture textureBlue_button_ani;
	static sf::Sprite spriteBlue_button_ani;

	static sf::Texture textureRed_button_ani;
	static sf::Sprite spriteRed_button_ani;

	static sf::Texture textureYellow_button_ani;
	static sf::Sprite spriteYellow_button_ani;

	static sf::Texture textureExit;
	static sf::Sprite spriteExit;

	static sf::Texture textureRail_end_L;
	static sf::Sprite spriteRail_end_L;

	static sf::Texture textureRail_end_R;
	static sf::Sprite spriteRail_end_R;

	static sf::Texture textureRail_middle;
	static sf::Sprite spriteRail_middle;

	static sf::Texture textureTile1;
	static sf::Sprite spriteTile1;

	static sf::Texture textureTile2;
	static sf::Sprite spriteTile2;

	static sf::Texture textureTile3;
	static sf::Sprite spriteTile3;

	static sf::Texture textureTile4;
	static sf::Sprite spriteTile4;

	static sf::Texture textureTile5;
	static sf::Sprite spriteTile5;

	static sf::Texture textureTile6;
	static sf::Sprite spriteTile6;

	static sf::Texture textureTile7;
	static sf::Sprite spriteTile7;

	static sf::Texture textureTile8;
	static sf::Sprite spriteTile8;

	static sf::Texture textureTile9;
	static sf::Sprite spriteTile9;
};

#endif