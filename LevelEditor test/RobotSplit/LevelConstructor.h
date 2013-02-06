#ifndef INC_LEVELCONSTRUCTOR
#define	INC_LEVELCONSTRUCTOR
#include "Level.h"
#include <SFML\Graphics.hpp>
class LevelConstructor :
	public Level
{
public:
	LevelConstructor(void);
	LevelConstructor(const Level&);
	~LevelConstructor(void);
	Level	getLevel();
	void	addUnit(sf::Vector2f Position,std::string id,std::string Sprite);
//	void	addLaser(sf::Vector2f Position,std::string id,std::string Sprite);
	void	addPlayer(sf::Vector2f Position);
	void	addPlatform(sf::Vector2f Position,std::string id,std::string Sprite);
	void	checkDeletedPointers();
private:
	void	createLines();
	void	removeLines();
};
#endif
