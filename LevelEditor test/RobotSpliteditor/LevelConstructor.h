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
	void		addUnit(Unit*);
//	void		addLaser(sf::Vector2f Position,std::string id,std::string Sprite);
	void		addPlayer(Player*);
	UnitVector&	accessObjects();
	void		deleteItem(Unit*);
	void		deletePlayer();
	bool&		ifPlayerExist();
	void		setNewName(const string&);
private:
	bool		mPlayerExist;
	void		createLines();
	void		removeLines();
};
#endif
