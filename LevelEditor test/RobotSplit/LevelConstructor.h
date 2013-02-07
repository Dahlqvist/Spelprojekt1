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
	LevelConstructor(const string&);
	~LevelConstructor(void);
	Level		getLevel();
	void		addUnit(sf::Vector2f Position,std::string id,std::string sprite,bool solid=true);
//	void		addLaser(sf::Vector2f Position,std::string id,std::string Sprite);
	void		addPlayer(sf::Vector2f Position);
	void		addPlatform(sf::Vector2f Position,std::string Sprite,int life=0);
	UnitVector&	accessObjects();
	void		deleteItem(int placement);
	void		deletePlayer();
private:
	bool		mPlayerExist;
	void		createLines();
	void		removeLines();
};
#endif
