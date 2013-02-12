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

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class Editor
{
public:
	Editor(void);
	void	run();
	~Editor(void);
private:
	RenderWindow		window;
	LevelConstructor	level;
	UnitContainer		selected;
	TextField			MTEXT;
	View				CurrView,miniView;
	void				renderLevel(View&);
	void				eventHandler(const Event&);
	bool				collide(UnitContainer&);
};

#endif