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
#include "Toolbar.h"
#include <SFML/Window/WindowHandle.hpp>

typedef	Container<Unit>		UnitContainer;
typedef	Container<Player>	PlayerContainer;

using namespace sf;

class Editor
{
public:
	Editor(void);
	~Editor(void);
	void				run();
	void				renderLevel(View&);
	RenderWindow&		getWindow();
private:
	RenderWindow		mWindow;
	LevelConstructor	mLevel;
	UnitContainer		mSelectedUnit;
	PlayerContainer		mSelectedPlayer;
	View				mCurrView,miniView;
	Toolbar				mTools;
	void				eventHandler(const Event&);
	bool				collide(UnitContainer&);
	bool				collide(PlayerContainer&);
};

#endif