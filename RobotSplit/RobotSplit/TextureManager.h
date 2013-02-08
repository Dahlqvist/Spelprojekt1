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
	void internalClear();
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
};

#endif