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
	Level			getLevel();
	sf::Vector2f	getSize();
	void			addUnit(Unit*);
	void			addPlayer(Player*);
	UnitVector&		accessObjects();
	void			deleteItem(Unit*);
	void			deletePlayer();
	bool&			ifPlayerExist();
	void			setNewName(const string&);
	void			setBackground(const string&);
private:
	bool		mPlayerExist;
	void		createLines();
	void		removeLines();
};
#endif
