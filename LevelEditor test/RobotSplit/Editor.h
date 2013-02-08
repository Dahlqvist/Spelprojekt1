#ifndef	INC_EDITOR
#define	INC_EDITOR
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "LevelConstructor.h"
#include "Unit.h"
#include "Player.h"
#include "TextField.h"
#include "Container.h"
#include <SFML/Window/WindowHandle.hpp>
using namespace sf;
typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;
class Editor
{
	RenderWindow		window;
	LevelConstructor	level;
	UnitContainer	selected;
public:
	Editor(void);
	void	run();
	~Editor(void);
	void	renderLevel(View);
};

#endif