#pragma once
#include "Level.h"
class LevelConstructor :
	public Level
{
public:
	LevelConstructor(void);
	LevelConstructor(const Level&);
	~LevelConstructor(void);
	Level	getLevel();
	void	addUnit();
	void	addLaser();
	void	addPlayer();
	void	addPlatform();
private:
	void	createLines();
	void	removieLines();
};

